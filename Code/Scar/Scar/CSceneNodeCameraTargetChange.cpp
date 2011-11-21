#include "CSceneNodeCameraTargetChange.h"

CSceneNodeCameraTargetChange::CSceneNodeCameraTargetChange( u32 delay, u32 duration, vector3df newtarget ) :
Begin( 0 ), Delay( delay ), Duration( duration ), NewTarget( newtarget.normalize() ), IsFirst( true )
{

}

void CSceneNodeCameraTargetChange::animateNode( ISceneNode* node, u32 timeMs )
{
	ICameraSceneNode* camera = static_cast<ICameraSceneNode*>( node );
	if( IsFirst )
	{
		IsFirst = false;
		Begin = timeMs + Delay;
		OriginTarget = camera->getTarget() - camera->getPosition();
		OriginTarget.normalize();
		camera->setTarget( camera->getPosition() + OriginTarget );
		ChangeFactor = ( NewTarget - OriginTarget ) / (f32)Duration;
		//ChangeFactor = ( NewTarget - OriginTarget ).getHorizontalAngle() / (f32)Duration;
	}

	//��δ�ﵽ������ʼʱ��
	if( Begin > timeMs )
		return;

	u32 t = timeMs - Begin;
	vector3df tar;
	if( t < Duration )
	{
		tar = OriginTarget + ChangeFactor * (f32)t;
		//tar = OriginTarget;
		//tar.rotateYZBy( ChangeFactor.X * (f32)t );
		//tar.rotateXZBy( -ChangeFactor.Y * (f32)t );
	}
	else
		tar = NewTarget;
	tar = tar + camera->getPosition();
	camera->setTarget( tar );

	//���ﶯ������ʱ��
	if ( timeMs - Begin > Duration )
	{
		//���Լ�ɾ��
		node->removeAnimator(this);
		return;
	}
}

ISceneNodeAnimator* CSceneNodeCameraTargetChange::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	throw std::exception("The method or operation is not implemented.");
}
