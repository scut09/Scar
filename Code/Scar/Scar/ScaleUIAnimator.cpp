#include "ScaleUIAnimator.h"
#include "UIImage.h"

ScaleUIAnimator::ScaleUIAnimator( u32 begin, u32 duration, vector2d<f32> scale, bool loop /*= false */ )
	: Begin( begin ), Duration( duration ), Scale( scale ), Loop( loop ), LastTime( begin )
{
	ScaleFactor.X = ( scale.X - 1 ) / duration;
	ScaleFactor.Y = ( scale.Y - 1 ) / duration;
	Origin = vector2d<f32>( 0.0012f, 0.0013f );
}

bool ScaleUIAnimator::animateUIObject( IUIObject* node, u32 timeMS )
{
	//��δ�ﵽ������ʼʱ��
	if( Begin > timeMS )
		return false;
	
	/*u32 t = timeMS - LastTime;
	LastTime = timeMS;
	node->SetScale( node->GetScale() + ScaleFactor * (f32)t );*/

	if( Origin == vector2d<f32>( 0.0012f, 0.0013f ) )
		Origin = node->GetScale();

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


