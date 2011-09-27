/********************************************************************
	创建时间: 2011-9-27   15:27
	文件名:   IMovable.h
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     

*********************************************************************/


#ifndef IMovable_h__
#define IMovable_h__


#include <functional>

typedef void* LPVOID;

// 回调函数
typedef std::function< LPVOID( LPVOID ) > IMovableCallBackFuncType;

class IMovable
{
public:
	virtual ~IMovable() {}
	virtual int Move() = 0;							// 移动
	virtual void AddCallbackFunc( std::function< LPVOID( LPVOID ) > func ) {}
};






#endif // IMovable_h__