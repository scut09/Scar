#include "SceneNodeAnimatorFollow.h"
#include "irrlicht.h"

void SceneNodeAnimatorFollow::animateNode( ISceneNode* node, u32 timeMs )
{
	ICameraSceneNode* camera = static_cast<ICameraSceneNode*>(Target);
	node->setRotation( camera->getRotation() );
	vector3df direction = camera->getTarget() - camera->getPosition();
	vector3df offset = direction * Distance;
	node->setPosition( camera->getPosition() + offset );

	vector3df up = camera->getUpVector();
	vector3df dir = camera->getPosition() - camera->getTarget();
	vector3df x = up.crossProduct( dir );

	up.normalize();	dir.normalize();	x.normalize();

	vector3df pos = node->getPosition();


	f32 m[ 16 ];
	m[ 0 ] = x.X;	m[ 1 ] = up.X;		m[ 2 ] = -dir.X;		m[ 3 ] = 0;	
	m[ 4 ] = x.Y;	m[ 5 ] = up.Y;		m[ 6 ] = -dir.Y;		m[ 7 ] = 0;
	m[ 8 ] = x.Z;	m[ 9 ] = up.Z;		m[ 10 ] = -dir.Z;	m[ 11 ] = 0;
	m[ 12 ] = 0;	m[ 13 ] = 0;		m[ 14 ] = 0;		m[ 15 ] = 1;
	//m[ 0 ] = 0;	m[ 1 ] = 1;	m[ 2 ] = 0;		m[ 3 ] = 0;	
	//m[ 4 ] = 1;	m[ 5 ] = 0;	m[ 6 ] = 0;		m[ 7 ] = 0;
	//m[ 8 ] = 0;	m[ 9 ] = 0;	m[ 10 ] = 1;	m[ 11 ] = 0;
	//m[ 12 ] = 0;	m[ 13 ] = 0;	m[ 14 ] = 0;		m[ 15 ] = 1;

	core::matrix4 mat;
	mat.setM( m );

	//node->setRotation( mat.getRotationDegrees() * -1.f );
	core::matrix4& matOld = (core::matrix4&)node->getAbsoluteTransformation();
	matOld = mat * node->getParent()->getAbsoluteTransformation();
}

ISceneNodeAnimator* SceneNodeAnimatorFollow::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	throw std::exception("The method or operation is not implemented.");
}

SceneNodeAnimatorFollow::SceneNodeAnimatorFollow( ISceneNode* tar, f32 distance /*= 0 */ )
	: Target( tar ), Distance( distance )
{

}
