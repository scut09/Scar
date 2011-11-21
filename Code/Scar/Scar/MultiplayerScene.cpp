/********************************************************************
创建时间: 2011-10-8   16:01
文件名:   MultiplayerScene.cpp
作者:     华亮 Cedric Porter [ Stupid ET ]	
说明:     多人游戏场景

*********************************************************************/


#include "AllAnimators.h"
#include "AllUIObjects.h"
#include "BulletNode.h"
#include "CSceneNodeAnimatorSelfDelFlyStraight.h"
#include "EngineHeader.h"
#include "Flame.h"
#include "Frigate.h"
#include "MultiplayerScene.h"
#include "MySceneManager.h"
#include "PlayerManager.h"
#include "PythonManager.h"
#include "RobotShip.h"
#include "Robot_Client.h"
#include "SpriteFlame.h"
#include "UIAnimators.h"
#include "UIManager.h"
#include <iostream>
#include "HumanPlayer.h"
#include "MySceneManager.h"
#include "GeneralCallBack.h"
#include "PythonWrapper.h"
#include "RunWay.h"
#include "LaserNode.h"

#define PRINT_POS( pos ) std::cout << #pos ## " " << pos.X << ' ' << pos.Y << ' ' << pos.Z << std::endl;

LaserNode * laser1;


using namespace irrklang;

template< class T >
struct Fuck
{
	T data;
	Fuck( T d ) : data( d ) {}
};

MultiplayerScene::~MultiplayerScene()
{
	Release();

	// Test
	new Fuck< boost::shared_ptr<Network::BoostClient> >( client );
	new Fuck< boost::shared_ptr<Network::BoostServer> >( server );
}


void MultiplayerScene::Run()
{
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	ISceneManager* smgr = pEngine->GetSceneManager();
	IVideoDriver* driver = pEngine->GetVideoDriver();
	boost::shared_ptr<UIManager> uiManager = pEngine->GetUIManager();
	boost::shared_ptr<IPlayer> player = pEngine->GetCurrentPlayer();
	shader = new SceneNodeShader();

	switch ( State )
	{
	case Select_Camp:
		{
			// 如果是第一次运行，初始化
			if ( bRunOnce )
			{
				bRunOnce = false;
				// 在此处进行初始化工作
				// 装载场景
				try
				{
					using namespace boost::python;
					object map = import( "SelectCampScene" );
					object LoadMap = map.attr( "LoadMap" );
					LoadMap();
				}
				catch ( ... )
				{
					PyErr_Print();
				}

				 // 显示选择阵营菜单
				/*IUIObject* scMenu = uiManager->GetUIObjectByName( "scMenu" );
				scMenu->SetVisible( true );
				scMenu->SetAlpha( 0 );
				IUIAnimator* alpAni = uiManager->CreateAnimatorAlphaChange( 0, 1000, 0, 255 );
				scMenu->AddAnimator( alpAni );
				alpAni->drop();*/

				// 恒星
				/*Sun = smgr->addBillboardSceneNode( 0, dimension2df( 256, 256 ) );
				Sun->setName("Sun");
				Sun->setMaterialTexture( 0, driver->getTexture( "../media/Space/sun.tga" ) );
				auto ani = pEngine->GetMySceneManager()->createRelateCameraStayAnimator(
					0, 1000, m_pCamera, vector3df(0,0,250), true );
				Sun->addAnimator( ani );
				ani->drop();
				Sun->setMaterialFlag( EMF_ZBUFFER, false );
				Sun->setMaterialFlag( EMF_LIGHTING, false );
				Sun->setMaterialType( EMT_TRANSPARENT_ADD_COLOR );*/
				// 行星与卫星
				Planet1 = pEngine->GetMySceneManager()->getSceneNodeFromName( "planet1" );
				Planet2 = pEngine->GetMySceneManager()->getSceneNodeFromName( "planet2" );
			}

			// 在此处进行游戏逻辑

			
			//if ( player->GetTeam() != 0 )
			//{
			//	State = Select_Ship;
			//	// 在此处释放资源或隐藏资源
			//	bRunOnce = true;
			//}
		}
		break;
	case Select_Ship:
		{

		}
		break;
	case Select_Equipment:
		{

		}
		break;
	case First_Flight:
		{

		}
		break;
	case Warp:
		{

		}
		break;
	case In_Battle:
		{
			InBattle();
			laser1->build();
		}
		break;
	case Dead:
		{

		}
		break;
	case Game_Over:
		{

		}
		break;
	case Quit:
		{

		}
		break;
	case Test:
		{
			InitScene();
			TestFuck();
			State = In_Battle;
		}
		break;
	}

		PRINT_POS(smgr->getActiveCamera()->getPosition());
}

void MultiplayerScene::Init()
{
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	IVideoDriver* driver = pEngine->GetVideoDriver();

	// 初始化状态为选阵营  测试可以将此处改为想要的状态
	State = Select_Camp;

	// 兼容Test状态
	if ( State != Test )
	{
		// 初始化摄像机
		m_pCamera = pEngine->GetSceneManager()->addCameraSceneNodeFPS();
		//m_pCamera = pEngine->GetSceneManager()->addCameraSceneNode();
		m_pCamera->setFarValue( 1e7 );
		m_pCamera->setFOV( 1 );
		m_pCamera->setAspectRatio( (f32)driver->getScreenSize().Width / (f32)driver->getScreenSize().Height );

		// 初始化玩家与飞船
		// 飞船为默认值，在玩家选船后更换模型
		IShip* playerShip = pEngine->GetMySceneManager()->addFrigateSceneNode( L"../model/ship/cf1.obj" );
		playerShip->setVisible( false );
		boost::shared_ptr<HumanPlayer> player = boost::shared_ptr<HumanPlayer>( new HumanPlayer( playerShip ) );
		pEngine->SetCurrentPlayer( player );

		// 加载UI界面
		pEngine->SetUIManager( boost::shared_ptr<UIManager>( new UIManager( pEngine->GetDevice()->getTimer() ) ) );
		try
		{
			using namespace boost::python;

			object UILoader = import( "MultiPlayIni" );
			object GetRoot = UILoader.attr( "GetRoot" );
			object root = GetRoot();	
		}
		catch ( ... )
		{
			PyErr_Print();
		}

		// 测试用
		/*m_playerManager = boost::shared_ptr<PlayerManager>( new PlayerManager );
		m_playerHelper = boost::shared_ptr<PlayerHelper>( new PlayerHelper );*/
		//m_playerHelper->LoadHelperUI( pEngine->GetUIManager() );
		//m_playerHelper->LoadPlayerManager( &*m_playerManager );

		// 创建控制台
		IGUIEnvironment* gui = MyIrrlichtEngine::GetEngine()->GetDevice()->getGUIEnvironment();
		IGUISkin* skin = gui->getSkin();
		IGUIFont* font = gui->getFont("../media/fonthaettenschweiler.bmp");
		if (font)
			skin->setFont(font);
		skin->setFont( gui->getBuiltInFont(), EGDF_TOOLTIP );
		console = gui->addStaticText( _T(""), core::rect<s32>( 0, 20, 500, 600 ), true, true, 0, -1, true );
		console->setVisible(false);

		dynamic_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [this]( const SEvent& event )->void*
		{	
			MyIrrlichtEngine::GetEngine()->GetUIManager()->OnEvent( event );

			if ( event.KeyInput.PressedDown )
			{
				if ( event.KeyInput.Key == KEY_F1 )
				{
					console->setVisible( ! console->isVisible() );
					if ( console->isVisible() )
					{
						UpdateConsole();
						//gui->setFocus( console );
					}
				}
			}

			return 0;
		} );

	}
}

void MultiplayerScene::Release()
{
	//	m_playerManager->RemoveAll();

	try
	{
		//if ( client.use_count() > 0 && server.use_count() > 0 )
		//{
		//	client->Close();
		//	server->Close();
		//}
	}
	catch ( std::exception& e )
	{
		std::cerr << e.what() << std::endl;
	}
	catch ( ... )
	{
		std::cerr << "client" << std::endl;

	}



	//	m_pAnimationMan->RemoveAll();


}

void MultiplayerScene::Draw()
{
	//uiManager->RunTree();
	MyIrrlichtEngine::GetEngine()->GetUIManager()->DrawAll();
}

void MultiplayerScene::InitScene()
{
	// 获取引擎
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	scene::ISceneManager* smgr = pEngine->GetSceneManager();
	smgr->clear();

	m_pModelMan = pEngine->GetModelManager();
	IVideoDriver* driver = pEngine->GetVideoDriver();

	shader = new SceneNodeShader();


	// 隐藏鼠标
	pEngine->GetDevice()->getCursorControl()->setVisible(false);


	// 创建飞船
	IShip* cf1;
	IMesh* cf1Mesh = smgr->getMesh( _T("../model/ship/cf1.obj") )->getMesh(0);
	if ( cf1Mesh )
	{
		IMesh* tangentMesh = smgr->getMeshManipulator()->createMeshWithTangents(cf1Mesh, true);
		cf1 = new CFrigate( tangentMesh, 0, smgr, -1 );	
		cf1->setName( "cf1" );
		cf1->setMaterialTexture( 1, driver->getTexture(_T("../model/ship/caldarifighter_tex_ngs.tga")) );
		cf1->setMaterialFlag( EMF_BACK_FACE_CULLING, false );
		GeneralCallBack* cb = new GeneralCallBack( cf1 );
		shader->ApplyShaderToSceneNode( cf1, cb, "Shader/cf_1V.vert", "Shader/cf_1F.frag" );
		cb->drop();
		tangentMesh->drop();
	}
	//cf1->setPosition( vector3df(0,-40,0)); 

	//m_playerHelper.LoadPlayerShip( boost::shared_ptr<)

	//飞船尾焰
	SpriteFlame spf;
	spf.SetOffset( vector3df( -6, 0, -22 ) );
	spf.AddFlameToShip( cf1, smgr );
	spf.SetOffset( vector3df( 6, 0, -22 ) );
	spf.AddFlameToShip( cf1, smgr );

	// 创建子弹
	BulletNode* bullet = new BulletNode( smgr, smgr->getRootSceneNode() );
	bullet->setMaterialTexture( 0, driver->getTexture( "../media/Weapon/bullet.png" ) );
	bullet->SetVelocity( 1000 );
	bullet->SetInterval( 100 );
	cf1->AddGun( bullet );
	bullet->drop();

	//  加入摄像机
	//m_pCamera = smgr->addCameraSceneNodeFPS( 0, 100, 50.0f );
	m_pCamera = smgr->addCameraSceneNode();

	auto fpsAni = new CSceneNodeAnimatorAircraftFPS( pEngine->GetDevice()->getCursorControl() );
	cf1->addAnimator( fpsAni );
	fpsAni->drop();

	m_pCamera->setFOV( 1 );
	m_pCamera->setFarValue( 1e7f );

	/*auto shakeAni = new MySceneNodeAnimatorShake( 0, 80000, 1.2f );
	m_pCamera->addAnimator( shakeAni );
	shakeAni->drop();*/

	// 开场动画
	auto BeginMove = new TheBeginMove( vector3df(50000),vector3df(0), 1000, 5000, 1 );
	m_pCamera->addAnimator( BeginMove );
	BeginMove->drop();

	//m_pCamera->setParent( cf1 );
	// 飞船跟随照相机
	auto folowAni = new CSceneNodeAnimatorCameraFollowShip( cf1, 30 );
	m_pCamera->addAnimator( folowAni );
	folowAni->drop();

	//加载行星
	auto planet = smgr->addSphereSceneNode( 4e5, 64 );
	if ( planet )
	{
		// 设置名称
		planet->setName( "planet1" );
		// 加载纹理
		planet->setMaterialTexture( 0, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/planet5.jpg") ) );
		planet->setMaterialTexture( 1, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/night0.jpg") ) );
		planet->setMaterialTexture( 2, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/a.tga") ) );
		// 星球自转
		auto rot = smgr->createRotationAnimator( vector3df( 0, 0.005f, 0) );
		planet->addAnimator( rot );
		rot->drop();
		// Shader
		GeneralCallBack* cb = new GeneralCallBack( planet );
		shader->ApplyShaderToSceneNode( planet, cb, "Shader/PlanetGroundV.vert", "Shader/PlanetGroundF.frag" );
		cb->drop();
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
	// 行星大气圈
	ISceneNode* planetAtmos = smgr->addSphereSceneNode( 4.2e5, 64, planet );
	if ( planetAtmos )
	{
		planetAtmos->setMaterialFlag( EMF_BACK_FACE_CULLING, false );
		planetAtmos->setMaterialFlag( EMF_FRONT_FACE_CULLING, true );
		//planetAtmos->setMaterialFlag( EMF_ZBUFFER, false );
		GeneralCallBack* cb = new GeneralCallBack( planetAtmos );
		// Shader
		shader->ApplyShaderToSceneNode( planetAtmos, cb, "Shader/PlanetAtmosV.vert", "Shader/PlanetAtmosF.frag",EMT_TRANSPARENT_ADD_COLOR );
		cb->drop();
	}


	//加载卫星
	auto moon = smgr->addSphereSceneNode( 1e5, 64 );
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

	IMesh* stationMesh = smgr->getMesh( _T("../model/station/cs1.obj") );
	if ( stationMesh )
	{
		IMesh* tangentMesh = smgr->getMeshManipulator()->createMeshWithTangents(stationMesh, true);
		IMeshSceneNode* station = smgr->addMeshSceneNode( tangentMesh );
		station->setName( "station1" );
		station->setMaterialTexture( 1, driver->getTexture(_T("../model/station/cs1_tex_ngs.tga")) );
		GeneralCallBack* cb = new GeneralCallBack( station );
		shader->ApplyShaderToSceneNode( station, cb, "Shader/cs_1V.vert", "Shader/cs_1F.frag" );
		cb->drop();
		tangentMesh->drop();
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

	m_playerManager = boost::shared_ptr<PlayerManager>( new PlayerManager );
	m_playerHelper = boost::shared_ptr<PlayerHelper>( new PlayerHelper );

	// 加载UI界面
	pEngine->SetUIManager( boost::shared_ptr<UIManager>( new UIManager( pEngine->GetDevice()->getTimer() ) ) );

	try
	{
		using namespace boost::python;

		object UILoader = import( "MultiPlayIni" );
		object GetRoot = UILoader.attr( "GetRoot" );
		object root = GetRoot();

		m_playerHelper->LoadHelperUI( pEngine->GetUIManager() );
		m_playerHelper->LoadPlayerManager( &*m_playerManager );

		object map = import( "MapV1" );
		object LoadMap = map.attr( "LoadMap" );
		LoadMap();

	}
	catch ( ... )
	{
		PyErr_Print();
	}



	boost::shared_ptr<HumanPlayer>	humanPlayer( new HumanPlayer( cf1 ) );
	m_playerHelper->LoadPlayer( humanPlayer );
	m_playerManager->AddPlayer( humanPlayer );

	//playerManager = new PlayerManager( uiManager, cf1 );

	//playerManager->AddPlayer( cf1->getID(), cf1 );

	try
	{
		server = pEngine->GetServer();//boost::shared_ptr<Network::BoostServer>( new Network::BoostServer );
		if ( server.use_count() == 0 )
		{
			CreateRoom();
			server = pEngine->GetServer();
		}
		client = pEngine->GetClient();//boost::shared_ptr<Network::BoostClient>( new Network::BoostClient( &*m_playerManager ) );
		if ( client.use_count() == 0 )
		{
			auto playerManager = boost::shared_ptr<PlayerManager>( new PlayerManager );
			client = boost::shared_ptr<Network::BoostClient>( new Network::BoostClient( playerManager ) );
			pEngine->SetClient( client );
			client->Start( 2012, 1990 );
		}
	}
	catch ( std::exception& e )
	{
		std::cerr << e.what() << std::endl;
	}

	//server->Start( 1990, 2012 );
	//client->Start( 2012, 1990 );



	// 添加robot
	IShip* npc;
	boost::shared_ptr<ShipAgentPlayer> robot;
	// robot 1
	npc = new CFrigate( smgr->getMesh("../module/1234.obj"), 0, smgr, 99 );
	npc->SetMaxSpeed( 2 );
	npc->setPosition( vector3df( (f32)(rand() % 100), (f32)(rand() % 100), (f32)(1000 + rand() % 1000) ) );
	spf.SetOffset( vector3df( -6, 0, -22 ) );
	spf.AddFlameToShip( npc, smgr );
	spf.SetOffset( vector3df( 6, 0, -22 ) );
	spf.AddFlameToShip( npc, smgr );
	bullet = new BulletNode( smgr, smgr->getRootSceneNode() );
	bullet->setMaterialTexture( 0, driver->getTexture( "../media/Weapon/bullet.png" ) );
	bullet->SetVelocity( 1000 );
	bullet->SetInterval( 100 );
	npc->AddGun( bullet );
	bullet->drop();	
	robot = boost::shared_ptr<ShipAgentPlayer>( new ShipAgentPlayer( npc, &*m_playerManager, server ) );
	m_playerManager->AddPlayer( robot );
	// robot 2
	npc = new CFrigate( smgr->getMesh("../module/1234.obj"), 0, smgr, 98 );
	npc->SetMaxSpeed( 2 );
	npc->setPosition( vector3df( (f32)(rand() % 100), (f32)(rand() % 100), (f32)(1000 + rand() % 1000) ) );
	spf.SetOffset( vector3df( -6, 0, -22 ) );
	spf.AddFlameToShip( npc, smgr );
	spf.SetOffset( vector3df( 6, 0, -22 ) );
	spf.AddFlameToShip( npc, smgr );
	bullet = new BulletNode( smgr, smgr->getRootSceneNode() );
	bullet->setMaterialTexture( 0, driver->getTexture( "../media/Weapon/bullet.png" ) );
	bullet->SetVelocity( 1000 );
	bullet->SetInterval( 100 );
	npc->AddGun( bullet );
	bullet->drop();	
	robot = boost::shared_ptr<ShipAgentPlayer>( new ShipAgentPlayer( npc, &*m_playerManager, server ) );
	m_playerManager->AddPlayer( robot );

	laser1 = new LaserNode( smgr->getMesh(_T("../model/weapon/cylinder.3ds") ), 0, smgr, -1, npc, cf1 );
	laser1->setMaterialTexture( 0, driver->getTexture( "../model/weapon/sphere_capmask.png" ) );
	laser1->setMaterialFlag( EMF_BACK_FACE_CULLING, false );
	SceneNodeShader shader;
	GeneralCallBack* newCB = new GeneralCallBack( laser1 );
	shader.ApplyShaderToSceneNode( laser1, newCB, "", "Shader/Laser1.frag", EMT_TRANSPARENT_ADD_COLOR );
	newCB->drop();

	// 创建火控
	auto fireAni = new ShipFireAnimator( client );
	cf1->addAnimator( fireAni );
	fireAni->drop();

	//
	client->QueryRoom();

	//

	IGUIEnvironment* gui = MyIrrlichtEngine::GetEngine()->GetDevice()->getGUIEnvironment();
	IGUISkin* skin = gui->getSkin();
	IGUIFont* font = gui->getFont("../media/fonthaettenschweiler.bmp");
	if (font)
		skin->setFont(font);

	skin->setFont( gui->getBuiltInFont(), EGDF_TOOLTIP );

	IGUIEditBox* box = gui->addEditBox( _T(""), core::rect<s32>( 0, 0, 100, 50 ) );


	console = gui->addStaticText( _T(""), core::rect<s32>( 0, 20, 500, 600 ), true, true, 0, -1, true );
	console->setVisible(false);


	//	gui->addScrollBar( false, core::recti( 0, 0, 200, 200 ), console );

	box->setVisible( false );

	//auto as = core::rect<s32>;

	MyIrrlichtEngine::GetEngine()->SetMotionBlur( true );

	console->setText( _T("Press F1 to show or close this box" ) );

	// 创建并注册receiver的事件处理回调函数
	dynamic_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc(
		[ this, gui, box ]( const SEvent& event )->void*
	{	
		m_playerManager->OnEvent( event );

		if ( event.KeyInput.PressedDown )
		{
			if ( event.KeyInput.Key == KEY_KEY_T )
			{
				box->setText( _T("") );
				box->setVisible( true );
				gui->setFocus( box );		
			}
			else if ( event.KeyInput.Key == KEY_RETURN )
			{
				box->setVisible( false );
				gui->setFocus( 0 );		
				client->BroadcastMessage( client->m_index, box->getText() );
				std::wcout << box->getText() << std::endl;
			}
			else if ( event.KeyInput.Key == KEY_ESCAPE )
			{
				box->setVisible( false );
				gui->setFocus( 0 );		
			}
			else if ( event.KeyInput.Key == KEY_KEY_I )
			{
				MyIrrlichtEngine::GetEngine()->SetMotionBlur( true );
			}
			else if ( event.KeyInput.Key == KEY_KEY_O )
			{
				MyIrrlichtEngine::GetEngine()->SetMotionBlur( false );
			}
			else if ( event.KeyInput.Key == KEY_F1 )
			{
				console->setVisible( ! console->isVisible() );
				if ( console->isVisible() )
				{
					UpdateConsole();
					//gui->setFocus( console );
				}
			}
			else if ( event.KeyInput.Key == KEY_KEY_P )
			{
				auto smgr = MyIrrlichtEngine::GetEngine()->GetGameSceneManager();
				smgr->SetCurrentGameScene( smgr->GetSceneByName( "MainMenu" ) );
			}
		}
		return 0;
	} );


}

void MultiplayerScene::InBattle()
{
	try
	{	
		auto pos = m_pCamera->getPosition();
		client->SendHeroMove( client->m_index, pos.X, pos.Y, pos.Z );
		auto rot = m_pCamera->getRotation();
		client->SendHeroRot( client->m_index, rot.X, rot.Y, rot.Z );
	}
	catch ( std::exception& e )
	{
		std::cerr << e.what() << std::endl;
	}
	catch ( ... )
	{
		std::cerr << "ERROR!!!!!!!!!!!!!!!!1" << std::endl;
	}

	UpdateConsole();

	m_playerHelper->Update();

	m_playerManager->Update();
}

