/********************************************************************
    创建时间: 2011-10-8   16:01
    文件名:   MultiplayerScene.cpp
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     多人游戏场景

*********************************************************************/

#include "MultiplayerScene.h"
#include "PythonManager.h"
#include "EngineHeader.h"
#include <iostream>
#include "Aircraft.h"
#include "FlyBehavior.h"



void MultiplayerScene::Run()
{

}

void MultiplayerScene::Init()
{
	PythonManager* p = PythonManager::GetPythonManager();

	object modelLoader = p->GetModelLoader();
	object MultiplayerLoad = modelLoader.attr( "MultiplayerLoad" );
	MultiplayerLoad();

	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();

	scene::ISceneManager* smgr = pEngine->GetSceneManager();

	smgr->addCameraSceneNodeFPS();

	ModelManager* modelMan = pEngine->GetModelManager();

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

	//// 注册引擎回调函数
	//pEngine->SetCallbackFunc( [ &scene ]( void* engine )->void*
	//{
	//	scene.Run();

	//	return 0;
	//} );



	//// 创建并注册receiver的事件处理回调函数
	//receiver.SetEventCallbackFunc( [ pEngine ]( const SEvent& event )->void*
	//{	
	//	//control.OnEvent( event );
	//	pEngine;		// 引擎指针
	//	//std::cout << "\n" << event.MouseInput.X << ' ' << event.MouseInput.Y << std::endl;
	//	return 0;
	//} );
}

void MultiplayerScene::Release()
{

}

