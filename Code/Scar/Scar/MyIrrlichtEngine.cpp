/********************************************************************
	创建时间: 2011:9:27   14:54
	文件名:   MyIrrlichtEngine.cpp
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     

*********************************************************************/

#include "MyIrrlichtEngine.h"

MyIrrlichtEngine* MyIrrlichtEngine::m_pIrrlichtEngine = NULL;
IEventReceiver*	MyIrrlichtEngine::pEventReceiver = NULL;

// 窗口大小
int MyIrrlichtEngine::screen_width = 1000;
int MyIrrlichtEngine::screen_height = 640;
// 全屏设置，默认为窗口
bool MyIrrlichtEngine::bFullScreen = false;

/*
** 名字：MyIrrlichtEngine::GetEngine()
** 说明：获取引擎指针
**
*/
MyIrrlichtEngine* MyIrrlichtEngine::GetEngine()
{
	if ( ! m_pIrrlichtEngine )
	{
		video::E_DRIVER_TYPE driverType = (video::E_DRIVER_TYPE)video::EDT_OPENGL;

		m_pDevice = createDevice(
			driverType, 
			core::dimension2d<u32>( screen_width, screen_height ), 
			16, 
			bFullScreen, 
			false, 
			false, 
			pEventReceiver
			);
		// 创建设备失败，返回NULL
		if ( ! m_pDevice ) return NULL;

		// 隐藏鼠标
		m_pDevice->getCursorControl()->setVisible( false );

		m_pDriver	= m_pDevice->getVideoDriver();
		m_pSmgr		= m_pDevice->getSceneManager();
		m_pColMan	= m_pSmgr->getSceneCollisionManager();

		m_pIrrlichtEngine = new MyIrrlichtEngine;
	}

	return m_pIrrlichtEngine;
}

scene::ISceneManager* MyIrrlichtEngine::GetSceneManager()
{
	return m_pSmgr;
}

scene::ISceneCollisionManager* MyIrrlichtEngine::GetCollisionManager()
{
	return m_pColMan;
}

video::IVideoDriver* MyIrrlichtEngine::GetVideoDriver()
{
	return m_pDriver;
}
