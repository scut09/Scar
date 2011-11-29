#include "RotateUIAnimator.h"
#include "UIImage.h"

RotateUIAnimator::RotateUIAnimator( u32 begin, u32 duration, f32 angle, bool loop /*= false */ ) : Begin( begin ), 
	Duration( duration ), Loop( loop ), LastTime( begin ), Angle(angle), IsFirst( true )
{
	AngleFactor = angle / Duration;
}

bool RotateUIAnimator::animateUIObject( IUIObject* node, u32 timeMS )
{	

	if( IsFirst )
	{
		Origin = node->GetRotation();
		Begin = timeMS + Begin;
		IsFirst = false;
	}

	//��δ���ﶯ����ʼʱ��
	if( Begin > timeMS)
		return false;

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
			node->SetRotation( Origin + ang );
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
