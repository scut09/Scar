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
#include "ModelManager.h"
#include "IMovable.h"
#include "AnimationManager.h"

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
	IrrlichtDevice*					m_pDevice;
	video::IVideoDriver*			m_pDriver;
	scene::ISceneManager*			m_pSmgr;
	scene::ISceneCollisionManager*	m_pColMan;
	scene::ICameraSceneNode*		m_pCamera;

	// 禁止直接创建实例
	MyIrrlichtEngine() {}

	static MyIrrlichtEngine*		m_pIrrlichtEngine;	// 单例模式，唯一的引擎
	EngineRunCallbackFuncType		m_runCallbackFunc;  // 每次帧运行时都会调用的回调函数

public:
	static int						screen_width;
	static int						screen_height;
	static IEventReceiver*			pEventReceiver;
	static bool						bFullScreen;

public:

	// 获取引擎指针
	static MyIrrlichtEngine* GetEngine();

	scene::ISceneManager* GetSceneManager();

	scene::ISceneCollisionManager* GetCollisionManager();

	video::IVideoDriver* GetVideoDriver();

	void Run();

	void SetCallbackFunc( EngineRunCallbackFuncType func );
};


#endif