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
		//把自己删掉
	}

	u32 t = timeMS - LastTime;
	LastTime = timeMS;

	// Rotate
	f32 angle = t * AngleFactor;

	float steprad = angle / 180 * PI;

	UIObject* pNode = reinterpret_cast< UIObject* >( node );
	//正角度为逆时针
	//记录矩阵四个顶点临时坐标
	vector2d<f32> temQuar[4];
	//得到旋转后的坐标
	for (int i = 0; i < 4; i++)
	{
		temQuar[i] = pNode->DstQuar[i] - RotPoint;
		float x,y;
		x = (float)temQuar[i].X;
		y = (float)temQuar[i].Y;
		temQuar[i].X = cos(steprad) * x - sin(steprad) * y;
		temQuar[i].Y = sin(steprad) * x + cos(steprad) * y;
		//加回到原来的坐标系
		pNode->DstQuar[i] = temQuar[i] + RotPoint;
	}

	return true;
}
