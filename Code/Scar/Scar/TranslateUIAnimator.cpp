#include "TranslateUIAnimator.h"
#include "UIObject.h"

TranslateUIAnimator::TranslateUIAnimator( u32 begin, u32 duration, const vector2d<s32>& offset, bool loop ) :
Begin(begin), Duration(duration), LastTime(begin), Loop(loop), Offset(offset)
{
	OffsetFactor.X = Offset.X / (f32)Duration;
	OffsetFactor.Y = Offset.Y / (f32)Duration;
}

bool TranslateUIAnimator::animateUIObject( IUIObject* node, u32 timeMS )
{
	UIObject* pNode = static_cast< UIObject* >( node );

	for(int i=0; i<4; i++)
		pNode->DstQuar[i] += OffsetFactor;

	return true;
}

TranslateUIAnimator* TranslateUIAnimator::Clone()
{
	return new TranslateUIAnimator(Begin, Duration, Offset, Loop);
}