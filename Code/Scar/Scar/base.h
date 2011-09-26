/*
** 作者：华亮
** 说明：
**
*/

#ifndef _BASE_H_
#define _BASE_H_

#include <functional>

typedef void* LPVOID;

// 回调函数
typedef std::function< LPVOID( LPVOID ) > IMovableCallBackFuncType;

class IMovable
{
public:
	virtual int Move() = 0;							// 移动
	virtual void AddCallbackFunc( std::function< LPVOID( LPVOID ) > func ) {}
};



#endif