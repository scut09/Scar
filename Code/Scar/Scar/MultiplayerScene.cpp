/********************************************************************
����ʱ��: 2011-10-8   16:01
�ļ���:   MultiplayerScene.cpp
����:     ���� Cedric Porter [ Stupid ET ]	
˵��:     ������Ϸ����

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
UIManager* uiManager; //������

IUIObject* root;	//������

IUIObject* Cursor;	// ���׼��
IUIObject* Speed1;	// �ٶȲ���
IUIObject* Speed2;	// �ٶȲۿ�
IUIObject* Shield1;	// ���ܲ���
IUIObject* Shield2;	// ���ܲۿ�
IUIObject* Armor1;	// ���ײ���
IUIObject* Armor2;	// ���ײۿ�
IUIObject* Gradienter;	// ˮƽ��
IUIObject* target1;	//Ŀ��Ȧ�����Ѿ�
IUIObject* lock1;	//�����򡪡�������
IUIObject* indicator1;	// �о�ָʾ
IShip* cf1;
IShip* npc;
BulletNode* bullet;	// �ӵ�

Toolkit* toolkit;
Node2DInfo info2D;

ISoundEngine* pSoundEngine;
ISoundSource* fuck;

//������shader
SceneNodeShader* shader;

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

			if ( rooms.size() > 1 && localIP.find( iter->first ) == localIP.end() )		// �Ǳ���IP
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


	// ׼��׷�����
	auto CursorPos = MyIrrlichtEngine::GetEngine()->GetDevice()->getCursorControl()->getPosition();
	Cursor->SetPosition( vector2df( (f32)CursorPos.X, (f32)CursorPos.Y ) );

	f32 ratio;
	f32 border;
	// �����ٶȲ�
	ratio = cf1->GetVelocity() / cf1->GetMaxSpeed();
	border = 389 * ( 1 - ratio );
	Speed1->SetSourceRect( vector2df( 0, border ), vector2df( 98, 389 ) );
	Speed2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 98, border ) );	
	// ���ƻ��ܲ�
	ratio = cf1->GetShield() / cf1->GetMaxShield();
	border = 389 * ( 1 - ratio );
	Shield1->SetSourceRect( vector2df( 0, border ), vector2df( 100, 389 ) );
	Shield2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 100, border ) );
	// ���ƻ��ײ�
	ratio = cf1->GetArmor() / cf1->GetMaxArmor();
	border = 360 * ( 1 - ratio );
	Armor1->SetSourceRect( vector2df( 0, border ), vector2df( 93, 360 ) );
	Armor2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 93, border ) );

	// ˮƽ��ת��
	core::vector3df vec( 0, 1, 0 );
	f32 rott = (f32)acos( ( m_pCamera->getUpVector().dotProduct( vector3df( 0, 1, 0 ) ) ) / m_pCamera->getUpVector().getLength() ) * RADTODEG;
	Gradienter->SetRotation( rott );

	// ������ȦȦȦסĿ��
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
		  // �����ü�ͷ��ǵط�λ��
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

	// ��ȡ����
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	scene::ISceneManager* smgr = pEngine->GetSceneManager();
	m_pModelMan = pEngine->GetModelManager();
	auto driver = pEngine->GetVideoDriver();
	shader = new SceneNodeShader();

	// �������
	pEngine->GetDevice()->getCursorControl()->setVisible(false);

	// �����ɴ�
	cf1 = new CFrigate( smgr->getMesh("../module/1234.obj"), 0, smgr, -1 );	

	//cf1->setPosition( vector3df( 0, 0, 50 ) );rt
	// �����ӵ�
	bullet = new BulletNode( smgr );
	bullet->setMaterialTexture( 0, driver->getTexture( "../media/Weapon/bullet.png" ) );
	bullet->SetVelocity( 1000 );
	bullet->SetInterval( 100 );
	cf1->AddGun( bullet );

	//  ���������
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
	// ��������
	/*auto BeginMove = new TheBeginMove( vector3df(50000),vector3df(0), 1000, 5000, 1 );
	m_pCamera->addAnimator( BeginMove );
	BeginMove->drop();*/

	// �ɴ����������
	auto folowAni = new SceneNodeAnimatorFollow( m_pCamera, -40 );
	cf1->addAnimator( folowAni );
	folowAni->drop();

	// ����npc�ɴ�
	npc = new CFrigate( smgr->getMesh("../module/1234.obj"), 0, smgr, -1 );
	npc->setPosition( vector3df(0,0,50) );
	toolkit = new Toolkit( m_pCamera, driver );

	// �������
	auto fireAni = new FireAnimator( m_pCamera );
	cf1->addAnimator( fireAni );
	fireAni->drop();

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
	auto moon = smgr->addSphereSceneNode( 1e5 );
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
	IAnimatedMeshSceneNode* station = smgr->addAnimatedMeshSceneNode( smgr->getMesh( _T("../model/station/cs1.obj") ) );
	if ( station )
	{
		// ��������
		station->setName( "station1" );
		station->setMaterialTexture( 1, driver->getTexture(_T("../model/station/cs1_tex_l.png")) );
		//station->
		GeneralCallBack* cb = new GeneralCallBack( station );
		shader->ApplyShaderToSceneNode( station, cb, "Shader/cs_1V.txt", "Shader/cs_1F.txt" );
		cb->drop();


	//	// ���ó�ʼ��С
	//	//station->setScale( vector3df( .001f));
	//	//station->setVisible(false);
	//	// ���Ŷ���
	//	//auto sca = new MySceneNodeAnimatorLogScale( 5000, 5000, vector3df( 1.999f ), 500 );
	//	//moon->addAnimator( sca );
	//	//sca->drop();
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

	// ����UI����
	uiManager = new UIManager( pEngine->GetDevice()->getTimer() );
	try
	{
		using namespace boost::python;

		object UILoader = import( "MultiPlayIni" );
		object GetRoot = UILoader.attr( "GetRoot" );
		object root = GetRoot();

		IUIObject* r = extract<IUIObject*>( root ); 
		uiManager->SetRoot( r );
		//r->drop();	// ʹ��Python�������ڴ����
	}
	catch ( ... )
	{
		PyErr_Print();
	}
	// ��ȡ���׼��
	Cursor = uiManager->GetObjectByName("cursor");
	// ��ȡ�ٶȲ�
	Speed1 = uiManager->GetObjectByName( "speed1" );
	Speed2 = uiManager->GetObjectByName( "speed2" );
	// ��ȡ���ܲ�
	Shield1 = uiManager->GetObjectByName( "shield1");
	Shield2 = uiManager->GetObjectByName( "shield2");
	// ��ȡ���ײ�
	Armor1 = uiManager->GetObjectByName( "armor1");
	Armor2 = uiManager->GetObjectByName( "armor2");
	// ��ȡˮƽ��
	Gradienter = uiManager->GetObjectByName( "gradienter" );
	// ��ȡĿ��Ȧ
	target1 = uiManager->GetObjectByName( "target1" );
	// ��ȡ����Ȧ����������
	lock1 = uiManager->GetObjectByName( "lock1" );
	// ��ȡ�о�ָʾ
	indicator1 = uiManager->GetObjectByName( "indicator1" );

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


	//	m_pAnimationMan = pEngine->GetAnimationManager();



	//// ����ģ�ͺͶ���
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
	


	//// ע������ص�����
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

	//�������ϵ�����****************
	//for (int i = 0;i < 24;i++)
	//{
	//	CFlame flame;
	//	auto fire = flame.createFlame(
	//		MyIrrlichtEngine::GetEngine()->GetDevice(), 
	//		"../media/particle.bmp"
	//		);
	////	fire->setVisible(false);   //��ʼ���ɼ�
	//	node->addChild( fire );
	//}
	IGUIEnvironment* gui = MyIrrlichtEngine::GetEngine()->GetDevice()->getGUIEnvironment();


	IGUIEditBox* box = gui->addEditBox( _T(""), core::rect<s32>( 0, 0, 100, 50 ) );
	box->setVisible( false );

	//auto as = core::rect<s32>;

	MyIrrlichtEngine::GetEngine()->SetMotionBlur( true );


	// ������ע��receiver���¼�����ص�����
	dynamic_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [ gui, box, fireAni, pEngine ]( const SEvent& event )->void*
	{	
		fireAni->OnEvent( event );
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

