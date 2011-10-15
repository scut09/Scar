#include "BlinkUIAnimator.h"
#include "UIObject.h"

BlinkUIAnimator::BlinkUIAnimator( const vector2d<f32>& offset )
{
	Offset = offset;
}

bool BlinkUIAnimator::animateUIObject( IUIObject* node, u32 timeMS )
{
	node->TransM(2,0) += Offset.X;
	node->TransM(2,1) += Offset.Y;
	return true;
}

BlinkUIAnimator* BlinkUIAnimator::Clone()
{
	return new BlinkUIAnimator(Offset);
}
