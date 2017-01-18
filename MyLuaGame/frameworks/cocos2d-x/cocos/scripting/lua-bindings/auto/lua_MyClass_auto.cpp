#include "lua_MyClass_auto.hpp"
#include "MyClass.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_MyClass_MyClass_init(lua_State* tolua_S)
{
    int argc = 0;
    MyClass* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MyClass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MyClass*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_MyClass_MyClass_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_MyClass_MyClass_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MyClass:init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_MyClass_MyClass_init'.",&tolua_err);
#endif

    return 0;
}
int lua_MyClass_MyClass_foo(lua_State* tolua_S)
{
    int argc = 0;
    MyClass* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MyClass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MyClass*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_MyClass_MyClass_foo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MyClass:foo");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_MyClass_MyClass_foo'", nullptr);
            return 0;
        }
        int ret = cobj->foo(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MyClass:foo",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_MyClass_MyClass_foo'.",&tolua_err);
#endif

    return 0;
}
int lua_MyClass_MyClass_TransmitLuaContructWithCallBack(lua_State* tolua_S)
{
    int argc = 0;
    MyClass* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MyClass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MyClass*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_MyClass_MyClass_TransmitLuaContructWithCallBack'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
//         int arg0;
// 
// 		ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MyClass:TransmitLuaContructWithCallBack");
// 		if(!ok)
// 		{
// 			tolua_error(tolua_S,"invalid arguments in function 'lua_MyClass_MyClass_TransmitLuaContructWithCallBack'", nullptr);
// 			return 0;
// 		}
// 		int ret = cobj->TransmitLuaContructWithCallBack(arg0);
// 		tolua_pushnumber(tolua_S,(lua_Number)ret);
// 		return 1;

#if COCOS2D_DEBUG >= 1 
		if (!toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err))
			goto tolua_lerror;
#endif
		LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 2, 0);
		int ret = cobj->TransmitLuaContructWithCallBack(handler);
		tolua_pushnumber(tolua_S, (lua_Number)ret);
		return 1;
	}
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MyClass:TransmitLuaContructWithCallBack",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_MyClass_MyClass_TransmitLuaContructWithCallBack'.",&tolua_err);
#endif

    return 0;
}
int lua_MyClass_MyClass_TransmitLuaContruct(lua_State* tolua_S)
{
    int argc = 0;
    MyClass* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"MyClass",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (MyClass*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_MyClass_MyClass_TransmitLuaContruct'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        int arg0;
        const char* arg1;
        const char* arg2;
        int arg3;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "MyClass:TransmitLuaContruct");

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "MyClass:TransmitLuaContruct"); arg1 = arg1_tmp.c_str();

        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "MyClass:TransmitLuaContruct"); arg2 = arg2_tmp.c_str();

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "MyClass:TransmitLuaContruct");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_MyClass_MyClass_TransmitLuaContruct'", nullptr);
            return 0;
        }
        int ret = cobj->TransmitLuaContruct(arg0, arg1, arg2, arg3);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MyClass:TransmitLuaContruct",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_MyClass_MyClass_TransmitLuaContruct'.",&tolua_err);
#endif

    return 0;
}
int lua_MyClass_MyClass_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"MyClass",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_MyClass_MyClass_create'", nullptr);
            return 0;
        }
        MyClass* ret = MyClass::create();
        object_to_luaval<MyClass>(tolua_S, "MyClass",(MyClass*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "MyClass:create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_MyClass_MyClass_create'.",&tolua_err);
#endif
    return 0;
}
int lua_MyClass_MyClass_constructor(lua_State* tolua_S)
{
    int argc = 0;
    MyClass* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_MyClass_MyClass_constructor'", nullptr);
            return 0;
        }
        cobj = new MyClass();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"MyClass");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "MyClass:MyClass",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_MyClass_MyClass_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_MyClass_MyClass_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (MyClass)");
    return 0;
}

int lua_register_MyClass_MyClass(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"MyClass");
    tolua_cclass(tolua_S,"MyClass","MyClass","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"MyClass");
        tolua_function(tolua_S,"new",lua_MyClass_MyClass_constructor);
        tolua_function(tolua_S,"init",lua_MyClass_MyClass_init);
        tolua_function(tolua_S,"foo",lua_MyClass_MyClass_foo);
        tolua_function(tolua_S,"TransmitLuaContructWithCallBack",lua_MyClass_MyClass_TransmitLuaContructWithCallBack);
        tolua_function(tolua_S,"TransmitLuaContruct",lua_MyClass_MyClass_TransmitLuaContruct);
        tolua_function(tolua_S,"create", lua_MyClass_MyClass_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(MyClass).name();
    g_luaType[typeName] = "MyClass";
    g_typeCast["MyClass"] = "MyClass";
    return 1;
}
TOLUA_API int register_all_MyClass(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_MyClass_MyClass(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

