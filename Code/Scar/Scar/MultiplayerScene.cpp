/********************************************************************
����ʱ��: 2011-10-8   16:01
�ļ���:   MultiplayerScene.cpp
����:     ���� Cedric Porter [ Stupid ET ]	
˵��:     ������Ϸ����

*********************************************************************/


#include "AllAnimators.h"
#include "AllUIObjects.h"
#include "Boost_Client.h"
#include "Boost_Server.h"
#include "BulletNode.h"
#include "CSceneNodeAnimatorSelfDelFlyStraight.h"
#include "EngineHeader.h"
#include "Flame.h"
#include "FlyBehavior.h"
#include "Frigate.h"
#include "GameBag.h"
#include "IRobot.h"
#include "MultiplayerScene.h"
#include "MySceneManager.h"
#include "PlayerManager.h"
#include "PythonManager.h"
//#include "RobotManager.h"
#include "RobotShip.h"
#include "Robot_Client.h"
#include "SceneNodeShader.h"
#include "SpriteFlame.h"
#include "Toolkit.h"
#include "UIAnimators.h"
#include "UIManager.h"
#include "irrKlang.h"
#include <iostream>
#include "HumanPlayer.h"

#define PRINT_POS( pos ) std::cout << #pos ## " " << pos.X << ' ' << pos.Y << ' ' << pos.Z << std::endl;


using namespace irrklang;


//boost::shared_ptr<Network::BoostClient> client;
boost::shared_ptr<Network::BoostClient> client;

boost::shared_ptr<Network::BoostServer> server;

//scene::ISceneNode* node;
UIManager* uiManager; //������

IUIObject* root;	//������

BulletNode* bullet;	// �ӵ�

Toolkit* toolkit;
Node2DInfo info2D;

ISoundEngine* pSoundEngine;
ISoundSource* fuck;

//������shader
SceneNodeShader* shader;
//RobotManager robotManager;

boost::shared_ptr<PlayerHelper>		m_playerHelper;
boost::shared_ptr<PlayerManager>	m_playerManager;

bool bRunOnce = true;
// CallBacks
// ͨ����Shader�ص�����
// �贫�������Ŀ��ڵ�
// �ں��������ͶӰ��������ʱ��
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

		//�ڵ�任����
		matrix4 transMatrix = Node->getAbsoluteTransformation();
		services->setVertexShaderConstant( "TransMatrix", transMatrix.pointer(), 16);

		//�ڵ��������
		vector3df absPos = Node->getAbsolutePosition();
		services->setVertexShaderConstant( "AbsPos", reinterpret_cast<f32*>(&absPos), 3);

		//����ͶӰ����
		matrix4 worldViewProj;
		worldViewProj = driver->getTransform( ETS_PROJECTION );
		worldViewProj *= driver->getTransform( ETS_VIEW );
		worldViewProj *= driver->getTransform( ETS_WORLD );
		services->setVertexShaderConstant( "WorldViewProj", worldViewProj.pointer(), 16);

		//������������
		matrix4 invWorld = driver->getTransform( ETS_WORLD );
		invWorld.makeInverse();
		services->setVertexShaderConstant( "InvWorld", invWorld.pointer(), 16);

		//�������ת�þ���
		matrix4 transWorld = driver->getTransform( ETS_WORLD );
		transWorld = transWorld.getTransposed();
		services->setVertexShaderConstant( "TransWorld", transWorld.pointer(), 16);

		//����, ���֧����������
		int d[]   = {0, 1, 2, 3};      //Sampler2d IDs
		services->setPixelShaderConstant("TextureL0",(float*)&d[0],1);
		services->setPixelShaderConstant("TextureL1",(float*)&d[1],1);
		services->setPixelShaderConstant("TextureL2",(float*)&d[2],1);
		services->setPixelShaderConstant("TextureL3",(float*)&d[3],1);

		//���������
		vector3df cameraPos = smgr->getActiveCamera()->getAbsolutePosition();
		services->setVertexShaderConstant( "CameraPos", reinterpret_cast<f32*>(&cameraPos), 3);

		//ʱ��
		f32 timeMs = (f32)MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
		services->setVertexShaderConstant( "TimeMs", (f32*)&timeMs, 1);
	}
};

irr::gui::IGUIStaticText* console;
void UpdateConsole()
{
	if ( ! console->isVisible() )	return;
	std::string buf = MyIrrlichtEngine::Console_Buffer.str();
	if ( buf.empty() )	
		return;

	std::wstring str( buf.begin(), buf.end() );
	str = console->getText() + str;
	std::size_t remain = 800;
	if ( str.length() > remain )
	{
		std::size_t pos = str.length() - remain;
		while ( pos )
		{
			if ( str[ pos ] == _T('\n') )
			{
				break;
			}
			pos--;
		}
		str = str.substr( pos );
	}
	console->setText( str.c_str() );
	MyIrrlichtEngine::Console_Buffer.clear();
}


void MultiplayerScene::Run()
{
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	IVideoDriver* driver = pEngine->GetVideoDriver();
	if ( bRunOnce )
	{
		bRunOnce = false;

		Sleep( 1500 );

		auto rooms = client->GetRooms();
		auto localIP = client->GetLocalIP();

		auto iter = rooms.begin();
		for ( ; iter != rooms.end(); ++iter )
		{
			std::cout << "Room " << iter->first << " ";
			std::wcout << iter->second.room_name << std::endl;

			if ( rooms.size() > 1 && localIP.find( iter->first ) == localIP.end() )		// �Ǳ���IP
			{	
				std::cout << "enter " << iter->first << std::endl;
				client->EnterRoom( iter->first );
				break;
			}
		}

		if ( iter == rooms.end()  ) 
			if ( ! localIP.empty() )
				client->EnterRoom( *localIP.begin() );		
			else
				client->EnterRoom( "127.0.0.1" );

		//Sleep( 2000 );

		//client->Send( "192.168.1.121" );

		while ( -11 == client->m_index )
		{
			Sleep( 500 );
		}

		std::cout << "m_index " << client->m_index << std::endl;

	}

	auto pos = m_pCamera->getPosition();
	client->SendHeroMove( client->m_index, pos.X, pos.Y, pos.Z );
	auto rot = m_pCamera->getRotation();
	client->SendHeroRot( client->m_index, rot.X, rot.Y, rot.Z );


	UpdateConsole();

	m_playerHelper->Update();

	m_playerManager->Update();

}

void MultiplayerScene::Init()
{
	// ��ȡ����
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	scene::ISceneManager* smgr = pEngine->GetSceneManager();
	m_pModelMan = pEngine->GetModelManager();
	auto driver = pEngine->GetVideoDriver();
	shader = new SceneNodeShader();

	// �������
	pEngine->GetDevice()->getCursorControl()->setVisible(false);


	// �����ɴ�
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
	
	 //�ɴ�β��
	SpriteFlame spf;
	spf.SetOffset( vector3df( -6, 0, -22 ) );
	spf.AddFlameToShip( cf1, smgr );
	spf.SetOffset( vector3df( 6, 0, -22 ) );
	spf.AddFlameToShip( cf1, smgr );

	// �����ӵ�
	bullet = new BulletNode( smgr, smgr->getRootSceneNode() );
	bullet->setMaterialTexture( 0, driver->getTexture( "../media/Weapon/bullet.png" ) );
	bullet->SetVelocity( 1000 );
	bullet->SetInterval( 100 );
	cf1->AddGun( bullet );
	bullet->drop();

	//  ���������
	//m_pCamera = smgr->addCameraSceneNodeFPS( 0, 100, 50.0f );
	m_pCamera = smgr->addCameraSceneNode();;

	auto fpsAni = new CSceneNodeAnimatorAircraftFPS( pEngine->GetDevice()->getCursorControl() );
	cf1->addAnimator( fpsAni );
	fpsAni->drop();

	m_pCamera->setFOV( 1 );
	m_pCamera->setFarValue( 1e7f );
	
	/*auto shakeAni = new MySceneNodeAnimatorShake( 0, 80000, 1.2f );
	m_pCamera->addAnimator( shakeAni );
	shakeAni->drop();*/

	// ��������
	auto BeginMove = new TheBeginMove( vector3df(50000),vector3df(0), 1000, 5000, 1 );
	m_pCamera->addAnimator( BeginMove );
	BeginMove->drop();

	//m_pCamera->setParent( cf1 );
	// �ɴ����������
	auto folowAni = new CSceneNodeAnimatorCameraFollowShip( cf1, -40 );
	m_pCamera->addAnimator( folowAni );
	folowAni->drop();

	//��������
	auto planet = smgr->addSphereSceneNode( 4e5, 64 );
	if ( planet )
	{
		// ��������
		planet->setName( "planet1" );
		// ��������
		planet->setMaterialTexture( 0, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/planet5.jpg") ) );
		planet->setMaterialTexture( 1, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/night0.jpg") ) );
		planet->setMaterialTexture( 2, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/a.tga") ) );
		// ������ת
		auto rot = smgr->createRotationAnimator( vector3df( 0, 0.005f, 0) );
		planet->addAnimator( rot );
		rot->drop();
		// Shader
		GeneralCallBack* cb = new GeneralCallBack( planet );
		shader->ApplyShaderToSceneNode( planet, cb, "Shader/PlanetGroundV.txt", "Shader/PlanetGroundF.txt" );
		cb->drop();
		//// ���ó�ʼ��С
		//planet->setScale( vector3df( .01f ) );
		//// ���Ŷ���
		//auto sca = new MySceneNodeAnimatorScale( 0, 8000, vector3df( 1.99f ), AS_MT_LOG );
		//planet->addAnimator( sca );
		//sca->drop();
		// ������Զ��Ծ�ͷ
		auto relstayAni = new RelateCameraAnimatorStay( 0, 1000, m_pCamera, vector3df( -2e5, 0, 8e5 ) );
		planet->addAnimator( relstayAni );
		relstayAni->drop();
	}
	// ���Ǵ���Ȧ
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


	//��������
	auto moon = smgr->addSphereSceneNode( 1e5, 64 );
	if ( moon )
	{
		// ��������
		moon->setName( "moon1" );
		// ��������
		moon->setMaterialTexture( 0, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/planet1.jpg") ) );
		// ������ת
		auto rot = smgr->createRotationAnimator( vector3df( 0, -0.006f, 0) );
		moon->addAnimator( rot );
		rot->drop();
		//// ���ó�ʼ��С
		//moon->setScale( vector3df( .001f ) );
		//// ���Ŷ���
		//auto sca = new MySceneNodeAnimatorScale( 2000, 6000, vector3df( 1.999f ), AS_MT_LOG, 500 );
		//moon->addAnimator( sca );
		//sca->drop();
		//// ��Ծ����Ч��
		//auto relmovAni = new RelateCameraAnimatorMove( 2000, 6000, m_pCamera,
		//	vector3df(1e5, 0, 2.5e5), vector3df(1e5, 0, -2.5e5), RM_MT_LOG, 800 );
		//moon->addAnimator( relmovAni );
		//relmovAni->drop();
		// ������Զ��Ծ�ͷ
		auto relstayAni = new RelateCameraAnimatorStay( 0, 1000, m_pCamera, vector3df( 1e5, 0, 2.5e5 ) );
		moon->addAnimator( relstayAni );
		relstayAni->drop();
	}

	pSoundEngine = createIrrKlangDevice();
	fuck = pSoundEngine->addSoundSourceFromFile("../media/booster_blue_b02a.ogg");

	//fuck->setVolume( fuck->getVolume() - 10 );

	//���ؿռ�վģ��

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

	////����̫��
	//auto sun = smgr->addSphereSceneNode( 200000 );
	//if ( sun )
	//{
	//	// ��������
	//	moon->setName( "sun1" );
	//}

	// ̫���⣨ƽ�й⣩
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

	// ����UI����
	uiManager = new UIManager( pEngine->GetDevice()->getTimer() );
	pEngine->SetUIManager( uiManager );

	try
	{
		using namespace boost::python;

		object UILoader = import( "MultiPlayIni" );
		object GetRoot = UILoader.attr( "GetRoot" );
		object root = GetRoot();

		IUIObject* r = extract<IUIObject*>( root ); 
		uiManager->SetRoot( r );
		//r->drop();	// ʹ��Python�������ڴ����
		m_playerHelper->LoadHelperUI( uiManager );
		m_playerHelper->LoadPlayerManager( &*m_playerManager );
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
		server = boost::shared_ptr<Network::BoostServer>( new Network::BoostServer );
		client = boost::shared_ptr<Network::BoostClient>( new Network::BoostClient( &*m_playerManager ) );
	}
	catch ( std::exception& e )
	{
		std::cerr << e.what() << std::endl;
	}

	server->Start( 1990, 2012 );
	client->Start( 2012, 1990 );


	// ���robot
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







	// ��������ϵͳ
	/*IParticleSystemSceneNode* ps  = smgr->addParticleSystemSceneNode(false, cf1);
	IParticleBoxEmitter* em = ps->createBoxEmitter( aabbox3df(-3,0,-3,3,1,3), vector3df(0,0.3f,0),
		80, 100, 
		SColor(0,255,255,255), SColor(0,255,255,255),
		400, 1100);
	em->setMinStartSize( dimension2df(30.f, 40.f));
	em->setMaxStartSize( dimension2df(30,40) );
	ps->setEmitter( em );
	em->drop();
	IParticleAffector* af = ps->createFadeOutParticleAffector();
	ps->addAffector( af );
	af->drop();
	ps->setMaterialFlag( EMF_LIGHTING, false );
	ps->setMaterialFlag( EMF_ZWRITE_ENABLE, false );
	ps->setMaterialTexture( 0, driver->getTexture("../media/fireball.bmp") );
	ps->setMaterialType( EMT_TRANSPARENT_VERTEX_ALPHA );*/


	// �������
	auto fireAni = new ShipFireAnimator( client );
	cf1->addAnimator( fireAni );
	fireAni->drop();

	client->QueryRoom();


	try
	{
		// ʹ��Pythonģ�����ģ��
		PythonManager* p = PythonManager::GetPythonManager();
		object modelLoader = p->GetModelLoader();
		object MultiplayerLoad = modelLoader.attr( "MultiplayerLoad" );
		MultiplayerLoad();
	}
	catch ( ... )
	{
		PyErr_Print();
	}


	// ��պ�
	m_pSkyBox = smgr->addSkyBoxSceneNode(
		driver->getTexture( _T("../media/Space/c07_up.jpg") ),
		driver->getTexture( _T("../media/Space/c07_dn.jpg") ),
		driver->getTexture( _T("../media/Space/c07_lt.jpg") ),
		driver->getTexture( _T("../media/Space/c07_rt.jpg") ),
		driver->getTexture( _T("../media/Space/c07_ft.jpg") ),
		driver->getTexture( _T("../media/Space/c07_bk.jpg") ));	
	if (m_pSkyBox)
	{
		//��֪��Ϊʲô����պ���Сһ�㷴��������ڱ�
		m_pSkyBox->setScale( vector3df( .1f, .1f, .1f ) );
		//shader
		//std::cout<< "!!!!!!!!!!!!!!!!!!!!!!!!!"<<m_pSkyBox->getMaterialCount()<<std::endl;
		m_pSkyBox->setMaterialTexture( 1, driver->getTexture("../media/Space/stars.png") );
		GeneralCallBack* cb = new GeneralCallBack(m_pSkyBox);
		shader->ApplyShaderToSceneNode( m_pSkyBox, cb, "Shader/universeV.txt", "Shader/universeF.txt" );
		cb->drop();
	}
	

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

	// ������ע��receiver���¼�����ص�����
	dynamic_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc(
		[ this, fpsAni, gui, box, pEngine ]( const SEvent& event )->void*
	{	
		//fpsAni->OnEvent( event );
		m_playerManager->OnEvent( event );

		//control.OnEvent( event );
		//pEngine;		// ����ָ��
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
		}
		return 0;
	} );




}

void MultiplayerScene::Release()
{
	if ( uiManager )
		delete uiManager;

	client->Close();
	server->Close();

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

