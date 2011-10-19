/********************************************************************
	����ʱ��: 2011:9:27   14:54
	�ļ���:   MyIrrlichtEngine.cpp
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     

*********************************************************************/

#include "MyIrrlichtEngine.h"
#include "IUIObject.h"

MyIrrlichtEngine* MyIrrlichtEngine::m_pIrrlichtEngine = NULL;
IEventReceiver*	MyIrrlichtEngine::pEventReceiver = NULL;

// ���ڴ�С
int MyIrrlichtEngine::screen_width = 1000;
int MyIrrlichtEngine::screen_height = 640;
// ȫ�����ã�Ĭ��Ϊ����
bool MyIrrlichtEngine::bFullScreen = false;
GameScene* MyIrrlichtEngine::currentScene = NULL;


/*
** ���֣�MyIrrlichtEngine::GetEngine()
** ˵������ȡ����ָ��
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
		// �����豸ʧ�ܣ�����NULL
		if ( ! pDevice ) return NULL;

		// �������
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
	core::dimension2d<u32> size = m_pDevice->getVideoDriver()->getScreenSize();
	u32 frameTime = 16;
	wchar_t tmp[255];
	s32 now = 0;
	s32 lastfps = 0;
	s32 sceneStartTime = m_pDevice->getTimer()->getTime();
	gui::IGUIStaticText* statusText;
	const int lwidth = size.Width - 20;
	const int lheight = 16;

	core::rect<int> pos(10, size.Height-lheight-10, 10+lwidth, size.Height-10);
	//m_pDevice->getGUIEnvironment()->addImage(pos);
	statusText = m_pDevice->getGUIEnvironment()->addStaticText(L"Loading...",	pos, true);
	statusText->setOverrideColor(video::SColor(255,205,200,200));

	while ( m_pDevice->run() )
	{
		if ( ! m_pDevice->isWindowActive() )	continue;

		if ( currentScene == NULL )		continue;

		u32 now = m_pDevice->getTimer()->getRealTime();

		if ( now - m_lastUpdateTime < frameTime )
		{
			// ����ע��Ļص�����
			m_runCallbackFunc( (void*)this );

			//m_AnimationManager.Run();

			// ���г���
			currentScene->Run();
		}


		m_pDriver->beginScene( true, true, video::SColor( 255, 0, 0, 0 ) );

		m_pSmgr->drawAll();	

		currentScene->Draw();

		m_pDriver->endScene();

		ClearDeletionList();	// ɾ����ɾ�������еĶ�������Ҫ�ṩ����ɾ������ʹ��

		// write statistics
		const s32 nowfps = m_pDriver->getFPS();

		swprintf(tmp, 255, L"%ls fps:%3d triangles:%0.3f mio/s",
			m_pDriver->getName(), m_pDriver->getFPS(),
			m_pDriver->getPrimitiveCountDrawn(1) * (1.f / 1000000.f));

		statusText->setText(tmp);
		if ( nowfps != lastfps )
		{
			m_pDevice->setWindowCaption(tmp);
			lastfps = nowfps;
		}

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
