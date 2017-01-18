#include "CCLuaValue.h"

USING_NS_CC;

typedef struct _tagAUCTION_BANKER_AUTO{
	int nUserID;								// 用户ID
	int nRoomID;								// 房间ID
	int nTableNO;								// 桌号
	int nChairNO;								// 位置
	int nAutoChairNO;                           // 自动叫的椅子号
	int nGains;									// 叫分
	int nReserved[4];
}AUCTION_BANKER_AUTO, *LPAUCTION_BANKER_AUTO;

class MyClass: public Ref 
{
public:
  ~MyClass()  {};
  MyClass()   {};

  bool init() { return true; };
  
  CREATE_FUNC(MyClass);

  int foo(int i);

  int TransmitLuaContruct(int nReq, const char* pData, const char* pData2, int nDateLen);

  int TransmitLuaContructWithCallBack(LUA_FUNCTION func);
};