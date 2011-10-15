#ifndef BlinkUIAnimator_h__
#define BlinkUIAnimator_h__

#include "IUIAnimator.h"
using namespace irr::core;

class BlinkUIAnimator;

//////////////////////////////////////////////////////////////////
//名称：BlinkUIAnimator
//描述：瞬移动画
//作者：屠文翔
//////////////////////////////////////////////////////////////////
class BlinkUIAnimator : public IUIAnimator
{
	vector2d<f32> Offset;
public:
	BlinkUIAnimator( const vector2d<f32>& offset);

	virtual bool animateUIObject( IUIObject* node, u32 timeMS );

	virtual BlinkUIAnimator* Clone();
};

#endif // BlinkUIAnimator_h__
