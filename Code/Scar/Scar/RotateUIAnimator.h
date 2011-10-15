#ifndef RotateUIAnimator_h__
#define RotateUIAnimator_h__

#include "IUIAnimator.h"
using namespace irr::core;

class RotateUIAnimator;

//////////////////////////////////////////////////////////////////
//���ƣ�RotateUIAnimator
//��������ת����
//���ߣ������裬�����
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
