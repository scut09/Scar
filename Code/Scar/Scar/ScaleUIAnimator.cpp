#include "ScaleUIAnimator.h"
#include "UIImage.h"

ScaleUIAnimator::ScaleUIAnimator( u32 begin, u32 duration, vector2d<f32> scale, bool loop /*= false */ )
	: Begin( begin ), Duration( duration ), Scale( scale ), Loop( loop ), LastTime( begin ), IsFirst( true )
{
	ScaleFactor.X = ( scale.X - 1 ) / duration;
	ScaleFactor.Y = ( scale.Y - 1 ) / duration;
}

bool ScaleUIAnimator::animateUIObject( IUIObject* node, u32 timeMS )
{
	if( IsFirst )
	{
		Origin = node->GetScale();
		Begin = timeMS + Begin;
		IsFirst = false;
	}

	//��δ�ﵽ������ʼʱ��
	if( Begin > timeMS )
		return false;

	u32 t = timeMS - Begin;
	vector2d<f32> sca = ScaleFactor * (f32)t;
	if( sca.getLength() > Scale.getLength() )
		sca = Scale;
	node->SetScale( Origin + sca );

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

	return true;
}

ScaleUIAnimator* ScaleUIAnimator::Clone()
{
	return new ScaleUIAnimator(Begin, Duration, Scale, Loop);
}

ScaleUIAnimator::~ScaleUIAnimator()
{
	DESTRUCTION_PRINT("ScaleUIAnimator");
}


