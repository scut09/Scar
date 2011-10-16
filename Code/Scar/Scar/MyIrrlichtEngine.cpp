/********************************************************************
	创建时间: 2011:9:27   14:54
	文件名:   MyIrrlichtEngine.cpp
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     

*********************************************************************/

#include "MyIrrlichtEngine.h"
#include "IUIObject.h"

MyIrrlichtEngine* MyIrrlichtEngine::m_pIrrlichtEngine = NULL;
IEventReceiver*	MyIrrlichtEngine::pEventReceiver = NULL;

// 窗口大小
int MyIrrlichtEngine::screen_width = 1000;
int MyIrrlichtEngine::screen_height = 640;
// 全屏设置，默认为窗口
bool MyIrrlichtEngine::bFullScreen = false;
shared_ptr<GameScene> MyIrrlichtEngine::currentScene;


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

		auto pDevice = irr::createDevice(
			driverType, 
			core::dimension2d<u32>( screen_width, screen_height ), 
			16, 
			bFullScreen, 
			false, 
			false, 
			pEventReceiver
			);
		// 创建设备失败，返回NULL
		if ( ! pDevice ) return NULL;

		// 隐藏鼠标
		//pDevice->getCursorControl()->setVisible( false );

		m_pIrrlichtEngine = new MyIrrlichtEngine;
		m_pIrrlichtEngine->m_pDevice = pDevice;
		m_pIrrlichtEngine->m_pDriver = pDevice->getVideoDriver();
		m_pIrrlichtEngine->m_pSmgr = pDevice->getSceneManager();
		m_pIrrlichtEngine->m_pColMan = m_pIrrlichtEngine->m_pSmgr->getSceneCollisionManager();

		m_pIrrlichtEngine->m_runCallbackFunc = []( void* )->void* { return 0; };
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

void MyIrrlichtEngine::Run()
{
	u32 frameTime = 16;
	while ( m_pDevice->run() )
	{
		if ( ! m_pDevice->isWindowActive() )	continue;

		u32 now = m_pDevice->getTimer()->getRealTime();

		if ( now - m_lastUpdateTime < frameTime )
		{
			// 运行注册的回调函数
			m_runCallbackFunc( (void*)this );

			//m_AnimationManager.Run();

			// 运行场景
			currentScene->Run();
		}


		m_pDriver->beginScene( true, true, video::SColor( 150, 50, 50, 50 ) );

		m_pSmgr->drawAll();	

		currentScene->Draw();

		m_pDriver->endScene();

		ClearDeletionList();	// 删除待删除队列中的东西，主要提供给自删除动画使用

		m_lastUpdateTime = now;
	}
}

void MyIrrlichtEngine::SetCallbackFunc( EngineRunCallbackFuncType func )
{
	m_runCallbackFunc = func;
}

IrrlichtDevice* MyIrrlichtEngine::GetDevice()
{
	return m_pDevice;
}

ModelManager* MyIrrlichtEngine::GetModelManager()
{
	return &m_ModelManager;
}

void MyIrrlichtEngine::AddToDeletionQueue( scene::ISceneNode* node )
{
	if ( ! node )	return;

	node->grab();

	m_ISceneNodeDeletionList.push_back( node );
}

void MyIrrlichtEngine::AddToDeletionQueue( IUIObject* node )
{
	if ( ! node )	return;

	node->grab();

	m_IUIObjectDeleteionList.push_back( node );
}

void MyIrrlichtEngine::ClearDeletionList()
{
	for ( auto iter = m_ISceneNodeDeletionList.begin(); iter != m_ISceneNodeDeletionList.end(); ++iter )
	{
		(*iter)->remove();
		(*iter)->drop();
	}

	m_ISceneNodeDeletionList.clear();

	for ( auto iter = m_IUIObjectDeleteionList.begin(); iter != m_IUIObjectDeleteionList.end(); ++iter )
	{
		(*iter)->remove();
		(*iter)->drop();
	}

	m_IUIObjectDeleteionList.clear();
}

//AnimationManager* MyIrrlichtEngine::GetAnimationManager()
//{
//	return &m_AnimationManager;
//}
