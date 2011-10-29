#include "SceneNodeAnimatorFollow.h"
#include "irrlicht.h"

void SceneNodeAnimatorFollow::animateNode( ISceneNode* node, u32 timeMs )
{
	ICameraSceneNode* camera = static_cast<ICameraSceneNode*>(Target);
	node->setRotation( camera->getRotation() );
	vector3df direction = camera->getTarget() - camera->getPosition();
	vector3df offset = direction * Distance;
	node->setPosition( camera->getPosition() + offset );
	
}

ISceneNodeAnimator* SceneNodeAnimatorFollow::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	throw std::exception("The method or operation is not implemented.");
}

SceneNodeAnimatorFollow::SceneNodeAnimatorFollow( ISceneNode* tar, f32 distance /*= 0 */ )
	: Target( tar ), Distance( distance )
{

}
