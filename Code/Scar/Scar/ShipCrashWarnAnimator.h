#ifndef ShipCrashWarnAnimator_h__
#define ShipCrashWarnAnimator_h__

/********************************************************************
	创建日期:	2011/12/06
	文件名: 	C:\Users\Administrator\Desktop\工作\SCAR项目组\opengl-scut\Code\Scar\Scar\ShipCrashWarnAnimator.h
	作者:		屠文翔
	
	描述:		提供舰船的碰撞预警
*********************************************************************/

#include <irrlicht.h>
#include "MyIrrlichtEngine.h"
#include "MultiplayerScene.h"
//#include <functional>
#include <iostream>

using namespace irr;
using namespace scene;

//typedef std::function< void( ISceneNode* node, const ISceneNode* ColNode, core::vector3df ColPos ) >	KidCollisionCallbackType;

class ShipCrashWarnAnimator : public ISceneNodeAnimator
{
public:
	ShipCrashWarnAnimator( ISceneCollisionManager* col, ITriangleSelector* sel, f32 radius )
	{
		CollisionMgr = col;
		TriSelector = sel;
		FirstRun = true;
		Radius = radius;
		//Func = []( ISceneNode*, const ISceneNode*, core::vector3df ) {};
	}

	virtual void animateNode( ISceneNode* node, u32 timeMs )
	{
		if (FirstRun)
		{
			FirstRun = false;
			LastPos = node->getPosition();
		}

		core::vector3df NowPos = node->getPosition();
		//ICameraSceneNode* camera = static_cast<ICameraSceneNode*>(node);
		//vector3df decPoint = (camera->getTarget() - camera->getPosition()).normalize() * Radius;
		vector3df decPoint = (NowPos - LastPos).normalize() * Radius;
		core::line3df Ray(NowPos, decPoint);

		bool IsCol = CollisionMgr->getCollisionPoint( Ray, TriSelector, ColPosition, ColTriangle, ColSceneNode );
		if ( IsCol )
		{
			// 反穿墙
			//node->setPosition( LastPos + (LastPos - NowPos).normalize() * 10 );
			// 调用回调函数
			//Func( node, ColSceneNode, ColPosition );
			//std::cout<< "!_!_!_!_!_!_!_!_"<< std::endl;
			// 显示预警信息
			static_cast<MultiplayerScene*>(MyIrrlichtEngine::GetEngine()->GetGameSceneManager()->GetCurrentGameScene())->m_playerHelper->AddWarnMsg(InfoAndWarn::PIW_CrashWarn);
		}

		LastPos = NowPos;
	}

	virtual ISceneNodeAnimator* createClone(
		ISceneNode* node,
		ISceneManager* newManager = 0 )
	{
		return 0;
	}

	//// 设置碰撞时的回调函数
	//void SetCollisionCallback( KidCollisionCallbackType func )
	//{
	//	Func = func;
	//}

private:
	ISceneCollisionManager*		CollisionMgr;
	ITriangleSelector*			TriSelector;

	core::vector3df				LastPos;			// 上次的位置
	bool						FirstRun;			// 是否第一次运行
	f32							Radius;				// 预警半径

	//KidCollisionCallbackType		Func;				// 碰撞时的回调
	const ISceneNode*			ColSceneNode;		// 被碰撞的节点
	core::vector3df				ColPosition;		// 碰撞发生的位置
	core::triangle3df			ColTriangle;		// 碰撞发生的三角形
};

#endif // ShipCrashWarnAnimator_h__
