#ifndef RotateUIAnimator_h__
#define RotateUIAnimator_h__

#include "IUIAnimator.h"
using namespace irr::core;

class RotateUIAnimator;

//////////////////////////////////////////////////////////////////
//名称：RotateUIAnimator
//描述：旋转动画
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////
class RotateUIAnimator : public IUIAnimator
{
private:
	u32 Begin;
	u32 Duration;
	f32 Angle;
	f32 AngleFactor;
	u32 LastTime;
	vector2d<f32> RotPoint;
	bool Loop;

public:
	RotateUIAnimator( u32 begin, u32 duration, f32 angle, 
		const vector2d<f32>& rotpoint, bool loop = false );
	
	virtual bool animateUIObject( IUIObject* node, u32 timeMS );

	virtual RotateUIAnimator* Clone();

};

#endif // RotateUIAnimator_h__
