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
	//还未达到动画开始时间
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

	//到达动画结束时间
	if ( timeMS - Begin > Duration )
	{
		//循环
		if ( Loop )
		{
			Begin = timeMS;
		}
		//不循环
		else
		{
			//把自己删掉
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


