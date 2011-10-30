/********************************************************************
	创建时间: 2011:9:27   14:54
	文件名:   MyIrrlichtEngine.h
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     引擎的包装

*********************************************************************/

#ifndef _MYIRRLICHTENGINE_H_
#define _MYIRRLICHTENGINE_H_

#include <irrlicht.h>
#include <functional>
#include <list>
#include "def.h"
#include "ModelManager.h"
//#include "IMovable.h"
//#include "AnimationManager.h"
#include "GameScene.h"

class IUIObject;

using namespace irr;

typedef std::function< void*( void* ) > EngineRunCallbackFuncType;

/*
** 名字：MyIrrlichtEngine
** 说明：单例模式
**
*/
class MyIrrlichtEngine
{
private:
	IrrlichtDevice*					m_pDevice;		// 设备
	video::IVideoDriver*			m_pDriver;		// 驱动
	scene::ISceneManager*			m_pSmgr;		// 场景管理器
	scene::ISceneCollisionManager*	m_pColMan;		// 碰撞管理器
	scene::ICameraSceneNode*		m_pCamera;		// 相机，暂时没用

	static MyIrrlichtEngine*		m_pIrrlichtEngine;	// 单例模式，唯一的引擎
	EngineRunCallbackFuncType		m_runCallbackFunc;  // 每次帧运行时都会调用的回调函数

	bool							m_bMotionBlur;		// 是否开启运动模糊

	// 禁止直接创建实例
	MyIrrlichtEngine() : m_lastUpdateTime( 0 ), m_bMotionBlur( false ) {}

private:
	ModelManager					m_ModelManager;
	//AnimationManager				m_AnimationManager;		// 过时，抛弃这个。使用irrlicht内部的动画管理
	u32								m_lastUpdateTime;
	std::list<IUIObject*>			m_IUIObjectDeleteionList;// 针对IUIOjbect的删除缓冲队列
	std::list<scene::ISceneNode*>	m_ISceneNodeDeletionList;// 待删除列表，在每次引擎总循环的一次循环结束后会清空它。
															// 使用它可以让我们实现通过IUIAnimator来删除IUIObject
	std::list<GameScene*>			m_GameSceneDeletionList;// 延迟场景删除


public:
	static int						screen_width;	// 屏幕宽度
	static int						screen_height;	// 屏幕高度
	static IEventReceiver*			pEventReceiver;	// 消息处理者
	static bool						bFullScreen;	// 是否全屏
	static GameScene*				currentScene;	// 当前场景

public:

	// 获取引擎指针
	static MyIrrlichtEngine* GetEngine();

	scene::ISceneManager* GetSceneManager();

	scene::ISceneCollisionManager* GetCollisionManager();

	video::IVideoDriver* GetVideoDriver();

	IrrlichtDevice*	GetDevice();

	ModelManager* GetModelManager();

	// 设置是否开启运动模糊
	void SetMotionBlur( bool bOpen = true );

	//AnimationManager* GetAnimationManager();	// 历史问题，动画管理交给

	void Run();

	void SetCallbackFunc( EngineRunCallbackFuncType func );

	// 添加节点到删除队列中
	void AddToDeletionQueue( scene::ISceneNode* node );
	void AddToDeletionQueue( IUIObject* node );
	void AddToDeletionQueue( GameScene* scene );

	// 删除所有删除队列中的节点，这个会在每次循环后被调用
	void ClearDeletionList();
};


#endif