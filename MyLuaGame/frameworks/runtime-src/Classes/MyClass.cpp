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
	//1. ����Lua�������Ľṹ��
	auto engine = LuaEngine::getInstance();
	lua_State* L = engine->getLuaStack()->getLuaState();

	int n1 = lua_tointeger(L, -1);
	int n3 = lua_tointeger(L, -4);
	const char* pDst = lua_tostring(L, -2);		// ��L��ջ��ȡ������
	const char* pDst1 = lua_tostring(L, -3);
	AUCTION_BANKER_AUTO* pInfo = (AUCTION_BANKER_AUTO*)pDst;
	AUCTION_BANKER_AUTO* pInfo1 = (AUCTION_BANKER_AUTO*)pDst1;
	int a = pInfo->nAutoChairNO;
	int b = pInfo->nChairNO;

	memset(pInfo, 0x0, sizeof(AUCTION_BANKER_AUTO));

	//2.����Lua�㺯�� 
	lua_getglobal(L, "LuaFunc");					// ��ȡ������ѹ��ջ��  

	lua_pushinteger(L, a);							// ѹ���һ������  
	lua_pushlstring(L, (const char*)pInfo, sizeof(AUCTION_BANKER_AUTO));         // ѹ��ڶ�������  
	int iRet= lua_pcall(L, 2, 1, 0);				// ���ú�������������Ժ󣬻Ὣ����ֵѹ��ջ�У�2��ʾ����������1��ʾ���ؽ��������  
	if (iRet)										// ���ó���  
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
	
	//�ṹ��Ҫ���ַ�������ʽ����ȥ
	cocos2d::LuaEngine::getInstance()->getLuaStack()->pushString((const char*)&a, sizeof(a));

	//3�����������
	int nRet = cocos2d::LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(func, 3);


	cocos2d::LuaEngine::getInstance()->getLuaStack()->clean();

	return nRet;
}
