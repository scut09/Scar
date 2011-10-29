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
IUIObject* Shield1;	// 护盾槽满
IUIObject* Shield2;	// 护盾槽空
IUIObject* Armor1;	// 护甲槽满
IUIObject* Armor2;	// 护甲槽空
IUIObject* Gradienter;	// 水平仪
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

	f32 ratio;
	f32 border;
	// 绘制速度槽
	ratio = cf1->GetVelocity() / cf1->GetMaxSpeed();
	border = 389 * ( 1 - ratio );
	Speed1->SetSourceRect( vector2df( 0, border ), vector2df( 98, 389 ) );
	Speed2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 98, border ) );	
	// 绘制护盾槽
	ratio = cf1->GetShield() / cf1->GetMaxShield();
	border = 389 * ( 1 - ratio );
	Shield1->SetSourceRect( vector2df( 0, border ), vector2df( 100, 389 ) );
	Shield2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 100, border ) );
	// 绘制护甲槽
	ratio = cf1->GetArmor() / cf1->GetMaxArmor();
	border = 360 * ( 1 - ratio );
	Armor1->SetSourceRect( vector2df( 0, border ), vector2df( 93, 360 ) );
	Armor2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 93, border ) );

	// 水平仪转动
	Gradienter->SetRotation( m_pCamera->getRotation().Z );
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

	// 创建飞船
	auto sh = new CFrigate( smgr->getMesh("../module/1234.obj"), 0, smgr, -1 );
	

	//cf1->setPosition( vector3df( 0, 0, 50 ) );
	// 创建子弹
	bullet = new BulletNode( smgr );
	bullet->setMaterialTexture( 0, driver->getTexture( "../media/Weapon/bullet.png" ) );
	bullet->SetVelocity( 1000 );
	bullet->SetInterval( 100 );
	cf1->AddGun( bullet );

	//  加入摄像机
	//m_pCamera = smgr->addCameraSceneNodeFPS( 0, 100, 50.0f );
	m_pCamera = smgr->addCameraSceneNode();
	auto fpsAni = new CSceneNodeAnimatorAircraftFPS( pEngine->GetDevice()->getCursorControl(), cf1 );
	m_pCamera->addAnimator( fpsAni );
	fpsAni->drop();
	m_pCamera->setFOV( 1 );
	m_pCamera->setFarValue( 1e7f );
	/*auto shakeAni = new MySceneNodeAnimatorShake( 0, 80000, 1.2f );
	m_pCamera->addAnimator( shakeAni );
	shakeAni->drop();*/

	// 飞船跟随照相机
	auto folowAni = new SceneNodeAnimatorFollow( m_pCamera, -40 );
	cf1->addAnimator( folowAni );
	folowAni->drop();

	// 创建火控
	auto fireAni = new FireAnimator( m_pCamera );
	cf1->addAnimator( fireAni );
	fireAni->drop();

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
	IAnimatedMeshSceneNode* station = smgr->addAnimatedMeshSceneNode( smgr->getMesh( _T("../modle/station/cs1.obj") ) );
	if ( station )
	{
		// 设置名字
		station->setName( "station1" );

		//// 创建碰撞的三角形选择器以支持碰撞检测
		//scene::ITriangleSelector* selector = 
		//	MyIrrlichtEngine::GetEngine()->GetSceneManager()->createTriangleSelector( station );
		//station->setTriangleSelector(selector);
		//selector->drop();

		// 设置初始大小
		//station->setScale( vector3df( .001f));
		//station->setVisible(false);
		// 缩放动画
		//auto sca = new MySceneNodeAnimatorLogScale( 5000, 5000, vector3df( 1.999f ), 500 );
		//moon->addAnimator( sca );
		//sca->drop();
	}
	//driver->setFog(video::SColor(0,138,125,81), video::EFT_FOG_LINEAR, 250, 1000, .003f, true, false);
	//IAnimatedMesh* stationMesh = smgr->getMesh( "../modle/station/cs1.3ds" );
	//ITexture* normalMap = driver->getTexture( "../modle/station/cs1_tex_ngs.jpg" );
	//if ( normalMap )
	//	driver->makeNormalMapTexture( normalMap, 9 );
	//IMesh* tangentMesh = smgr->getMeshManipulator()->
	//	createMeshWithTangents(stationMesh->getMesh(0));
	//ISceneNode* station = smgr->addMeshSceneNode( tangentMesh );
	//tangentMesh->drop();
	//station->setMaterialTexture( 0, driver->getTexture( "../modle/station/cs1_tex_d.jpg"));
	////station->getMaterial( 0 ).SpecularColor.set(0,0,0,0);
	////station->getMaterial( 0 ).MaterialTypeParam = 0.035f;
	////station->getMaterial( 0 ).AmbientColor.set(255);
	////station->getMaterial( 0 ).DiffuseColor.set(255);
	//station->setMaterialTexture( 1, normalMap );
	////station->setMaterialFlag( EMF_FOG_ENABLE, true );
	//station->setMaterialType( EMT_NORMAL_MAP_SOLID );
	//station->setMaterialFlag( EMF_LIGHTING, true );
	//smgr->addLightSceneNode( 0, vector3df(1000), SColorf(1), 10000.0f );

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
	Cursor = uiManager->GetObjectByName("cursor");
	// 获取速度槽
	Speed1 = uiManager->GetObjectByName( "speed1" );
	Speed2 = uiManager->GetObjectByName( "speed2" );
	// 获取护盾槽
	Shield1 = uiManager->GetObjectByName( "shield1");
	Shield2 = uiManager->GetObjectByName( "shield2");
	// 获取护甲槽
	Armor1 = uiManager->GetObjectByName( "armor1");
	Armor2 = uiManager->GetObjectByName( "armor2");
	// 获取水平仪
	Gradienter = uiManager->GetObjectByName( "gradienter" );

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
	dynamic_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [ fireAni, pEngine ]( const SEvent& event )->void*
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

