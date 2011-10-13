#include "ScaleUIAnimator.h"
#include "UIObject.h"

ScaleUIAnimator::ScaleUIAnimator( u32 begin, u32 duration, vector2d<f32> scale, const vector2d<f32>& scapoint, bool loop /*= false */ )
	: Begin( begin ), Duration( duration ), Scale( scale ), ScaPoint( scapoint ), Loop( loop ), LastTime( begin )
{
	ScaleFactor.X = ( scale.X - 1 ) / duration;
	ScaleFactor.Y = ( scale.Y - 1 ) / duration;
}

bool ScaleUIAnimator::animateUIObject( IUIObject* node, u32 timeMS )
{
	//��δ�ﵽ������ʼʱ��
	if( Begin > timeMS )
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

	//Scale
	vector2d<f32> scale = t * ScaleFactor + 1;

	UIObject* pNode = static_cast< UIObject* >( node );

	//��¼�����ĸ�������ʱ����
	vector2d<f32> temQuar[4];
	//�õ�����������
	for ( int i = 0 ; i < 4; i++)
	{
		temQuar[i] = pNode->DstQuar[i] - ScaPoint;
		temQuar[i].X *= scale.X;
		temQuar[i].Y *= scale.Y;
		//�ӻص�ԭ��������ϵ
		pNode->DstQuar[i] = temQuar[i] + ScaPoint;
	}
	return true;
}

ScaleUIAnimator* ScaleUIAnimator::Clone()
{
	return new ScaleUIAnimator(Begin, Duration, Scale, ScaPoint, Loop);
}
