#include "AlphaChangeUIAnimator.h"
#include "IUIObject.h"

AlphaChangeUIAnimator::AlphaChangeUIAnimator( u32 delay, u32 duration, 
	f32 srcalpha, f32 taralpha, bool loop /*= false */ )
	: Delay( delay ), Duration( duration ), SrcAlpha( srcalpha ),
	TarAlpha(taralpha),Loop( loop ), First( true )
{
	if(taralpha > 255)
		taralpha = 255;
	else if(taralpha < 0)
		taralpha = 0;
	AlphaFactor = ( taralpha - srcalpha ) / (f32)duration;
}

bool AlphaChangeUIAnimator::animateUIObject( IUIObject* node, u32 timeMS )
{
	if ( First )
	{
		First = false;
		Begin = Delay + timeMS;
	}
	//还未达到动画开始时间
	if ( Begin > timeMS )
		return false;
	
	/*u32 t = timeMS - LastTime;
	LastTime = timeMS;*/
	u32 t = timeMS - Begin;
	f32 alpha = SrcAlpha + AlphaFactor * (f32)t;
	if( alpha > 255 ) alpha = 255;
	else if ( alpha < 0 ) alpha = 0;
	node->SetAlpha( alpha );

	//到达动画结束时间
	if ( timeMS - Begin > Duration )
	{
		//循环
		if ( Loop )
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

AlphaChangeUIAnimator* AlphaChangeUIAnimator::Clone()
{
	return new AlphaChangeUIAnimator(Begin, Duration, SrcAlpha, TarAlpha, Loop);
}

AlphaChangeUIAnimator::~AlphaChangeUIAnimator()
{
	DESTRUCTION_PRINT("AlphaChangeUIAnimator");
}
