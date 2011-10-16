#include "TranslateUIAnimator.h"
#include "UIImage.h"

TranslateUIAnimator::TranslateUIAnimator( u32 begin, u32 duration, const vector2d<s32>& offset, bool loop ) :
Begin(begin), Duration(duration), LastTime(begin), Loop(loop), Offset(offset)
{
	OffsetFactor.X = Offset.X / (f32)Duration;
	OffsetFactor.Y = Offset.Y / (f32)Duration;
}

bool TranslateUIAnimator::animateUIObject( IUIObject* node, u32 timeMS )
{
	//还未到达动画开始时间
	if( Begin > timeMS)
		return false;
	//到达动画结束时间
	if( timeMS - Begin > Duration )
	{
		//循环
		if(Loop)
		{
			Begin = timeMS;
		}
		//不循环
		else
		{
			//把自己删掉
			node->RemoveAnimator(this);
			return false;
		}
	}
	u32 t = timeMS - LastTime;
	LastTime = timeMS;

	vector2d<f32> pos = node->GetPosition();
	node->SetPosition( vector2d<f32>( pos.X + OffsetFactor.X * t, pos.Y + OffsetFactor.Y * t ) );

	return true;
}

TranslateUIAnimator* TranslateUIAnimator::Clone()
{
	return new TranslateUIAnimator(Begin, Duration, Offset, Loop);
}
