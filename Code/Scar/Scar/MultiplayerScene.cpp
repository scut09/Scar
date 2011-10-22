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
#include "SceneNodeAnimatorAircraftFPS.h"
#include "SpaceStation.h"

scene::ISceneNode* node;

void MultiplayerScene::Run()
{
	// 获取引擎
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	scene::ISceneManager* smgr = pEngine->GetSceneManager();

	vector3df camarapos = m_pCamera->getPosition();
	// 设置行星位置，使其永远相对摄像机
	smgr->getSceneNodeFromName("planet1")->setPosition( camarapos + vector3df(-200000, 0, 1000000) );//100万
	// 设置卫星位置，使其永远相对摄像机
	smgr->getSceneNodeFromName("moon1")->setPosition( camarapos + vector3df(100000, 0, -250000) );
}

void MultiplayerScene::Init()
{
	// 使用Python模块加载模型
	PythonManager* p = PythonManager::GetPythonManager();

	// 获取引擎
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	scene::ISceneManager* smgr = pEngine->GetSceneManager();
	m_pModelMan = pEngine->GetModelManager();
	auto driver = pEngine->GetVideoDriver();

	//  加入摄像机
	//m_pCamera = smgr->addCameraSceneNodeFPS( 0, 100, 50.0f );
	m_pCamera = smgr->addCameraSceneNode();
	auto ani = new CSceneNodeAnimatorAircraftFPS( pEngine->GetDevice()->getCursorControl() );
	m_pCamera->addAnimator( ani );
	ani->drop();
	m_pCamera->setFOV( 1 );
	m_pCamera->setFarValue( 1000000 );
	//m_pCamera->setPosition( vector3df( 0, 0, -1000000 ) );

	//加载行星
	auto planet = smgr->addSphereSceneNode( 500000 );
	if ( planet )
	{
		// 设置名称
		planet->setName( "planet1" );
		// 加载纹理
		planet->setMaterialTexture( 0, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/planet6.jpg") ) );
		// 星球自转
		auto rot = smgr->createRotationAnimator( vector3df( 0, 0.005f, 0) );
		planet->addAnimator( rot );
		// 设置初始大小
		//planet->setScale( vector3df( .01f ) );
		// 缩放动画
		//auto sca = smgr->createRotationAnimator()
	}

	//加载卫星
	auto moon = smgr->addSphereSceneNode( 125000 );
	if ( moon )
	{
		// 设置名称
		moon->setName( "moon1" );
		// 加载纹理
		moon->setMaterialTexture( 0, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/planet1.jpg") ) );
	}

	//加载空间站模型
	/*IMeshSceneNode* cs1 = smgr->addMeshSceneNode( smgr->getMesh( _T("../modle/station/cs1.obj") ) );*/
	BuildSpaceStation* cs1 = new BuildSpaceStation( smgr, _T("../modle/station/cs1.obj" ) );
	//m_pCamera->addAnimator(smgr->createCollisionResponseAnimator(cs1->getTriangleSelector(), m_pCamera));
	//cs1->drop();
	if( cs1 )
	{
		// 设置名字
		//station->setName( "station1" );
	}

	////加载太阳
	//auto sun = smgr->addSphereSceneNode( 200000 );
	//if ( sun )
	//{
	//	// 设置名称
	//	moon->setName( "sun1" );
	//}

	// 太阳光（平行光）
	video::SLight light1;
	light1.Type = ELT_DIRECTIONAL;
	light1.SpecularColor = video::SColorf( 0, 0, 0 );
	light1.AmbientColor = video::SColorf( 0.15f, 0.15f, 0.15f );
	//light1.AmbientColor = video::SColorf( 0,0,0 );
	auto lsn = smgr->addLightSceneNode();
	lsn->setLightData( light1 );
	lsn->setRotation( vector3df( 0, 90, 0 ) );

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
	auto bottleNode = m_pModelMan->AddSceneNodeFromMesh( _T("bottle") );

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

	

	/*m_pSkyBox = smgr->addSkyBoxSceneNode(
		driver->getTexture("../media/irrlicht2_up.jpg"),
		driver->getTexture("../media/irrlicht2_dn.jpg"),
		driver->getTexture("../media/irrlicht2_lf.jpg"),
		driver->getTexture("../media/irrlicht2_rt.jpg"),
		driver->getTexture("../media/irrlicht2_ft.jpg"),
		driver->getTexture("../media/irrlicht2_bk.jpg"));*/

	// 天空盒
	m_pSkyBox = smgr->addSkyBoxSceneNode(
		driver->getTexture( _T("../media/Space/c07_up.jpg") ),
		driver->getTexture( _T("../media/Space/c07_dn.jpg") ),
		driver->getTexture( _T("../media/Space/c07_lt.jpg") ),
		driver->getTexture( _T("../media/Space/c07_rt.jpg") ),
		driver->getTexture( _T("../media/Space/c07_ft.jpg") ),
		driver->getTexture( _T("../media/Space/c07_bk.jpg") ));	
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

