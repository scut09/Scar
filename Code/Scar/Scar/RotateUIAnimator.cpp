#include "RotateUIAnimator.h"
#include "UIImage.h"

RotateUIAnimator::RotateUIAnimator( u32 begin, u32 duration, f32 angle, bool loop /*= false */ ) : Begin( begin ), 
	Duration( duration ), Loop( loop ), LastTime( begin ), Angle(angle)
{
	AngleFactor = angle / Duration;
}

bool RotateUIAnimator::animateUIObject( IUIObject* node, u32 timeMS )
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
			//historyM *= 
			//把自己删掉
			node->RemoveAnimator(this);
			return false;
		}
	}
	u32 t = timeMS - LastTime;
	LastTime = timeMS;

	node->SetRotation( node->GetRotation() + AngleFactor * t );

	return true;
}

RotateUIAnimator* RotateUIAnimator::Clone()
{
	return new RotateUIAnimator(Begin, Duration, Angle, Loop);
}
