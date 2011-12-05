#ifndef MySceneNodeAnimatorCollisionResponse_h__
#define MySceneNodeAnimatorCollisionResponse_h__

/********************************************************************
	创建时间:	2011/12/04
	文件名称: 	MySceneNodeAnimatorCollisionResponse
	作者:		屠文翔 - Kid
	
	描述:		使用triangle selector的碰撞响应
*********************************************************************/

#include <irrlicht.h>
#include <functional>
#include <iostream>

using namespace irr;
using namespace scene;

typedef std::function< void( ISceneNode* node, const ISceneNode* ColNode, core::vector3df ColPos ) >	KidCollisionCallbackType;

class MySceneNodeAnimatorCollisionResponse : public ISceneNodeAnimator
{
public:
	MySceneNodeAnimatorCollisionResponse( ISceneCollisionManager* col, ITriangleSelector* sel )
	{
		CollisionMgr = col;
		TriSelector = sel;
		FirstRun = true;
		Func = []( ISceneNode*, const ISceneNode*, core::vector3df ) {};
	}

	virtual void animateNode( ISceneNode* node, u32 timeMs )
	{
		if (FirstRun)
		{
			FirstRun = false;
			LastPos = node->getPosition();
		}

		core::vector3df NowPos = node->getPosition();
		core::line3df Ray(LastPos, NowPos);

		bool IsCol = CollisionMgr->getCollisionPoint( Ray, TriSelector, ColPosition, ColTriangle, ColSceneNode );
		if ( IsCol )
		{
			// 反穿墙
			//node->setPosition( LastPos + (LastPos - NowPos).normalize() * 10 );
			// 调用回调函数
			Func( node, ColSceneNode, ColPosition );
			//std::cout<< "!_!_!_!_!_!_!_!_"<< std::endl;
		}
		else
			LastPos = NowPos;
	}

	virtual ISceneNodeAnimator* createClone(
		ISceneNode* node,
		ISceneManager* newManager = 0 )
	{
		return 0;
	}

	// 设置碰撞时的回调函数
	void SetCollisionCallback( KidCollisionCallbackType func )
	{
		Func = func;
	}

private:
	ISceneCollisionManager*		CollisionMgr;
	ITriangleSelector*			TriSelector;

	core::vector3df				LastPos;			// 上次的位置
	bool						FirstRun;			// 是否第一次运行

	KidCollisionCallbackType		Func;				// 碰撞时的回调
	const ISceneNode*			ColSceneNode;		// 被碰撞的节点
	core::vector3df				ColPosition;		// 碰撞发生的位置
	core::triangle3df			ColTriangle;		// 碰撞发生的三角形
};

#endif // MySceneNodeAnimatorCollisionResponse_h__
