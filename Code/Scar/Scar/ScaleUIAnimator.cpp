#include "ScaleUIAnimator.h"
#include "UIObject.h"

ScaleUIAnimator::ScaleUIAnimator( u32 begin, u32 duration, vector2d<f32> scale, const vector2d<f32>& scapoint, bool loop /*= false */ )
	: Begin( begin ), Duration( duration ), Scale( scale ), ScaPoint( scapoint ), Loop( loop ), LastTime( begin )
{
	ScaleFactor.X = ( scale.X - 1 ) / duration;
	ScaleFactor.Y = ( scale.Y - 1 ) / duration;
	ScaleSet = false;
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

	//IUIObject* pNode = static_cast< IUIObject* >( node );

	//if (! ScaleSet )
	//{
	//	for ( int i = 0; i < 4; i++ )
	//		ScaleVector[i] = node->DstQuar[i] - ScaPoint;
	//	ScaleSet = true;
	//}
	//u32 t = timeMS - LastTime;
	//LastTime = timeMS;

	////Scale
	//vector2d<f32> scale = ScaleFactor * (f32)t ;



	//ScaPoint += ( node->GetCenter() - OldObjCen ) * ( scale + vector2d<f32> ( 1,1 ));
	//OldObjCen = node->GetCenter();

	////��¼�����ĸ�������ʱ����
	//vector2d<f32> temQuar;
	////�õ�����������
	//for ( int i = 0 ; i < 4; i++)
	//{
	//	temQuar = node->DstQuar[i] - ScaPoint;
	//	temQuar += ScaleVector[i] * scale;
	//	//�ӻص�ԭ��������ϵ
	//	node->DstQuar[i] = temQuar + ScaPoint /** ( scale + vector2d<f32> ( 1,1 ))*/;
	//}
	//
	//
	
	return true;

}

ScaleUIAnimator* ScaleUIAnimator::Clone()
{
	return new ScaleUIAnimator(Begin, Duration, Scale, ScaPoint, Loop);
}


