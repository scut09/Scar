/********************************************************************
    ����ʱ��: 2011-10-8   16:01
    �ļ���:   MultiplayerScene.cpp
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     ������Ϸ����

*********************************************************************/

#include "MultiplayerScene.h"
#include "PythonManager.h"
#include "EngineHeader.h"
#include <iostream>
#include "Aircraft.h"
#include "FlyBehavior.h"



void MultiplayerScene::Run()
{
	m_pAnimationMan->Run();

	static int i = 0;

	if ( i++ > 300 )
	{
		i = 0;
		Release();
		MyIrrlichtEngine::currentScene = startScene;
		MyIrrlichtEngine::currentScene->Init();
		std::cout << "Back\n";
	}

}

void MultiplayerScene::Init()
{
	// ʹ��Pythonģ�����ģ��
	PythonManager* p = PythonManager::GetPythonManager();

	object modelLoader = p->GetModelLoader();
	object MultiplayerLoad = modelLoader.attr( "MultiplayerLoad" );
	MultiplayerLoad();

	// ��ȡ����
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	scene::ISceneManager* smgr = pEngine->GetSceneManager();
	m_pModelMan = pEngine->GetModelManager();
	m_pAnimationMan = pEngine->GetAnimationManager();

	//  ���������
	m_pCamera = smgr->addCameraSceneNodeFPS();

	// ����ģ�ͺͶ���
	scene::ISceneNode* node = m_pModelMan->AddSceneNodeFromMesh( "bottle" );

	shared_ptr<Aircraft> bottle( new Aircraft );
	bottle->LoadSceneNode( node );
	bottle->SetSpeed( vector3df( 0.01, 0.1, 0 ) );
	shared_ptr<FlyStraightBehavior> beh( new FlyStraightBehavior );
	bottle->AddFlyBehavior( beh );

	AnimationManager* aniMan = pEngine->GetAnimationManager();
	aniMan->AddMovableNode( node, bottle );

	ModuleControl control;

	auto driver = pEngine->GetVideoDriver();

	m_pSkyBox = smgr->addSkyBoxSceneNode(
		driver->getTexture("../media/irrlicht2_up.jpg"),
		driver->getTexture("../media/irrlicht2_dn.jpg"),
		driver->getTexture("../media/irrlicht2_lf.jpg"),
		driver->getTexture("../media/irrlicht2_rt.jpg"),
		driver->getTexture("../media/irrlicht2_ft.jpg"),
		driver->getTexture("../media/irrlicht2_bk.jpg"));

	//// ע������ص�����
	//pEngine->SetCallbackFunc( [ &scene ]( void* engine )->void*
	//{
	//	scene.Run();

	//	return 0;
	//} );



	//// ������ע��receiver���¼�����ص�����
	//receiver.SetEventCallbackFunc( [ pEngine ]( const SEvent& event )->void*
	//{	
	//	//control.OnEvent( event );
	//	pEngine;		// ����ָ��
	//	//std::cout << "\n" << event.MouseInput.X << ' ' << event.MouseInput.Y << std::endl;
	//	return 0;
	//} );
}

void MultiplayerScene::Release()
{
	m_pCamera->remove();
	m_pSkyBox->remove();

	m_pAnimationMan->RemoveAll();

	m_pModelMan->DeleteAll();
}

