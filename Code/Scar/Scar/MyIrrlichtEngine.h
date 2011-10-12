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
#include "def.h"
#include "ModelManager.h"
#include "IMovable.h"
#include "AnimationManager.h"
#include "GameScene.h"

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

	// 禁止直接创建实例
	MyIrrlichtEngine() : m_lastUpdateTime( 0 ) {}

private:
	ModelManager					m_ModelManager;
	//AnimationManager				m_AnimationManager;		// 过时，抛弃这个。使用irrlicht内部的动画管理
	u32								m_lastUpdateTime;


public:
	static int						screen_width;	// 屏幕宽度
	static int						screen_height;	// 屏幕高度
	static IEventReceiver*			pEventReceiver;	// 消息处理者
	static bool						bFullScreen;	// 是否全屏
	static shared_ptr<GameScene>	currentScene;	// 当前场景

public:

	// 获取引擎指针
	static MyIrrlichtEngine* GetEngine();

	scene::ISceneManager* GetSceneManager();

	scene::ISceneCollisionManager* GetCollisionManager();

	video::IVideoDriver* GetVideoDriver();

	IrrlichtDevice*	GetDevice();

	ModelManager* GetModelManager();

	//AnimationManager* GetAnimationManager();

	void Run();

	void SetCallbackFunc( EngineRunCallbackFuncType func );

	void LoadModels()
	{
	}
};


#endif