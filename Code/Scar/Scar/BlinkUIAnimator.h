#ifndef BlinkUIAnimator_h__
#define BlinkUIAnimator_h__

#include "IUIAnimator.h"
using namespace irr::core;

class BlinkUIAnimator;

//////////////////////////////////////////////////////////////////
//���ƣ�BlinkUIAnimator
//������˲�ƶ���
//���ߣ�������
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
