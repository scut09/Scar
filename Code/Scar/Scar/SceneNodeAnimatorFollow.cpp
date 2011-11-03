#include "SceneNodeAnimatorFollow.h"
#include "irrlicht.h"
#include "MyIrrlichtEngine.h"
#include <iostream>

#define PRINT_POS( pos ) std::cout << #pos ## " " << pos.X << ' ' << pos.Y << ' ' << pos.Z << std::endl;


void SceneNodeAnimatorFollow::animateNode( ISceneNode* node, u32 timeMs )
{
	ICameraSceneNode* camera = static_cast<ICameraSceneNode*>(Target);
	vector3df direction = camera->getTarget() - camera->getPosition();
	vector3df offset = direction * Distance;

	vector3df up = camera->getUpVector();
	vector3df dir = camera->getTarget() - camera->getPosition();
	vector3df x = up.crossProduct( dir );
	up.normalize();	dir.normalize();	x.normalize();

	vector3df pos = camera->getPosition() + offset;

	core::matrix4 mat;
	f32 m[ 16 ];
	m[ 0 ] = x.X;	m[ 1 ] = up.X;		m[ 2 ] = dir.X;		m[ 3 ] = 0;	
	m[ 4 ] = x.Y;	m[ 5 ] = up.Y;		m[ 6 ] = dir.Y;		m[ 7 ] = 0;
	m[ 8 ] = x.Z;	m[ 9 ] = up.Z;		m[ 10 ] = dir.Z;	m[ 11 ] = 0;
	m[ 12 ] = 0;	m[ 13 ] = 0;	m[ 14 ] = 0;		m[ 15 ] = 1;
	mat.setM( m );
	mat.makeInverse();

	node->setRotation( mat.getRotationDegrees() );
	node->setPosition( pos );
	
}

ISceneNodeAnimator* SceneNodeAnimatorFollow::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	throw std::exception("The method or operation is not implemented.");
}

SceneNodeAnimatorFollow::SceneNodeAnimatorFollow( ISceneNode* tar, f32 distance /*= 0 */ )
	: Target( tar ), Distance( distance )
{

}
