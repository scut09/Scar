/********************************************************************
	����ʱ��: 2011-9-27   14:56
	�ļ���:   base.h
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     

*********************************************************************/

#ifndef _BASE_H_
#define _BASE_H_

#include <functional>

typedef void* LPVOID;

// �ص�����
typedef std::function< LPVOID( LPVOID ) > IMovableCallBackFuncType;

class IMovable
{
public:
	virtual int Move() = 0;							// �ƶ�
	virtual void AddCallbackFunc( std::function< LPVOID( LPVOID ) > func ) {}
};



#endif