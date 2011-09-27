/********************************************************************
	����ʱ��: 2011:9:27   14:54
	�ļ���:   MyIrrlichtEngine.cpp
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     

*********************************************************************/

#include "MyIrrlichtEngine.h"

MyIrrlichtEngine* MyIrrlichtEngine::m_pIrrlichtEngine = NULL;
IEventReceiver*	MyIrrlichtEngine::pEventReceiver = NULL;

// ���ڴ�С
int MyIrrlichtEngine::screen_width = 1000;
int MyIrrlichtEngine::screen_height = 640;
// ȫ�����ã�Ĭ��Ϊ����
bool MyIrrlichtEngine::bFullScreen = false;

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

		m_pDevice = createDevice(
			driverType, 
			core::dimension2d<u32>( screen_width, screen_height ), 
			16, 
			bFullScreen, 
			false, 
			false, 
			pEventReceiver
			);
		// �����豸ʧ�ܣ�����NULL
		if ( ! m_pDevice ) return NULL;

		// �������
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
