#include "RotateUIAnimator.h"
#include "UIObject.h"

RotateUIAnimator::RotateUIAnimator( u32 begin, u32 duration, f32 angle, const vector2d<f32>& rotpoint, bool loop /*= false */ ) : Begin( begin ), Duration( duration ),
	RotPoint( rotpoint ), Loop( loop ), LastTime( begin )
{
	AngleFactor = angle / Duration;
}

bool RotateUIAnimator::animateUIObject( IUIObject* node, u32 timeMS )
{
	if( timeMS - Begin > Duration )
	{
		//���Լ�ɾ��
	}

	u32 t = timeMS - LastTime;
	LastTime = timeMS;

	// Rotate
	f32 angle = t * AngleFactor;

	float steprad = angle / 180 * PI;

	UIObject* pNode = reinterpret_cast< UIObject* >( node );
	//���Ƕ�Ϊ��ʱ��
	//��¼�����ĸ�������ʱ����
	vector2d<f32> temQuar[4];
	//�õ���ת�������
	for (int i = 0; i < 4; i++)
	{
		temQuar[i] = pNode->DstQuar[i] - RotPoint;
		float x,y;
		x = (float)temQuar[i].X;
		y = (float)temQuar[i].Y;
		temQuar[i].X = cos(steprad) * x - sin(steprad) * y;
		temQuar[i].Y = sin(steprad) * x + cos(steprad) * y;
		//�ӻص�ԭ��������ϵ
		pNode->DstQuar[i] = temQuar[i] + RotPoint;
	}

	return true;
}
