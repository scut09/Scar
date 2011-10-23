#include "MySceneNodeAnimatorScale.h"


MySceneNodeAnimatorScale::MySceneNodeAnimatorScale( u32 delay, u32 duration, vector3df scale, MOVE_TYPE type /*= LINER*/, f32 factor /*= 0 */ ) :
Begin( 0 ), Delay( delay ), Duration( duration ), Scale( scale ), MoveType( type ), Factor( factor )
{
	Origin = vector3df( -1, -1, -1 );
	ScaleFactor = scale - vector3df( 1 );
	switch( MoveType )
	{
	case MT_LINER:
		ScaleFactor /= (f32)duration;
		break;
	case MT_LOG:
		if ( Factor == 0 ) Factor = 80;
		ScaleFactor /= log( (f32)(duration / Factor + 1) );
		break;
	case MT_SQUARE:
		break;
	case MT_SQRT:
		if ( Factor == 0 ) Factor = 1;
		ScaleFactor /= sqrt( (f32)(duration / Factor) );
	case MT_POW:
		if ( Factor == 0 ) Factor = 1;
		ScaleFactor /= pow( (f32)duration, Factor );
		break;
	}
}

void MySceneNodeAnimatorScale::animateNode( ISceneNode* node, u32 timeMs )
{
	if( Begin == 0 )
		Begin = timeMs + Delay;
	//还未达到动画开始时间
	if( Begin > timeMs )
		return;

	if ( Origin == vector3df( -1, -1, -1 ) )
		Origin = node->getScale();

	u32 t = timeMs - Begin;
	vector3df sca;
	switch ( MoveType )
	{
	case MT_LINER:
		sca = ScaleFactor * (f32)t;
		break;
	case MT_LOG:
		sca = ScaleFactor * log( (f32)(t / Factor + 1) );
		break;
	case MT_SQUARE:
		break;
	case MT_SQRT:
		sca = ScaleFactor * sqrt( (f32)(t / Factor) );
		break;
	case MT_POW:
		sca = ScaleFactor * pow( (f32)t, Factor );
		break;
	}
	if ( sca.getLength() > Scale.getLength() )
		sca = Scale;
	node->setScale( Origin + sca );

	//到达动画结束时间
	if ( timeMs - Begin > Duration )
	{
		//把自己删掉
		node->removeAnimator(this);
		return;
	}
}

ISceneNodeAnimator* MySceneNodeAnimatorScale::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	throw std::exception("The method or operation is not implemented.");
}
