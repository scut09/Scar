#include "SceneNodeAnimatorFollow.h"
#include "irrlicht.h"
#include "MyIrrlichtEngine.h"
#include <iostream>
#include "IShip.h"

#define PRINT_POS( pos ) std::cout << #pos ## " " << pos.X << ' ' << pos.Y << ' ' << pos.Z << std::endl;


void CSceneNodeAnimatorCameraFollowShip::animateNode( ISceneNode* node, u32 timeMs )
{
	ICameraSceneNode* camera = static_cast<ICameraSceneNode*>( node );
	IShip* ship = static_cast<IShip*>(Target);

	vector3df direction = (ship->getTarget() - ship->getPosition()).normalize();
	vector3df offset = direction * Distance;
	vector3df upoffset = ship->getUpVector();
	upoffset = upoffset.normalize() * 10;

	camera->setPosition( ship->getPosition() + offset + upoffset );
	camera->setRotation( ship->getRotation() );
	camera->setUpVector( ship->getUpVector() );
	camera->setTarget( ship->getTarget() );


}

ISceneNodeAnimator* CSceneNodeAnimatorCameraFollowShip::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	throw std::exception("The method or operation is not implemented.");
}

CSceneNodeAnimatorCameraFollowShip::CSceneNodeAnimatorCameraFollowShip( ISceneNode* tar, f32 distance /*= 0 */ )
	: Target( tar ), Distance( distance )
{

}
