#ifndef MySceneNodeAnimatorCallFunc_h__
#define MySceneNodeAnimatorCallFunc_h__

/********************************************************************
	创建日期:	2011/10/23
	文件名: 	C:\Users\Administrator\Desktop\工作\SCAR项目组\opengl-scut\Code\Scar\Scar\MySceneNodeAnimatorCallFunc.h
	作者:		屠文翔
	
	描述:		设定延迟一段时间之后调用另一个函数
				使用SetCallBack来设置回调函数
				用法为
				funcAni->SetCallback( []()
				{
					//此处写函数体
				});
*********************************************************************/

#include "ISceneNode.h"
#include <functional>

using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class MySceneNodeAnimatorCallFunc : public ISceneNodeAnimator
{
	typedef std::function< void() >	FuncCallbackType;

	u32 Begin;
	u32 Delay;
	u32 Duration;	

	FuncCallbackType	Func;

public:
	MySceneNodeAnimatorCallFunc( u32 delay, u32 duration );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );

	void SetCallback( FuncCallbackType func )
	{
		Func = func;
	}

};

#endif // MySceneNodeAnimatorCallFunc_h__
