/*
** 作者：华亮
** 说明：引擎的包装
**
*/

#ifndef _MYIRRLICHTENGINE_H_
#define _MYIRRLICHTENGINE_H_

#include <irrlicht.h>

using namespace irr;

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

public:
	static int						screen_width;
	static int						screen_height;
	static IEventReceiver*			pEventReceiver;
	static bool						bFullScreen;

public:
	// 获取引擎指针
	MyIrrlichtEngine* GetEngine();

	scene::ISceneManager* GetSceneManager();

	scene::ISceneCollisionManager* GetCollisionManager();

	video::IVideoDriver* GetVideoDriver();


};


#endif