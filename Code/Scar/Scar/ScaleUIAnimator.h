#ifndef ScaleUIAnimator_h__
#define ScaleUIAnimator_h__

#include "IUIAnimator.h"
using namespace irr::core;

class RotateUIAnimator;

//////////////////////////////////////////////////////////////////
//���ƣ�ScaleUIAnimator
//���������Ŷ���
//���ߣ������裬�����
//////////////////////////////////////////////////////////////////
class ScaleUIAnimator : public IUIAnimator
{
private:
	u32 Begin;
	u32 Duration;
	u32 LastTime;
	vector2d<f32> Scale;
	vector2d<f32> ScaleFactor;
	vector2d<f32> Origin;
	bool Loop;
	bool IsFirst;

public:
	ScaleUIAnimator( u32 begin, u32 duration, vector2d<f32> scale, bool loop = false );
	~ScaleUIAnimator();

	virtual bool animateUIObject( IUIObject* node, u32 timeMS );

	virtual ScaleUIAnimator* Clone();
};

#endif // ScaleUIAnimator_h__
