#include "SceneNodeAnimatorFollow.h"

void SceneNodeAnimatorFollow::animateNode( ISceneNode* node, u32 timeMs )
{
	node->setRotation( Target->getRotation() );
	vector3df direction = Target->getRotation().rotationToDirection().normalize();
	vector3df offset = direction * Distance;
	node->setPosition( Target->getPosition() + offset );
	
}

ISceneNodeAnimator* SceneNodeAnimatorFollow::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	throw std::exception("The method or operation is not implemented.");
}

SceneNodeAnimatorFollow::SceneNodeAnimatorFollow( ISceneNode* tar, f32 distance /*= 0 */ )
	: Target( tar ), Distance( distance )
{

}
