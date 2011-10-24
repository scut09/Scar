#include "MySceneNodeAnimatorMove.h"


MySceneNodeAnimatorMove::MySceneNodeAnimatorMove( u32 delay, u32 duration, vector3df start, 
	vector3df end, AM_MOVE_TYPE moveType /*= AM_MT_LINER*/, f32 factor /*= 0 */ )
	: Begin( 0 ), Delay( delay ), Duration( duration ), StartPos( start), EndPos( end ),
	MoveType( moveType ), Factor( factor )
{
	vector3df v = end - start;
	switch ( moveType )
	{
	case  AM_MT_LINER:
		OffsetFactor = v / (f32)duration;
		break;
	case AM_MT_LOG:
		if ( Factor == 0 ) Factor = 80;
		OffsetFactor = v / log( (f32)(duration / Factor) );
		break;
	}
}

void MySceneNodeAnimatorMove::animateNode( ISceneNode* node, u32 timeMs )
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
	case  AM_MT_LINER:
		offSet = OffsetFactor * (f32)t;
		break;
	case AM_MT_LOG:
		offSet = OffsetFactor * log( (f32)(t / Factor) );
		break;
	}
	node->setPosition( StartPos + offSet );

	//到达动画结束时间
	if ( timeMs - Begin > Duration )
	{
		//把自己删掉
		node->removeAnimator(this);
	}
}

ISceneNodeAnimator* MySceneNodeAnimatorMove::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	return new MySceneNodeAnimatorMove( Delay, Duration, StartPos, EndPos, MoveType, Factor );
}
