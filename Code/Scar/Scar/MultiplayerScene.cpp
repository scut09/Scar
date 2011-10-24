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
#include "AllAnimators.h"

//scene::ISceneNode* node;

vector3df moonPos = vector3df( 1e5, 0, 2.5e5 );

void MultiplayerScene::Run()
{

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
	/*m_pCamera = smgr->addCameraSceneNodeFPS( 0, 100, 50.0f );*/
	m_pCamera = smgr->addCameraSceneNode();
	auto fpsAni = new CSceneNodeAnimatorAircraftFPS( pEngine->GetDevice()->getCursorControl() );
	m_pCamera->addAnimator( fpsAni );
	fpsAni->drop();
	//m_pCamera = smgr->addCameraSceneNodeMaya();
	m_pCamera->setFOV( 1 );
	m_pCamera->setFarValue( 1e7f );
	auto shakeAni = new MySceneNodeAnimatorShake( 0, 8000, 1.2f );
	m_pCamera->addAnimator( shakeAni );
	shakeAni->drop();
	m_pCamera->bindTargetAndRotation(true);
	
	//m_pCamera->setPosition( vector3df( 0, 0, -5e5 ) );
	//auto warpAni = new MySceneNodeAnimatorMove( 4000, 3000, m_pCamera->getPosition(), vector3df( 0, 0, -1e5) );
	//m_pCamera->addAnimator( warpAni );
	//m_pCamera->setRotation(vector3df(0));
	//warpAni->drop();

	//加载行星
	auto planet = smgr->addSphereSceneNode( 4e5 );
	if ( planet )
	{
		// 设置名称
		planet->setName( "planet1" );
		// 加载纹理
		planet->setMaterialTexture( 0, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/planet6.jpg") ) );
		// 星球自转
		auto rot = smgr->createRotationAnimator( vector3df( 0, 0.003f, 0) );
		planet->addAnimator( rot );
		rot->drop();
		// 设置初始大小
		planet->setScale( vector3df( .01f ) );
		// 缩放动画
		auto sca = new MySceneNodeAnimatorScale( 0, 8000, vector3df( 1.99f ), AS_MT_LOG );
		planet->addAnimator( sca );
		sca->drop();
		// 行星永远相对镜头
		auto relstayAni = new RelateCameraAnimatorStay( 0, 1000, m_pCamera, vector3df( -2e5, 0, 8e5 ) );
		planet->addAnimator( relstayAni );
		relstayAni->drop();
	}

	//加载卫星
	auto moon = smgr->addSphereSceneNode( 1e5 );
	if ( moon )
	{
		// 设置名称
		moon->setName( "moon1" );
		// 加载纹理
		moon->setMaterialTexture( 0, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/planet1.jpg") ) );
		// 星球自转
		auto rot = smgr->createRotationAnimator( vector3df( 0, -0.006f, 0) );
		moon->addAnimator( rot );
		rot->drop();
		// 设置初始大小
		moon->setScale( vector3df( .001f ) );
		//moon->setVisible( false );
		// 缩放动画
		auto sca = new MySceneNodeAnimatorScale( 2000, 6000, vector3df( 1.999f ), AS_MT_LOG, 500 );
		moon->addAnimator( sca );
		sca->drop();
		// 飞跃星球效果
		auto relmovAni = new RelateCameraAnimatorMove( 2000, 6000, m_pCamera,
			vector3df(1e5, 0, 2.5e5), vector3df(1e5, 0, -2.5e5), RM_MT_LOG, 800 );
		moon->addAnimator( relmovAni );
		relmovAni->drop();
	}



	//加载空间站模型
	IMeshSceneNode* station = smgr->addMeshSceneNode( smgr->getMesh( _T("../modle/station/cs1.obj") ) );
	if ( station )
	{
		// 设置名字
		station->setName( "station1" );
		// 设置初始大小
		//station->setScale( vector3df( .001f));
		//station->setVisible(false);
		// 缩放动画
		//auto sca = new MySceneNodeAnimatorLogScale( 5000, 5000, vector3df( 1.999f ), 500 );
		//moon->addAnimator( sca );
		//sca->drop();
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
	light1.SpecularColor = video::SColorf( 0.1f, 0.1f, 0.1f );
	light1.AmbientColor = video::SColorf( 0.15f, 0.15f, 0.15f );
	//light1.AmbientColor = video::SColorf( 0,0,0 );
	auto lsn = smgr->addLightSceneNode();
	lsn->setLightData( light1 );
	lsn->setRotation( vector3df( 0, 90, 0 ) );

	//try
	//{
	//	object modelLoader = p->GetModelLoader();
	//	object MultiplayerLoad = modelLoader.attr( "MultiplayerLoad" );
	//	MultiplayerLoad();
	//}
	//catch ( ... )
	//{
	//	PyErr_Print();
	//}


//	m_pAnimationMan = pEngine->GetAnimationManager();



	//// 加载模型和动画
	//auto bottleNode = m_pModelMan->AddSceneNodeFromMesh( _T("bottle") );

	////ISceneNodeAnimator* anim = new CSceneNodeAnimatorSelfDelFlyStraight( vector3df( 0, 0, 0 ),
	////	vector3df( 0, 1000, 1000 ), 5000, pEngine->GetDevice()->getTimer()->getTime() );
	//ISceneNodeAnimator* anim = new CSceneNodeAnimatorAutoTrack( smgr );
	//bottleNode->addAnimator( anim );
	//anim->drop();

	//for ( auto iter = m_pModelMan->GetISceneNodeList().begin(); iter != m_pModelMan->GetISceneNodeList().end(); ++iter )
	//{
	//	ISceneNodeAnimator* anim = new Chuoyanshuxing( smgr );
	//	(*iter)->addAnimator( anim );
	//	//(*iter)->setScale( vector3df( 1000, 1000, 1000 ) );
	//	anim->drop();
	//}

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

