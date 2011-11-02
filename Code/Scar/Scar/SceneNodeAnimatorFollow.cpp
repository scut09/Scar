#include "SceneNodeAnimatorFollow.h"
#include "irrlicht.h"
#include <iostream>

#define PRINT_POS( pos ) std::cout << #pos ## " " << pos.X << ' ' << pos.Y << ' ' << pos.Z << std::endl;


void SceneNodeAnimatorFollow::animateNode( ISceneNode* node, u32 timeMs )
{
	ICameraSceneNode* camera = static_cast<ICameraSceneNode*>(Target);
	vector3df direction = camera->getTarget() - camera->getPosition();
	vector3df offset = direction * Distance;
	node->setPosition( camera->getPosition() + offset );

	//node->setRotation( direction.getHorizontalAngle() );

	vector3df up = camera->getUpVector();
	vector3df dir = camera->getTarget() - camera->getPosition();
	vector3df x = - up.crossProduct( dir );

	up.normalize();	dir.normalize();	x.normalize();

	//vector3df pos = camera->getPosition();
	vector3df pos = node->getPosition();

	node->updateAbsolutePosition();

	core::matrix4 mat;

	
	f32 m[ 16 ];
	m[ 0 ] = x.X;	m[ 1 ] = up.X;		m[ 2 ] = dir.X;		m[ 3 ] = 0;	
	m[ 4 ] = x.Y;	m[ 5 ] = up.Y;		m[ 6 ] = dir.Y;		m[ 7 ] = 0;
	m[ 8 ] = x.Z;	m[ 9 ] = up.Z;		m[ 10 ] = dir.Z;	m[ 11 ] = 0;
	m[ 12 ] = pos.X;	m[ 13 ] = pos.Y;		m[ 14 ] = pos.Z;		m[ 15 ] = 1;

	////m[ 0 ] = 0;	m[ 1 ] = 1;	m[ 2 ] = 0;		m[ 3 ] = 0;	
	////m[ 4 ] = 1;	m[ 5 ] = 0;	m[ 6 ] = 0;		m[ 7 ] = 0;
	////m[ 8 ] = 0;	m[ 9 ] = 0;	m[ 10 ] = 1;	m[ 11 ] = 0;
	////m[ 12 ] = 0;	m[ 13 ] = 0;	m[ 14 ] = 0;		m[ 15 ] = 1;

	mat.setM( m );

	//node->setRotation( mat.getRotationDegrees() * -1.f );
	core::matrix4& matOld = (core::matrix4&)node->getAbsoluteTransformation();
	matOld = node->getParent()->getAbsoluteTransformation() * mat;


	mat = node->getAbsoluteTransformation();	
	PRINT_POS( pos );
	for ( int i = 0; i < 4; i++ )
	{
		for ( int j = 0; j < 4; j++ )
		{
			std::cout << mat( i, j ) << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

ISceneNodeAnimator* SceneNodeAnimatorFollow::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	throw std::exception("The method or operation is not implemented.");
}

SceneNodeAnimatorFollow::SceneNodeAnimatorFollow( ISceneNode* tar, f32 distance /*= 0 */ )
	: Target( tar ), Distance( distance )
{

}
