#include "AlphaChangeUIAnimator.h"
#include "IUIObject.h"

AlphaChangeUIAnimator::AlphaChangeUIAnimator( u32 begin, u32 duration, 
	f32 srcalpha, f32 taralpha, bool loop /*= false */ )
	: Begin( begin ), Duration( duration ), SrcAlpha( srcalpha ),
	TarAlpha(taralpha),Loop( loop ), LastTime( begin )
{
	if(taralpha > 255)
		taralpha = 255;
	else if(taralpha < 0)
		taralpha = 0;
	AlphaFactor = ( (int)taralpha - (int)srcalpha ) / (f32)duration;
}

bool AlphaChangeUIAnimator::animateUIObject( IUIObject* node, u32 timeMS )
{
	//还未达到动画开始时间
	if ( Begin > timeMS )
		return false;
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

	//u32 t = timeMS - LastTime;
	//LastTime = timeMS;

	////AlphaChange
	//f32 alpha = node->GetAlpha() + t * AlphaFactor;	
	//node->SetAlpha( alpha );
	return true;
}

AlphaChangeUIAnimator* AlphaChangeUIAnimator::Clone()
{
	return new AlphaChangeUIAnimator(Begin, Duration, SrcAlpha, TarAlpha, Loop);
}
