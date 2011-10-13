#ifndef ScaleUIAnimator_h__
#define ScaleUIAnimator_h__

#include "IUIAnimator.h"
using namespace irr::core;

class RotateUIAnimator;

//////////////////////////////////////////////////////////////////
//名称：ScaleUIAnimator
//描述：缩放动画
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////
class ScaleUIAnimator : public IUIAnimator
{
private:
	u32 Begin;
	u32 Duration;
	u32 LastTime;
	vector2d<f32> Scale;
	vector2d<f32> ScaleFactor;
	vector2d<f32> ScaPoint;
	bool Loop;

public:
	ScaleUIAnimator( u32 begin, u32 duration, vector2d<f32> scale,
		const vector2d<f32>& scapoint, bool loop = false );

	virtual bool animateUIObject( IUIObject* node, u32 timeMS );

	virtual ScaleUIAnimator* Clone();
};

#endif // ScaleUIAnimator_h__
