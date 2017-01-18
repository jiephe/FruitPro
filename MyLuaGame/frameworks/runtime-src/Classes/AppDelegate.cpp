#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "lua_module_register.h"
#include "lua_MyClass_auto.hpp"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_LINUX)
#include "ide-support/CodeIDESupport.h"
#endif

#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)
#include "runtime/Runtime.h"
#include "ide-support/RuntimeLuaImpl.h"
#endif

using namespace CocosDenshion;

USING_NS_CC;
using namespace std;


/*
* lpack.c
* a Lua library for packing and unpacking binary data
* Luiz Henrique de Figueiredo <lhf@tecgraf.puc-rio.br>
* 29 Jun 2007 19:27:20
* This code is hereby placed in the public domain.
* with contributions from Ignacio Castaño <castanyo@yahoo.es> and
* Roberto Ierusalimschy <roberto@inf.puc-rio.br>.
*/

#define	OP_ZSTRING	'z'		/* zero-terminated string */
#define	OP_BSTRING	'p'		/* string preceded by length byte */
#define	OP_WSTRING	'P'		/* string preceded by length word */
#define	OP_SSTRING	'a'		/* string preceded by length size_t */
#define	OP_STRING	'A'		/* string */
#define	OP_FLOAT	'f'		/* float */
#define	OP_DOUBLE	'd'		/* double */
#define	OP_NUMBER	'n'		/* Lua number */
#define	OP_CHAR		'c'		/* char */
#define	OP_BYTE		'b'		/* byte = unsigned char */
#define	OP_SHORT	'h'		/* short */
#define	OP_USHORT	'H'		/* unsigned short */
#define	OP_INT		'i'		/* int */
#define	OP_UINT		'I'		/* unsigned int */
#define	OP_LONG		'l'		/* long */
#define	OP_ULONG	'L'		/* unsigned long */
#define	OP_LITTLEENDIAN	'<'		/* little endian */
#define	OP_BIGENDIAN	'>'		/* big endian */
#define	OP_NATIVE	'='		/* native endian */

#include <ctype.h>
#include <string.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

static void badcode(lua_State *L, int c)
{
	char s[]="bad code `?'";
	s[sizeof(s)-3]=c;
	luaL_argerror(L,1,s);
}

static int doendian(int c)
{
	int x=1;
	int e=*(char*)&x;
	if (c==OP_LITTLEENDIAN) return !e;
	if (c==OP_BIGENDIAN) return e;
	if (c==OP_NATIVE) return 0;
	return 0;
}

static void doswap(int swap, void *p, size_t n)
{
	if (swap)
	{
		char *a=(char*)p;
		int i,j;
		for (i=0, j=n-1, n=n/2; n--; i++, j--)
		{
			char t=a[i]; a[i]=a[j]; a[j]=t;
		}
	}
}

#define UNPACKNUMBER(OP,T)		\
   case OP:				\
{					\
	T a;				\
	int m=sizeof(a);			\
	if (i+m>len) goto done;		\
	memcpy(&a,s+i,m);			\
	i+=m;				\
	doswap(swap,&a,m);			\
	lua_pushnumber(L,(lua_Number)a);	\
	++n;				\
	break;				\
}

#define UNPACKSTRING(OP,T)		\
   case OP:				\
{					\
	T l;				\
	int m=sizeof(l);			\
	if (i+m>len) goto done;		\
	memcpy(&l,s+i,m);			\
	doswap(swap,&l,m);			\
	if (i+m+l>len) goto done;		\
	i+=m;				\
	lua_pushlstring(L,s+i,l);		\
	i+=l;				\
	++n;				\
	break;				\
}

static int l_unpack(lua_State *L) 		/** unpack(s,f,[init]) */
{
	size_t len;
	const char *s=luaL_checklstring(L,1,&len);
	const char *f=luaL_checkstring(L,2);
	int i=luaL_optnumber(L,3,1)-1;
	int n=0;
	int swap=0;
	lua_pushnil(L);
	while (*f)
	{
		int c=*f++;
		int N=1;
		if (isdigit(*f)) 
		{
			N=0;
			while (isdigit(*f)) N=10*N+(*f++)-'0';
			if (N==0 && c==OP_STRING) { lua_pushliteral(L,""); ++n; }
		}
		while (N--) switch (c)
		{
		case OP_LITTLEENDIAN:
		case OP_BIGENDIAN:
		case OP_NATIVE:
			{
				swap=doendian(c);
				N=0;
				break;
			}
		case OP_STRING:
			{
				++N;
				if (i+N>len) goto done;
				lua_pushlstring(L,s+i,N);
				i+=N;
				++n;
				N=0;
				break;
			}
		case OP_ZSTRING:
			{
				size_t l;
				if (i>=len) goto done;
				l=strlen(s+i);
				lua_pushlstring(L,s+i,l);
				i+=l+1;
				++n;
				break;
			}
			UNPACKSTRING(OP_BSTRING, unsigned char)
				UNPACKSTRING(OP_WSTRING, unsigned short)
				UNPACKSTRING(OP_SSTRING, size_t)
				UNPACKNUMBER(OP_NUMBER, lua_Number)
				UNPACKNUMBER(OP_DOUBLE, double)
				UNPACKNUMBER(OP_FLOAT, float)
				UNPACKNUMBER(OP_CHAR, char)
				UNPACKNUMBER(OP_BYTE, unsigned char)
				UNPACKNUMBER(OP_SHORT, short)
				UNPACKNUMBER(OP_USHORT, unsigned short)
				UNPACKNUMBER(OP_INT, int)
				UNPACKNUMBER(OP_UINT, unsigned int)
				UNPACKNUMBER(OP_LONG, long)
				UNPACKNUMBER(OP_ULONG, unsigned long)
		case ' ': case ',':
			break;
		default:
			badcode(L,c);
			break;
		}
	}
done:
	lua_pushnumber(L,i+1);
	lua_replace(L,-n-2);
	return n+1;
}

#define PACKNUMBER(OP,T)			\
   case OP:					\
{						\
	T a=(T)luaL_checknumber(L,i++);		\
	doswap(swap,&a,sizeof(a));			\
	luaL_addlstring(&b,(const char*)&a,sizeof(a));	\
	break;					\
}

#define PACKSTRING(OP,T)			\
   case OP:					\
{						\
	size_t l;					\
	const char *a=luaL_checklstring(L,i++,&l);	\
	T ll=(T)l;					\
	doswap(swap,&ll,sizeof(ll));		\
	luaL_addlstring(&b,(const char*)&ll,sizeof(ll));	\
	luaL_addlstring(&b,a,l);			\
	break;					\
}

static int l_pack(lua_State *L) 		/** pack(f,...) */
{
	int i=2;
	const char *f=luaL_checkstring(L,1);
	int swap=0;
	luaL_Buffer b;
	luaL_buffinit(L,&b);
	while (*f)
	{
		int c=*f++;
		int N=1;
		if (isdigit(*f)) 
		{
			N=0;
			while (isdigit(*f)) N=10*N+(*f++)-'0';
		}
		while (N--) switch (c)
		{
		case OP_LITTLEENDIAN:
		case OP_BIGENDIAN:
		case OP_NATIVE:
			{
				swap=doendian(c);
				N=0;
				break;
			}
		case OP_STRING:
		case OP_ZSTRING:
			{
				size_t l;
				const char *a=luaL_checklstring(L,i++,&l);
				luaL_addlstring(&b,a,l+(c==OP_ZSTRING));
				break;
			}
			PACKSTRING(OP_BSTRING, unsigned char)
			PACKSTRING(OP_WSTRING, unsigned short)
			PACKSTRING(OP_SSTRING, size_t)
			PACKNUMBER(OP_NUMBER, lua_Number)
			PACKNUMBER(OP_DOUBLE, double)
			PACKNUMBER(OP_FLOAT, float)
			PACKNUMBER(OP_CHAR, char)
			PACKNUMBER(OP_BYTE, unsigned char)
			PACKNUMBER(OP_SHORT, short)
			PACKNUMBER(OP_USHORT, unsigned short)
			PACKNUMBER(OP_INT, int)
			PACKNUMBER(OP_UINT, unsigned int)
			PACKNUMBER(OP_LONG, long)
			PACKNUMBER(OP_ULONG, unsigned long)
		case ' ': case ',':
			break;
		default:
			badcode(L,c);
			break;
		}
	}
	luaL_pushresult(&b);
	return 1;
}

static const luaL_reg R[] =
{
	{"pack",	l_pack},
	{"unpack",	l_unpack},
	{NULL,	NULL}
};

int luaopen_pack(lua_State *L)
{
#ifdef USE_GLOBALS
	lua_register(L,"bpack",l_pack);
	lua_register(L,"bunpack",l_unpack);
#else
	luaL_openlib(L, LUA_STRLIBNAME, R, 0);
#endif
	return 0;
}
/*
* lpack.c
* a Lua library for packing and unpacking binary data
* Luiz Henrique de Figueiredo <lhf@tecgraf.puc-rio.br>
* 29 Jun 2007 19:27:20
* This code is hereby placed in the public domain.
* with contributions from Ignacio Castaño <castanyo@yahoo.es> and
* Roberto Ierusalimschy <roberto@inf.puc-rio.br>.
*/


AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();

#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)
    // NOTE:Please don't remove this call if you want to debug with Cocos Code IDE
    RuntimeEngine::getInstance()->end();
#endif

}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages,
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching()
{	
    // set default FPS
    Director::getInstance()->setAnimationInterval(1.0 / 60.0f);

    // register lua module
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    lua_State* L = engine->getLuaStack()->getLuaState();
    lua_module_register(L);
	register_all_MyClass(L);

	luaopen_pack(L);

    register_all_packages();

    LuaStack* stack = engine->getLuaStack();
    stack->setXXTEAKeyAndSign("2dxLua", strlen("2dxLua"), "XXTEA", strlen("XXTEA"));

    //register custom function
    //LuaStack* stack = engine->getLuaStack();
    //register_custom_function(stack->getLuaState());

#if (COCOS2D_DEBUG > 0) && (CC_CODE_IDE_DEBUG_SUPPORT > 0)
    // NOTE:Please don't remove this call if you want to debug with Cocos Code IDE
    auto runtimeEngine = RuntimeEngine::getInstance();
    runtimeEngine->addRuntime(RuntimeLuaImpl::create(), kRuntimeEngineLua);
    runtimeEngine->start();
#else
    if (engine->executeScriptFile("src/main.lua"))
    {
        return false;
    }
#endif

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
