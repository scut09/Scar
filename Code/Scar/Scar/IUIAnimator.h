/********************************************************************
    创建时间: 2011-10-13   14:38
    文件名:   IUIAnimator.h
    作者:     华亮 屠文翔
    说明:     2D动画接口，如果需要创建自己的动画，我们只需要实现IUIAnimator接口，
			便可以为2D场景节点添加自己的动画。

*********************************************************************/


#ifndef UIAnimator_h__
#define UIAnimator_h__

#include <irrlicht.h>
using namespace irr;

class IUIObject;

//////////////////////////////////////////////////////////////////
//名称：IUIAnimator
//描述：动画的接口类，所有的动画均派生自此类
//作者：华亮
//////////////////////////////////////////////////////////////////
class IUIAnimator : public irr::IReferenceCounted
{
public:
	virtual ~IUIAnimator() {}

	//************************************
	// 函数名:  IUIAnimator::animateUIObject
	// 返回值:  bool
	// 参数:    IUIObject * node		输入被动画作用的2D节点
	// 参数:    u32 timeMS			输入当前的虚拟时间，
	//								时间由video::IVideoDriver::GetTimer()->GetTime()提供
	// 函数修饰:
	// 描述：   当IUIObject被调用OnAnimate()时，
	//			IUIObject会调用所有注册到里面的IUIAnimator的animateUIObject( this, timeMS )。
	//************************************
	virtual bool animateUIObject( IUIObject* node, u32 timeMS ) = 0;

	virtual IUIAnimator* Clone() = 0;
};

#endif // UIAnimator_h__
