/********************************************************************
    创建时间: 2011-10-22   20:05
    文件名:   CSceneNodeAnimatorCollisionResponse.cpp
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     

*********************************************************************/


#include "CSceneNodeAnimatorCollisionResponse.h"
#include <iostream>
#include "IWeapon.h"


CSceneNodeAnimatorMyCollisionResponse::CSceneNodeAnimatorMyCollisionResponse( ISceneCollisionManager* col ) : CollisionMgr( col )
	, FirstRun( true )
{
	Func = []( ISceneNode*, ISceneNode* ) {};
}

void CSceneNodeAnimatorMyCollisionResponse::animateNode( ISceneNode* node, u32 timeMs )
{
	using namespace core;

	if ( FirstRun )
	{
		FirstRun = false;
		LastPoint = node->getPosition();
	}

	core::vector3df pos = node->getPosition();

	line3df		line( LastPoint, pos );

	vector3df	collisonPoint;
	triangle3df	tri;
	ISceneNode* colNode = CollisionMgr->getSceneNodeAndCollisionPointFromRay( line, collisonPoint, tri );
	if ( colNode )
	{
		Func( node, colNode );
		//std::cout << "haha\n";
	}

	if ( line.getLength() > 3 )
	{
		LastPoint = pos;
	}
}

ISceneNodeAnimator* CSceneNodeAnimatorMyCollisionResponse::createClone( ISceneNode* node, ISceneManager* newManager /*= 0 */ )
{
	return new CSceneNodeAnimatorMyCollisionResponse( CollisionMgr );
}
