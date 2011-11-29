#include "TranslateUIAnimator.h"
#include "UIImage.h"
#include <iostream>

TranslateUIAnimator::TranslateUIAnimator( u32 begin, u32 duration, const vector2df& offset, bool loop ) :
Begin(begin), Duration(duration), LastTime(begin), Loop(loop), Offset(offset), IsFirst( true )
{
	Type = 1;
	OffsetFactor.X = Offset.X / (f32)Duration;
	OffsetFactor.Y = Offset.Y / (f32)Duration;
}

TranslateUIAnimator::TranslateUIAnimator( u32 delay, u32 duration, const vector2df& from, const vector2df& to, bool loop /*= false */ )
	: Begin( delay ), Duration( duration ), Origin( from ), Offset( to - from ), Loop( loop ), IsFirst( true )
{
	Type = 2;
	OffsetFactor.X = Offset.X / (f32)Duration;
	OffsetFactor.Y = Offset.Y / (f32)Duration;
}

bool TranslateUIAnimator::animateUIObject( IUIObject* node, u32 timeMS )
{	
	if( IsFirst )
	{
		if ( Type == 1 )
			Origin = node->GetPosition();
		Begin = timeMS + Begin;
		IsFirst = false;
	}

	//还未到达动画开始时间
	if( Begin > timeMS)
		return false;

	u32 t = timeMS - Begin;
	vector2d<f32> offset = OffsetFactor * (f32)t;
	if( offset.getLength() > Offset.getLength() )
	{
		offset.X = (f32)Offset.X;
		offset.Y = (f32)Offset.Y;
	}
	node->SetPosition( Origin + offset );

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

	return true;
}

TranslateUIAnimator* TranslateUIAnimator::Clone()
{
	return new TranslateUIAnimator(Begin, Duration, Offset, Loop);
}

TranslateUIAnimator::~TranslateUIAnimator()
{
	DESTRUCTION_PRINT("TranslateUIAnimator");
}
