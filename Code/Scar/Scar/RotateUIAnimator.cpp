#include "RotateUIAnimator.h"
#include "UIObject.h"

RotateUIAnimator::RotateUIAnimator( u32 begin, u32 duration, f32 angle, const vector2d<f32>& rotpoint, bool loop /*= false */ ) : Begin( begin ), 
	Duration( duration ), RotPoint( rotpoint ), Loop( loop ), LastTime( begin ), Angle(angle)
{
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
			//historyM *= 
			//把自己删掉
			node->RemoveAnimator(this);
			return false;
		}
	}
	u32 t = timeMS - LastTime;
	LastTime = timeMS;
	//计算新的旋转中心
	ub::vector<f32> tmp(3);
	tmp(0) = RotPoint.X;	tmp(1) = RotPoint.Y; tmp(2) = 1;
	tmp = prod(tmp, node->TransM);
	vector2d<f32> newRotPoint(tmp(0), tmp(1));
	// Rotate
	f32 angle = t * AngleFactor;
	float rad = angle / 180 * PI;
	vector2d<f32> offset = newRotPoint - node->DstQuar[0];
	//创建平移矩阵（移来移去)
	matrix<f32> inmat(3,3);
	inmat.clear();
	inmat(0,0) = inmat(1,1) = inmat(2,2) = 1;
	inmat(2,0) = -offset.X;	inmat(2,1) = -offset.Y;
	matrix<f32> outmat(3,3);
	outmat.clear();
	outmat(0,0) = outmat(1,1) = outmat(2,2) = 1;
	outmat(2,0) = offset.X;	outmat(2,1) = offset.Y;
	//创建旋转矩阵
	matrix<f32> rotmat(3,3);
	rotmat.clear();
	rotmat(2,2) = 1;
	rotmat(0,0) = cos(rad);	rotmat(0,1) = -sin(rad);
	rotmat(1,0) = sin(rad);	rotmat(1,1) = cos(rad);
	//旋转操作
	node->TransM = prod(node->TransM, inmat);
	node->TransM = prod(node->TransM, rotmat);
	node->TransM = prod(node->TransM, outmat);
	//std::cout<< angle <<std::endl;
	//std::cout<< rad <<std::endl;
	//std::cout<< rotmat <<std::endl;

	//计算新的旋转中心
	//平移
	//RotPoint += (node->GetCenter() - OldObjCen);	
	////缩放
	//vector2d<f32> oldvec = OldObjLT - OldObjCen;
	//vector2d<f32> newvec = node->DstQuar[0] - node->GetCenter();
	////f32 scalfactor = sqrt(newvec.getLengthSQ() / oldvec.getLengthSQ());
	////RotPoint += (scalfactor - 1) * (RotPoint - node->GetCenter());
	//旋转
	/*f32 rotdeg = (f32)newvec.getAngleWith(oldvec);
	vector2d<f32> v1 = RotPoint - node->GetCenter();
	vector2d<f32> v2 = v1.rotateBy(-rotdeg);
	vector2d<f32> v3 = v2 - v1;
	RotPoint += v3;*/

	//OldObjCen = node->GetCenter();

	return true;
}

RotateUIAnimator* RotateUIAnimator::Clone()
{
	return new RotateUIAnimator(Begin, Duration, Angle, RotPoint, Loop);
}
