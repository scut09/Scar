#include "RelateCameraAnimatorMove.h"

RelateCameraAnimatorMove::RelateCameraAnimatorMove( u32 delay, u32 duration, ICameraSceneNode* camera,
	vector3df start, vector3df end, RM_MOVE_TYPE moveType, f32 factor )
	: Begin( 0 ), Delay( delay ), Duration( duration ), Camera( camera), StartPos( start), EndPos( end ),
	MoveType( moveType ), Factor( factor )
{
	vector3df v = end - start;
	switch ( moveType )
	{
	case  RM_MT_LINER:
		OffsetFactor = v / (f32)duration;
		break;
	case RM_MT_LOG:
		if ( Factor == 0 ) Factor = 80;
		OffsetFactor = v / log( (f32)(duration / Factor) );
		break;
	}
}

void RelateCameraAnimatorMove::animateNode( ISceneNode* node, u32 timeMs )
{
	if( Begin == 0 )
		Begin = timeMs + Delay;
	//还未达到动画开始时间
	if( Begin > timeMs )
		return;

	u32 t = timeMs - Begin;
	vector3df offSet;
	switch ( MoveType )
	{
	case  RM_MT_LINER:
		offSet = OffsetFactor * (f32)t;
		break;
	case RM_MT_LOG:
		offSet = OffsetFactor * log( (f32)(t / Factor) );
		break;
	}
	node->setPosition( Camera->getPosition() + StartPos + offSet );

	//到达动画结束时间
	if ( timeMs - Begin > Duration )
	{
		//把自己删掉
		node->removeAnimator(this);
	}
}

ISceneNodeAnimator* RelateCameraAnimatorMove::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	throw std::exception("The method or operation is not implemented.");
}
