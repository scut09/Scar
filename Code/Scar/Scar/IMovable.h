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


/*
** 名字：IMovable
** 说明：所有可移动物体的抽象基类
**
*/
class IMovable
{
public:
	virtual ~IMovable() {}

	//************************************
	// 函数名:  IMovable::Move
	// 返回值:  int
	// 函数修饰:
	// 描述：   计算位置，处理碰撞等等，都发生在这里面
	//************************************
	virtual int Move() = 0;							

	//************************************
	// 函数名:  IMovable::AddCallbackFunc
	// 返回值:  void
	// 参数:    std::function< LPVOID > func
	// 函数修饰:
	// 描述：   添加每次Move()被调用时都被调用的回调函数
	//************************************
	virtual void AddCallbackFunc( std::function< LPVOID( LPVOID ) > func ) {}
};






#endif // IMovable_h__