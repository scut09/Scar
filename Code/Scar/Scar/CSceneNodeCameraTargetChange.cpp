#include "CSceneNodeCameraTargetChange.h"

CSceneNodeCameraTargetChange::CSceneNodeCameraTargetChange( u32 delay, u32 duration, vector3df newtarget, AS_MOVE_TYPE type /*= LINER*/, f32 factor /*= 0 */ ) :
Begin( 0 ), Delay( delay ), Duration( duration ), Target( newtarget ), MoveType( type ), Factor( factor )
{
	OriginTatget = newtarget;
}

void CSceneNodeCameraTargetChange::animateNode( ISceneNode* node, u32 timeMs )
{
	if( Begin == 0 )
		Begin = timeMs + Delay;
	//��δ�ﵽ������ʼʱ��
	if( Begin > timeMs )
		return;
	ChangeFactor = OriginTatget;
	OriginTatget = ((ICameraSceneNode*)node)->getTarget();
	ChangeFactor = ChangeFactor - OriginTatget;

	switch( MoveType )
	{
	case AS_MT_LINER:
		ChangeFactor /= (f32)Duration;
		break;
	case AS_MT_LOG:
		if ( Factor == 0 ) Factor = 80;
		ChangeFactor /= log( (f32)(Duration / Factor + 1) );
		break;
	case AS_MT_SQUARE:
		break;
	case AS_MT_SQRT:
		if ( Factor == 0 ) Factor = 1;
		ChangeFactor /= sqrt( (f32)(Duration / Factor) );
	case AS_MT_POW:
		if ( Factor == 0 ) Factor = 1;
		ChangeFactor /= pow( (f32)Duration, Factor );
		break;
	}

	u32 t = timeMs - Begin;
	vector3df tar;
	switch ( MoveType )
	{
	case AS_MT_LINER:
		tar = ChangeFactor * (f32)t;
		break;
	case AS_MT_LOG:
		tar = ChangeFactor * log( (f32)(t / Factor + 1) );
		break;
	case AS_MT_SQUARE:
		break;
	case AS_MT_SQRT:
		tar = ChangeFactor * sqrt( (f32)(t / Factor) );
		break;
	case AS_MT_POW:
		tar = ChangeFactor * pow( (f32)t, Factor );
		break;
	}
	((ICameraSceneNode*)node)->setTarget( tar );

	//���ﶯ������ʱ��
	if ( timeMs - Begin > Duration )
	{
		((ICameraSceneNode*)node)->setTarget( Target );
		//���Լ�ɾ��
		node->removeAnimator(this);
		return;
	}
}

ISceneNodeAnimator* CSceneNodeCameraTargetChange::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	throw std::exception("The method or operation is not implemented.");
}
