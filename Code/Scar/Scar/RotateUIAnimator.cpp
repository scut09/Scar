#include "RotateUIAnimator.h"
#include "UIImage.h"

RotateUIAnimator::RotateUIAnimator( u32 begin, u32 duration, f32 angle, bool loop /*= false */ ) : Begin( begin ), 
	Duration( duration ), Loop( loop ), LastTime( begin ), Angle(angle)
{
	AngleFactor = angle / Duration;
}

bool RotateUIAnimator::animateUIObject( IUIObject* node, u32 timeMS )
{
	//��δ���ﶯ����ʼʱ��
	if( Begin > timeMS)
		return false;
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
			//historyM *= 
			//���Լ�ɾ��
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
