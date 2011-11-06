#include "FlameAnimator.h"


void FlameAnimator::animateNode( ISceneNode* node, u32 timeMs )
{
	vector3df scale = vector3df( 8, 8, 20 );
	f32 speedRatio = Ship->GetVelocity() / Ship->GetMaxSpeed();
	vector3df newScale = scale * speedRatio;
	node->setScale( newScale );
	vector3df pos = vector3df( Offset.X, Offset.Y, Offset.Z + 20 - newScale.Z );
	node->setPosition( pos );
}

ISceneNodeAnimator* FlameAnimator::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	throw std::exception("The method or operation is not implemented.");
}

FlameAnimator::FlameAnimator( IShip* ship, vector3df offset )
	: Ship( ship ), Offset( offset )
{

}
