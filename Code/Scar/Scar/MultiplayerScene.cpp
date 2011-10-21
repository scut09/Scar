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
#include "CSceneNodeAnimatorSelfDelFlyStraight.h"
#include "Flame.h"
#include "huoyanshuxing.h"

scene::ISceneNode* node;

void MultiplayerScene::Run()
{
	//m_pAnimationMan->Run();

	//static int i = 0;

	//if ( i++ > 300 )
	//{
	//	i = 0;
	//	Release();
	//	MyIrrlichtEngine::currentScene = startScene;
	//	MyIrrlichtEngine::currentScene->Init();
	//	std::cout << "Back\n";
	//}
	vector3df camarapos = m_pCamera->getPosition();
	node->setPosition(camarapos + vector3df(0, 0, 1000000));//100万

}

void MultiplayerScene::Init()
{
	// 使用Python模块加载模型
	PythonManager* p = PythonManager::GetPythonManager();

	// 获取引擎
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	scene::ISceneManager* smgr = pEngine->GetSceneManager();
	m_pModelMan = pEngine->GetModelManager();

	//  加入摄像机
	m_pCamera = smgr->addCameraSceneNodeFPS( 0, 100, 50.0f );
	m_pCamera->setFOV( 1 );
	m_pCamera->setFarValue( 1000000 );

	//加载星球
	node = smgr->addSphereSceneNode( 500000 );
	if ( node )
	{
		node->setMaterialTexture( 0, pEngine->GetVideoDriver()->getTexture("../media/Planets/planet6.jpg") );
		node->setMaterialFlag( video::EMF_LIGHTING, false );
	}

	//加载空间站模型
	IMeshSceneNode* cs1 = smgr->addMeshSceneNode( smgr->getMesh("../modle/station/cs1.obj") );
	if( cs1 )
	{
		std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
		//cs1->setPosition( core::vector3df(0,0,0) );
		//cs1->setMaterialTexture( 0, driver->getTexture("../media/Planets/planet6.jpg") );
		//cs1->setMaterialFlag( video::EMF_LIGHTING, false );
	}

	try
	{
		object modelLoader = p->GetModelLoader();
		object MultiplayerLoad = modelLoader.attr( "MultiplayerLoad" );
		MultiplayerLoad();
	}
	catch ( ... )
	{
		PyErr_Print();
	}


//	m_pAnimationMan = pEngine->GetAnimationManager();



	// 加载模型和动画
	auto bottleNode = m_pModelMan->AddSceneNodeFromMesh( "bottle" );

	//ISceneNodeAnimator* anim = new CSceneNodeAnimatorSelfDelFlyStraight( vector3df( 0, 0, 0 ),
	//	vector3df( 0, 1000, 1000 ), 5000, pEngine->GetDevice()->getTimer()->getTime() );
	ISceneNodeAnimator* anim = new CSceneNodeAnimatorAutoTrack( smgr );
	bottleNode->addAnimator( anim );
	anim->drop();

	for ( auto iter = m_pModelMan->GetISceneNodeList().begin(); iter != m_pModelMan->GetISceneNodeList().end(); ++iter )
	{
		ISceneNodeAnimator* anim = new Chuoyanshuxing( smgr );
		(*iter)->addAnimator( anim );
		//(*iter)->setScale( vector3df( 1000, 1000, 1000 ) );
		anim->drop();
	}






	ModuleControl control;

	auto driver = pEngine->GetVideoDriver();

	/*m_pSkyBox = smgr->addSkyBoxSceneNode(
		driver->getTexture("../media/irrlicht2_up.jpg"),
		driver->getTexture("../media/irrlicht2_dn.jpg"),
		driver->getTexture("../media/irrlicht2_lf.jpg"),
		driver->getTexture("../media/irrlicht2_rt.jpg"),
		driver->getTexture("../media/irrlicht2_ft.jpg"),
		driver->getTexture("../media/irrlicht2_bk.jpg"));*/

	// 天空盒
	m_pSkyBox = smgr->addSkyBoxSceneNode(
		driver->getTexture("../media/Space/c07_up.jpg"),
		driver->getTexture("../media/Space/c07_dn.jpg"),
		driver->getTexture("../media/Space/c07_lt.jpg"),
		driver->getTexture("../media/Space/c07_rt.jpg"),
		driver->getTexture("../media/Space/c07_ft.jpg"),
		driver->getTexture("../media/Space/c07_bk.jpg"));	
	//不知道为什么把天空盒设小一点反而不会出黑边
	m_pSkyBox->setScale( vector3df( .1f, .1f, .1f ) );

	//// 注册引擎回调函数
	//pEngine->SetCallbackFunc( [ &scene ]( void* engine )->void*
	//{
	//	scene.Run();

	//	return 0;
	//} );

	
	//CFlame flame;
	//auto fire = flame.createFlame(
	//	MyIrrlichtEngine::GetEngine()->GetDevice(), 
	//	"../media/particle.bmp"
	//	);
	//node->addChild( fire );

	//创建边上的粒子****************
	//for (int i = 0;i < 24;i++)
	//{
	//	CFlame flame;
	//	auto fire = flame.createFlame(
	//		MyIrrlichtEngine::GetEngine()->GetDevice(), 
	//		"../media/particle.bmp"
	//		);
	////	fire->setVisible(false);   //初始不可见
	//	node->addChild( fire );
	//}


	// 创建并注册receiver的事件处理回调函数
	static_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [ pEngine ]( const SEvent& event )->void*
	{	
		//control.OnEvent( event );
		pEngine;		// 引擎指针
		//std::cout << "\n" << event.MouseInput.X << ' ' << event.MouseInput.Y << std::endl;
		return 0;
	} );
}

void MultiplayerScene::Release()
{
	m_pCamera->remove();
	m_pSkyBox->remove();

//	m_pAnimationMan->RemoveAll();

	m_pModelMan->DeleteAll();

	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	scene::ISceneManager* smgr = pEngine->GetSceneManager();
	smgr->clear();
}

