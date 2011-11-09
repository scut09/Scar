#include "TranslateUIAnimator.h"
#include "UIImage.h"
#include <iostream>

TranslateUIAnimator::TranslateUIAnimator( u32 begin, u32 duration, const vector2df& offset, bool loop ) :
Begin(begin), Duration(duration), LastTime(begin), Loop(loop), Offset(offset)
{
	OffsetFactor.X = Offset.X / (f32)Duration;
	OffsetFactor.Y = Offset.Y / (f32)Duration;
	Origin = vector2d<f32>( 0.0012f, 0.0013f );
}

bool TranslateUIAnimator::animateUIObject( IUIObject* node, u32 timeMS )
{
	//��δ���ﶯ����ʼʱ��
	if( Begin > timeMS)
		return false;
	
	/*u32 t = timeMS - LastTime;
	LastTime = timeMS;
	vector2d<f32> pos = node->GetPosition();
	node->SetPosition( vector2d<f32>( pos.X + OffsetFactor.X * t, pos.Y + OffsetFactor.Y * t ) );*/

	if ( Origin == vector2d<f32>( 0.0012f, 0.0013f ) )
		Origin = node->GetPosition();

	u32 t = timeMS - Begin;
	vector2d<f32> offset = OffsetFactor * (f32)t;
	if( offset.getLength() > Offset.getLength() )
	{
		offset.X = (f32)Offset.X;
		offset.Y = (f32)Offset.Y;
	}
	node->SetPosition( Origin + offset );

	//���ﶯ������ʱ��
	if( timeMS - Begin > Duration )
	{
		//ѭ��
		if(Loop)
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
