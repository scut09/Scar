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

	virtual bool animateUIObject( IUIObject* node, u32 timeMS ) = 0;

	virtual IUIAnimator* Clone() = 0;
};

#endif // UIAnimator_h__
