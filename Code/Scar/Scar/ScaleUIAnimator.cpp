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
	//还未达到动画开始时间
	if( Begin > timeMS )
		return false;
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

	u32 t = timeMS - LastTime;
	LastTime = timeMS;

	//Scale
	vector2d<f32> scale = t * ScaleFactor + 1;

	UIObject* pNode = static_cast< UIObject* >( node );

	//记录矩阵四个顶点临时坐标
	vector2d<f32> temQuar[4];
	//得到拉伸后的坐标
	for ( int i = 0 ; i < 4; i++)
	{
		temQuar[i] = pNode->DstQuar[i] - ScaPoint;
		temQuar[i].X *= scale.X;
		temQuar[i].Y *= scale.Y;
		//加回到原来的坐标系
		pNode->DstQuar[i] = temQuar[i] + ScaPoint;
	}
	return true;
}

ScaleUIAnimator* ScaleUIAnimator::Clone()
{
	return new ScaleUIAnimator(Begin, Duration, Scale, ScaPoint, Loop);
}
