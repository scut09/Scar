/********************************************************************
    创建时间: 2011-10-22   20:03
    文件名:   CSceneNodeAnimatorCollisionResponse.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     命中响应Animator

*********************************************************************/


#ifndef CSceneNodeAnimatorCollisionResponse_h__
#define CSceneNodeAnimatorCollisionResponse_h__

#include <irrlicht.h>

using namespace irr;
using namespace scene;


/*
** 名字：CSceneNodeAnimatorCollisionResponse
** 说明：碰撞响应
**
*/
class CSceneNodeAnimatorCollisionResponse : public ISceneNodeAnimator
{
public:
	CSceneNodeAnimatorCollisionResponse( ISceneCollisionManager* col ) 
		: CollisionMgr( col )
		, FirstRun( true )
	{

	}

	virtual void animateNode( ISceneNode* node, u32 timeMs )
	{
		using namespace core;

		if ( FirstRun )
		{
			FirstRun = true;
			LastPoint = node->getPosition();
		}

		core::vector3df pos = node->getPosition();

		line3df		line( LastPoint, pos );
		vector3df	collisonPoint;
		triangle3df	tri;
		ISceneNode* colNode = CollisionMgr->getSceneNodeAndCollisionPointFromRay( line, collisonPoint, tri );
		if ( colNode )
		{

		}

		LastPoint = pos;

	}

	virtual ISceneNodeAnimator* createClone(
		ISceneNode* node,
		ISceneManager* newManager = 0 )
	{
		return new CSceneNodeAnimatorCollisionResponse( CollisionMgr );
	}

private:
	ISceneCollisionManager*		CollisionMgr;
	core::vector3df				LastPoint;
	bool						FirstRun;
};




#endif // CSceneNodeAnimatorCollisionResponse_h__