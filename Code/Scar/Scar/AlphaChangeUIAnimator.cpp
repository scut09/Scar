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
