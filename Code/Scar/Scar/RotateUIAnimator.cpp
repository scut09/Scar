#include "RotateUIAnimator.h"
#include "UIObject.h"

RotateUIAnimator::RotateUIAnimator( u32 begin, u32 duration, f32 angle, const vector2d<f32>& rotpoint, const vector2d<f32>& ObjCen, bool loop /*= false */ ) : Begin( begin ), Duration( duration ),
	RotPoint( rotpoint ), Loop( loop ), LastTime( begin ), Angle(angle)
{
	OldObjCen = ObjCen;
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
			//���Լ�ɾ��
			node->RemoveAnimator(this);
			return false;
		}
	}
	u32 t = timeMS - LastTime;
	LastTime = timeMS;

	// Rotate
	f32 angle = t * AngleFactor;
	float steprad = angle / 180 * PI;

	//IUIObject* pNode = static_cast< IUIObject* >( node );
	RotPoint += (node->GetCenter() - OldObjCen);
	

	//���Ƕ�Ϊ��ʱ��
	//��¼�����ĸ�������ʱ����
	vector2d<f32> temQuar;
	//�õ���ת�������
	for (int i = 0; i < 4; i++)
	{
		temQuar = node->DstQuar[i] - RotPoint;
		float x,y;
		x = (float)temQuar.X;
		y = (float)temQuar.Y;
		temQuar.X = cos(steprad) * x - sin(steprad) * y;
		temQuar.Y = sin(steprad) * x + cos(steprad) * y;
		//�ӻص�ԭ��������ϵ
		node->DstQuar[i] = temQuar + RotPoint;
	}

	OldObjCen = node->GetCenter();

	return true;
}

RotateUIAnimator* RotateUIAnimator::Clone()
{
	return new RotateUIAnimator(Begin, Duration, Angle, RotPoint, OldObjCen, Loop);
}
