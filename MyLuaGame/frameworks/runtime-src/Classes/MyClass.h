#include "CCLuaValue.h"

USING_NS_CC;

typedef struct _tagAUCTION_BANKER_AUTO{
	int nUserID;								// �û�ID
	int nRoomID;								// ����ID
	int nTableNO;								// ����
	int nChairNO;								// λ��
	int nAutoChairNO;                           // �Զ��е����Ӻ�
	int nGains;									// �з�
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