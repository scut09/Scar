/*
** ���ߣ�����
** ˵����
**
*/

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