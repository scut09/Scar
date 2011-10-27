/********************************************************************
    创建时间: 2011-10-8   16:01
    文件名:   MultiplayerScene.cpp
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     多人游戏场景

*********************************************************************/

#include "Boost_Client.h"
#include "Boost_Server.h"
#include "GameBag.h"

#include "MultiplayerScene.h"
#include "PythonManager.h"
#include "EngineHeader.h"
#include <iostream>
#include "FlyBehavior.h"
#include "CSceneNodeAnimatorSelfDelFlyStraight.h"
#include "Flame.h"
#include "AllAnimators.h"
#include "AllUIObjects.h"
#include "UIAnimators.h"
#include "UIManager.h"
#include "Frigate.h"
#include "BulletNode.h"

#include "irrKlang.h"
using namespace irrklang;

Network::BoostServer server;

Network::BoostClient client;

//scene::ISceneNode* node;
UIManager* uiManager; //测试用

IUIObject* root;	//测试用

IUIObject* Cursor;	// 鼠标准心
IUIObject* Speed1;	// 速度槽慢
IUIObject* Speed2;	// 速度槽空
IShip* cf1;
BulletNode* bullet;	// 子弹

ISoundEngine* pSoundEngine;
ISoundSource* fuck;

bool bRunOnce = true;

void MultiplayerScene::Run()
{
	if ( bRunOnce )
	{
		bRunOnce = false;

		Sleep( 1000 );

		auto rooms = client.GetRooms();
		auto localIP = client.GetLocalIP();

		auto iter = rooms.begin();
		for ( ; iter != rooms.end(); ++iter )
		{
			std::cout << "Room " << iter->first << " ";
			std::wcout << iter->second.room_name << std::endl;

			if ( rooms.size() > 1 && localIP.find( iter->first ) == localIP.end() )		// 非本机IP
			{	
				std::cout << "enter " << iter->first << std::endl;
				client.EnterRoom( iter->first );
				break;
			}
		}

		if ( iter == rooms.end() )
			client.EnterRoom( *localIP.begin() );		

		Sleep( 2000 );

		//client.Send( "192.168.1.121" );

		std::cout << "m_index " << client.m_index << std::endl;

	}

	auto pos = m_pCamera->getPosition();
	client.SendHeroMove( client.m_index, pos.X, pos.Y, pos.Z );
	auto rot = m_pCamera->getRotation();
	client.SendHeroRot( client.m_index, rot.X, rot.Y, rot.Z );


	// 准心追随鼠标
	auto CursorPos = MyIrrlichtEngine::GetEngine()->GetDevice()->getCursorControl()->getPosition();
	Cursor->SetPosition( vector2df( (f32)CursorPos.X, (f32)CursorPos.Y ) );

	// 绘制速度槽
	f32 ratio = cf1->GetVelocity() / cf1->GetMaxSpeed();
	f32 border = 389 * ( 1 - ratio );
	Speed1->SetSourceRect( vector2df( 0, border ), vector2df( 98, 389 ) );
	Speed2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 98, border ) );	
}

void MultiplayerScene::Init()
{
	server.Start( 1990, 2012 );
	client.Start( 2012, 1990 );

	// 获取引擎
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	scene::ISceneManager* smgr = pEngine->GetSceneManager();
	m_pModelMan = pEngine->GetModelManager();
	auto driver = pEngine->GetVideoDriver();

	// 隐藏鼠标
	pEngine->GetDevice()->getCursorControl()->setVisible(false);

	// 创建飞船
	cf1 = new CFrigate( smgr->getMesh("../module/1234.obj"), 0, smgr, -1 );
	//m_pCamera->addChild( cf1 );
	cf1->setPosition( vector3df( 0, 0, 50 ) );
	// 创建子弹
	bullet = new BulletNode( smgr->getMesh("../module/mayabottle.obj"), 0, smgr, -1,
		vector3df(0,0,0), vector3df(0), vector3df(1) );
	//bullet->setVisible( true );
	cf1->AddGun( bullet );
	// 创建火控
	auto fireAni = new FireAnimator();
	cf1->addAnimator( fireAni );
	fireAni->drop();

	//  加入摄像机
	//m_pCamera = smgr->addCameraSceneNodeFPS( 0, 100, 50.0f );

	m_pCamera = smgr->addCameraSceneNode();
	auto fpsAni = new CSceneNodeAnimatorAircraftFPS( pEngine->GetDevice()->getCursorControl(), cf1 );
	m_pCamera->addAnimator( fpsAni );
	fpsAni->drop();
	m_pCamera->setFOV( 1 );
	m_pCamera->setFarValue( 1e7f );
	/*auto shakeAni = new MySceneNodeAnimatorShake( 0, 8000, 1.2f );
	m_pCamera->addAnimator( shakeAni );
	shakeAni->drop();
	m_pCamera->bindTargetAndRotation(true);*/

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
		//// 设置初始大小
		//planet->setScale( vector3df( .01f ) );
		//// 缩放动画
		//auto sca = new MySceneNodeAnimatorScale( 0, 8000, vector3df( 1.99f ), AS_MT_LOG );
		//planet->addAnimator( sca );
		//sca->drop();
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
		//// 设置初始大小
		//moon->setScale( vector3df( .001f ) );
		//// 缩放动画
		//auto sca = new MySceneNodeAnimatorScale( 2000, 6000, vector3df( 1.999f ), AS_MT_LOG, 500 );
		//moon->addAnimator( sca );
		//sca->drop();
		//// 飞跃星球效果
		//auto relmovAni = new RelateCameraAnimatorMove( 2000, 6000, m_pCamera,
		//	vector3df(1e5, 0, 2.5e5), vector3df(1e5, 0, -2.5e5), RM_MT_LOG, 800 );
		//moon->addAnimator( relmovAni );
		//relmovAni->drop();
		// 卫星永远相对镜头
		auto relstayAni = new RelateCameraAnimatorStay( 0, 1000, m_pCamera, vector3df( 1e5, 0, 2.5e5 ) );
		moon->addAnimator( relstayAni );
		relstayAni->drop();
	}

	pSoundEngine = createIrrKlangDevice();
	fuck = pSoundEngine->addSoundSourceFromFile("../media/booster_blue_b02a.ogg");
		//fuck->setVolume( fuck->getVolume() - 10 );

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

	// 加载UI界面
	uiManager = new UIManager( pEngine->GetDevice()->getTimer() );
	try
	{
		using namespace boost::python;

		object UILoader = import( "MultiPlayIni" );
		object GetRoot = UILoader.attr( "GetRoot" );
		object root = GetRoot();

		IUIObject* r = extract<IUIObject*>( root ); 
		uiManager->SetRoot( r );
		//r->drop();	// 使用Python对象不用内存管理
	}
	catch ( ... )
	{
		PyErr_Print();
	}
	// 获取鼠标准心
	Cursor = uiManager->GetRoot()->GetChildren()[3];
	// 获取速度槽
	Speed1 = uiManager->GetRoot()->GetChildren()[4];
	Speed2 = uiManager->GetRoot()->GetChildren()[5];

	try
	{
		// 使用Python模块加载模型
		PythonManager* p = PythonManager::GetPythonManager();
		object modelLoader = p->GetModelLoader();
		object MultiplayerLoad = modelLoader.attr( "MultiplayerLoad" );
		MultiplayerLoad();
	}
	catch ( ... )
	{
		PyErr_Print();
	}


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
	static_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [ fireAni, pEngine ]( const SEvent& event )->void*
	{	
		fireAni->OnEvent( event );
		//control.OnEvent( event );
		//pEngine;		// 引擎指针
		/*if (event.EventType == EET_KEY_INPUT_EVENT )
		{
			if (event.KeyInput.Key == KEY_KEY_W )
			{
				pSoundEngine->play2D( fuck );
			}
		}*/
		return 0;
	} );
	

	client.QueryRoom();


}

void MultiplayerScene::Release()
{
	if ( uiManager )
		delete uiManager;

	m_pCamera->remove();
	m_pSkyBox->remove();

//	m_pAnimationMan->RemoveAll();

	m_pModelMan->DeleteAll();

	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	scene::ISceneManager* smgr = pEngine->GetSceneManager();
	smgr->clear();
}

void MultiplayerScene::Draw()
{
	uiManager->RunTree();
}

