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
	m_pAnimation->Run();

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
	ModelManager* modelMan = pEngine->GetModelManager();
	m_pAnimation = pEngine->GetAnimationManager();

	smgr->addCameraSceneNodeFPS();

	scene::ISceneNode* node = modelMan->AddSceneNodeFromMesh( "bottle" );

	shared_ptr<Aircraft> bottle( new Aircraft );
	bottle->LoadSceneNode( node );
	bottle->SetSpeed( vector3df( 0.01, 0.1, 0 ) );
	shared_ptr<FlyStraightBehavior> beh( new FlyStraightBehavior );
	bottle->AddFlyBehavior( beh );

	AnimationManager* aniMan = pEngine->GetAnimationManager();
	aniMan->AddMovableNode( node, bottle );


	ModuleControl control;


	modelMan->LoadModels();

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

}

