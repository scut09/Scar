/********************************************************************
	����ʱ��: 2011-9-27   15:27
	�ļ���:   IMovable.h
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     

*********************************************************************/


#ifndef IMovable_h__
#define IMovable_h__


#include <functional>

typedef void* LPVOID;

// �ص�����
typedef std::function< LPVOID( LPVOID ) > IMovableCallBackFuncType;

class IMovable
{
public:
	virtual ~IMovable() {}
	virtual int Move() = 0;							// �ƶ�
	virtual void AddCallbackFunc( std::function< LPVOID( LPVOID ) > func ) {}
};






#endif // IMovable_h__