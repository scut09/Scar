#include "RotateUIAnimator.h"
#include "UIImage.h"

RotateUIAnimator::RotateUIAnimator( u32 begin, u32 duration, f32 angle, bool loop /*= false */ ) : Begin( begin ), 
	Duration( duration ), Loop( loop ), LastTime( begin ), Angle(angle)
{
	AngleFactor = angle / Duration;
	Origin = 0.0013f;
}

bool RotateUIAnimator::animateUIObject( IUIObject* node, u32 timeMS )
{
	//��δ���ﶯ����ʼʱ��
	if( Begin > timeMS)
		return false;
	
	/*u32 t = timeMS - LastTime;
	LastTime = timeMS;
	node->SetRotation( node->GetRotation() + AngleFactor * t );*/

	if( Origin == 0.0013f )
		Origin = node->GetRotation();

	u32 t = timeMS - Begin;
	f32 ang = AngleFactor * (f32)t;
	if ( abs(ang) > abs(Angle) ) ang = Angle;
	node->SetRotation( Origin + ang );

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

RotateUIAnimator* RotateUIAnimator::Clone()
{
	return new RotateUIAnimator(Begin, Duration, Angle, Loop);
}

RotateUIAnimator::~RotateUIAnimator()
{
	DESTRUCTION_PRINT("RotateUIAnimator");
}
