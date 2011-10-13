#include "AlphaChangeUIAnimator.h"
#include "UIObject.h"

AlphaChangeUIAnimator::AlphaChangeUIAnimator( u32 begin, u32 duration, 
	unsigned int srcalpha, unsigned int taralpha, bool loop /*= false */ )
	: Begin( begin ), Duration( duration ), SrcAlpha( srcalpha ),
	TarAlpha(taralpha),Loop( loop ), LastTime( begin )
{
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

	u32 t = timeMS - LastTime;
	LastTime = timeMS;

	//AlphaChange
	unsigned int alpha = (u32)(SrcAlpha + t * AlphaFactor);
	
	UIObject* pNode = static_cast< UIObject* >( node );
	
	pNode->SetAlpha( SrcAlpha = alpha );
	return true;
}

AlphaChangeUIAnimator* AlphaChangeUIAnimator::Clone()
{
	return new AlphaChangeUIAnimator(Begin, Duration, SrcAlpha, TarAlpha, Loop);
}
