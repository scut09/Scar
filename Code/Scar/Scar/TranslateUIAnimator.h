#ifndef TranslateUIAnimator_h__
#define TranslateUIAnimator_h__

#include "IUIAnimator.h"

using namespace irr::core;

class RotateUIAnimator;

//////////////////////////////////////////////////////////////////
//���ƣ�TranslateUIAnimator
//��������ת����
//���ߣ������裬�����
//////////////////////////////////////////////////////////////////
class TranslateUIAnimator : public IUIAnimator
{
public:
	TranslateUIAnimator( u32 begin, u32 duration, const vector2d<s32>& offset, bool loop = false );

	virtual bool animateUIObject( IUIObject* node, u32 timeMS );

	virtual TranslateUIAnimator* Clone();

private:
	u32 LastTime;
	u32 Begin;
	u32 Duration;
	vector2d<f32> OffsetFactor;
	vector2d<s32> Offset;
	bool Loop;
	
};

#endif // TranslateUIAnimator_h__
