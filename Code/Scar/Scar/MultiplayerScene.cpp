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
#include "Toolkit.h"
#include "SceneNodeShader.h"
#include "MySceneManager.h"
#include "irrKlang.h"

#define PRINT_POS( pos ) std::cout << #pos ## " " << pos.X << ' ' << pos.Y << ' ' << pos.Z << std::endl;


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
IUIObject* target1;	//目标圈——友军
IUIObject* lock1;	//锁定框——已锁定
IUIObject* indicator1;	// 敌军指示
IShip* cf1;
IShip* npc;
BulletNode* bullet;	// 子弹

Toolkit* toolkit;
Node2DInfo info2D;

ISoundEngine* pSoundEngine;
ISoundSource* fuck;

//测试用shader
SceneNodeShader* shader;

bool bRunOnce = true;
// CallBacks
// 通用型Shader回调函数
// 需传入参数：目标节点
// 内含世界矩阵，投影矩阵，纹理，时钟
class GeneralCallBack : public video::IShaderConstantSetCallBack
{
	ISceneNode* Node;

public:
	GeneralCallBack( ISceneNode* node )
		: Node( node )
	{

	}
private:
	virtual void OnSetConstants( IMaterialRendererServices* services, s32 userData ) 
	{
		IVideoDriver* driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
		ISceneManager* smgr = MyIrrlichtEngine::GetEngine()->GetDevice()->getSceneManager();

		//节点变换矩阵
		matrix4 transMatrix = Node->getAbsoluteTransformation();
		services->setVertexShaderConstant( "TransMatrix", transMatrix.pointer(), 16);

		//节点绝对坐标
		vector3df absPos = Node->getAbsolutePosition();
		services->setVertexShaderConstant( "AbsPos", reinterpret_cast<f32*>(&absPos), 3);

		//世界投影矩阵
		matrix4 worldViewProj;
		worldViewProj = driver->getTransform( ETS_PROJECTION );
		worldViewProj *= driver->getTransform( ETS_VIEW );
		worldViewProj *= driver->getTransform( ETS_WORLD );
		services->setVertexShaderConstant( "WorldViewProj", worldViewProj.pointer(), 16);

		//世界矩阵逆矩阵
		matrix4 invWorld = driver->getTransform( ETS_WORLD );
		invWorld.makeInverse();
		services->setVertexShaderConstant( "InvWorld", invWorld.pointer(), 16);

		//世界矩阵转置矩阵
		matrix4 transWorld = driver->getTransform( ETS_WORLD );
		transWorld = transWorld.getTransposed();
		services->setVertexShaderConstant( "TransWorld", transWorld.pointer(), 16);

		//纹理, 最多支持四重纹理
		int d[]   = {0, 1, 2, 3};      //Sampler2d IDs
		services->setPixelShaderConstant("TextureL0",(float*)&d[0],1);
		services->setPixelShaderConstant("TextureL1",(float*)&d[1],1);
		services->setPixelShaderConstant("TextureL2",(float*)&d[2],1);
		services->setPixelShaderConstant("TextureL3",(float*)&d[3],1);

		//摄像机坐标
		vector3df cameraPos = smgr->getActiveCamera()->getAbsolutePosition();
		services->setVertexShaderConstant( "CameraPos", reinterpret_cast<f32*>(&cameraPos), 3);

		//时钟
		f32 timeMs = (f32)MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
		services->setVertexShaderConstant( "TimeMs", (f32*)&timeMs, 1);
	}
};

void MultiplayerScene::Run()
{
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	IVideoDriver* driver = pEngine->GetVideoDriver();
	if ( bRunOnce )
	{
		bRunOnce = false;

		Sleep( 1500 );

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

		while ( -11 == client.m_index )
		{
			Sleep( 500 );
		}

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
	core::vector3df vec( 0, 1, 0 );
	f32 rott = (f32)acos( ( m_pCamera->getUpVector().dotProduct( vector3df( 0, 1, 0 ) ) ) / m_pCamera->getUpVector().getLength() ) * RADTODEG;
	Gradienter->SetRotation( rott );

	// 测试用圈圈圈住目标
	 if ( toolkit->GetNode2DInfo( npc, &info2D ) )
	 {
		 indicator1->SetVisible( false );
		 f32 sca = info2D.height / 60.0f;
		 if ( sca > 1.2f )
			 sca = 1.2f;
		 else if ( sca < 0.5f )
			 sca = 0.5f;
		 target1->SetPosition( info2D.pos );
		 target1->SetScale( vector2df(sca) );
		 lock1->SetPosition( info2D.pos );
		 lock1->SetScale( vector2df(sca) );
		 target1->SetVisible( true );
		 lock1->SetVisible( true );
	 }
	 else
	 {
		  target1->SetVisible( false );
		  lock1->SetVisible( false );
		  indicator1->SetVisible( true );
		  // 测试用箭头标记地方位置
		  vector2df screenPos;
		  toolkit->To2DScreamPos( (npc->getPosition() - m_pCamera->getPosition()), &screenPos );
		  vector2df screenVec = screenPos - vector2df( driver->getScreenSize().Width / 2.f, driver->getScreenSize().Height / 2.f );
		  f32 ang = (f32)screenVec.getAngle();
		  ang = -(ang-90);
		  //std::cout<< ang << std::endl;
		  indicator1->SetRotation( ang );
	 } 
	 
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
	shader = new SceneNodeShader();

	// 隐藏鼠标
	pEngine->GetDevice()->getCursorControl()->setVisible(false);

	// 创建飞船
	cf1 = new CFrigate( smgr->getMesh("../module/1234.obj"), 0, smgr, -1 );	

	//cf1->setPosition( vector3df( 0, 0, 50 ) );rt
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
	// 开场动画
	/*auto BeginMove = new TheBeginMove( vector3df(50000),vector3df(0), 1000, 5000, 1 );
	m_pCamera->addAnimator( BeginMove );
	BeginMove->drop();*/

	// 飞船跟随照相机
	auto folowAni = new SceneNodeAnimatorFollow( m_pCamera, -40 );
	cf1->addAnimator( folowAni );
	folowAni->drop();

	// 创建npc飞船
	npc = new CFrigate( smgr->getMesh("../module/1234.obj"), 0, smgr, -1 );
	npc->setPosition( vector3df(0,0,50) );
	toolkit = new Toolkit( m_pCamera, driver );

	// 创建火控
	auto fireAni = new FireAnimator( m_pCamera );
	cf1->addAnimator( fireAni );
	fireAni->drop();

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
		shader->ApplyShaderToSceneNode( planet, cb, "Shader/PlanetGroundV.txt", "Shader/PlanetGroundF.txt" );
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
		shader->ApplyShaderToSceneNode( planetAtmos, cb, "Shader/PlanetAtmosV.txt", "Shader/PlanetAtmosF.txt",EMT_TRANSPARENT_ADD_COLOR );
		cb->drop();
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
	IAnimatedMeshSceneNode* station = smgr->addAnimatedMeshSceneNode( smgr->getMesh( _T("../model/station/cs1.obj") ) );
	if ( station )
	{
		// 设置名字
		station->setName( "station1" );
		station->setMaterialTexture( 1, driver->getTexture(_T("../model/station/cs1_tex_l.png")) );
		//station->
		GeneralCallBack* cb = new GeneralCallBack( station );
		shader->ApplyShaderToSceneNode( station, cb, "Shader/cs_1V.txt", "Shader/cs_1F.txt" );
		cb->drop();


	//	// 设置初始大小
	//	//station->setScale( vector3df( .001f));
	//	//station->setVisible(false);
	//	// 缩放动画
	//	//auto sca = new MySceneNodeAnimatorLogScale( 5000, 5000, vector3df( 1.999f ), 500 );
	//	//moon->addAnimator( sca );
	//	//sca->drop();
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
	// 获取目标圈
	target1 = uiManager->GetObjectByName( "target1" );
	// 获取锁定圈——已锁定
	lock1 = uiManager->GetObjectByName( "lock1" );
	// 获取敌军指示
	indicator1 = uiManager->GetObjectByName( "indicator1" );

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
	if (m_pSkyBox)
	{
		//不知道为什么把天空盒设小一点反而不会出黑边
		//m_pSkyBox->setScale( vector3df( .1f, .1f, .1f ) );
		//shader
		/*std::cout<< "!!!!!!!!!!!!!!!!!!!!!!!!!"<<m_pSkyBox->getMaterialCount()<<std::endl;
		SMaterial mat = m_pSkyBox->getMaterial(1);
		mat.setTexture( 0, 0 );
		mat.MaterialType = (E_MATERIAL_TYPE)driver->getGPUProgrammingServices()->addHighLevelShaderMaterialFromFiles(
			"Shader/universeV.txt", "main", EVST_VS_1_1, "Shader/universeF.txt");*/
		/*GeneralCallBack* cb = new GeneralCallBack(m_pSkyBox);
		shader->ApplyShaderToSceneNode( m_pSkyBox, cb, "", "Shader/universeF.txt" );
		cb->drop();*/
	}
	


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
	IGUIEnvironment* gui = MyIrrlichtEngine::GetEngine()->GetDevice()->getGUIEnvironment();


	IGUIEditBox* box = gui->addEditBox( _T(""), core::rect<s32>( 0, 0, 100, 50 ) );
	box->setVisible( false );

	//auto as = core::rect<s32>;

	MyIrrlichtEngine::GetEngine()->SetMotionBlur( true );


	// 创建并注册receiver的事件处理回调函数
	dynamic_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [ gui, box, fireAni, pEngine ]( const SEvent& event )->void*
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
				client.BroadcastMessage( client.m_index, box->getText() );
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
		}
		return 0;
	} );


	client.QueryRoom();


}

void MultiplayerScene::Release()
{
	if ( uiManager )
		delete uiManager;

	client.Close();
	server.Close();

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

