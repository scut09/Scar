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
	//��δ�ﵽ������ʼʱ��
	if ( Begin > timeMS )
		return false;
	//���ﶯ������ʱ��
	if ( timeMS - Begin > Duration )
	{
		//ѭ��
		if ( Loop )
		{
			Begin = timeMS;
		} 
		//��ѭ��
		else
		{
			//���Լ�ɾ��
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
