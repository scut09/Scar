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
	//还未到达动画开始时间
	if( Begin > timeMS)
		return false;
	//到达动画结束时间
	if( timeMS - Begin > Duration )
	{
		//循环
		if(Loop)
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

	// Rotate
	f32 angle = t * AngleFactor;
	float steprad = angle / 180 * PI;

	UIObject* pNode = static_cast< UIObject* >( node );
	RotPoint += (pNode->GetCenter() - OldObjCen);
	

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

	OldObjCen = pNode->GetCenter();

	return true;
}

RotateUIAnimator* RotateUIAnimator::Clone()
{
	return new RotateUIAnimator(Begin, Duration, Angle, RotPoint, OldObjCen, Loop);
}
