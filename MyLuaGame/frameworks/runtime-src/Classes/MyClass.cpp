#include "MyClass.h"
#include "CCLuaEngine.h"
#include "lua.h"
#include "tolua_fix.h"
#include <iostream>

int MyClass::foo(int i)
{
  return i + 100;
}

int MyClass::TransmitLuaContruct(int nReq, const char* pData, const char* pData2, int nDateLen)
{
	//1. 解析Lua传过来的结构体
	auto engine = LuaEngine::getInstance();
	lua_State* L = engine->getLuaStack()->getLuaState();

	int n1 = lua_tointeger(L, -1);
	int n3 = lua_tointeger(L, -4);
	const char* pDst = lua_tostring(L, -2);		// 从L的栈顶取出数据
	const char* pDst1 = lua_tostring(L, -3);
	AUCTION_BANKER_AUTO* pInfo = (AUCTION_BANKER_AUTO*)pDst;
	AUCTION_BANKER_AUTO* pInfo1 = (AUCTION_BANKER_AUTO*)pDst1;
	int a = pInfo->nAutoChairNO;
	int b = pInfo->nChairNO;

	memset(pInfo, 0x0, sizeof(AUCTION_BANKER_AUTO));

	//2.调用Lua层函数 
	lua_getglobal(L, "LuaFunc");					// 获取函数，压入栈中  

	lua_pushinteger(L, a);							// 压入第一个参数  
	lua_pushlstring(L, (const char*)pInfo, sizeof(AUCTION_BANKER_AUTO));         // 压入第二个参数  
	int iRet= lua_pcall(L, 2, 1, 0);				// 调用函数，调用完成以后，会将返回值压入栈中，2表示参数个数，1表示返回结果个数。  
	if (iRet)										// 调用出错  
	{  
		const char *pErrorMsg = lua_tostring(L, -1);  
		std::cout << pErrorMsg << std::endl;  
		lua_close(L);  
		return 0;  
	}  

	lua_close(L);  

	return 0;
}

int MyClass::TransmitLuaContructWithCallBack(LUA_FUNCTION func)
{
	AUCTION_BANKER_AUTO a;
	a.nChairNO = 123;
	a.nAutoChairNO = 245;

	cocos2d::LuaEngine::getInstance()->getLuaStack()->pushInt(1000);
	cocos2d::LuaEngine::getInstance()->getLuaStack()->pushString("testt");
	
	//结构体要用字符串的形式发过去
	cocos2d::LuaEngine::getInstance()->getLuaStack()->pushString((const char*)&a, sizeof(a));

	//3代表参数个数
	int nRet = cocos2d::LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(func, 3);


	cocos2d::LuaEngine::getInstance()->getLuaStack()->clean();

	return nRet;
}
