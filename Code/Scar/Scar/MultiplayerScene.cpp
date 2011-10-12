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
	// 使用Python模块加载模型
	PythonManager* p = PythonManager::GetPythonManager();

	object modelLoader = p->GetModelLoader();
	object MultiplayerLoad = modelLoader.attr( "MultiplayerLoad" );
	MultiplayerLoad();

	// 获取引擎
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	scene::ISceneManager* smgr = pEngine->GetSceneManager();
	m_pModelMan = pEngine->GetModelManager();
	m_pAnimationMan = pEngine->GetAnimationManager();

	//  加入摄像机
	m_pCamera = smgr->addCameraSceneNodeFPS();

	// 加载模型和动画
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
	m_pCamera->remove();
	m_pSkyBox->remove();

	m_pAnimationMan->RemoveAll();

	m_pModelMan->DeleteAll();
}

