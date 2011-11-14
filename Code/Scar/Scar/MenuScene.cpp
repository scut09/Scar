#include "MenuScene.h"
#include "def.h"
#include "UIAnimators.h"
#include "UIManager.h"
#include "MyIrrlichtEngine.h"
#include "EventListener.h"
#include "PlayerManager.h"
#include "PythonWrapper.h"

#undef LoadImage

void MenuScene::Run()
{
	//std::cout<< "fuck" << std::endl;
	if ( IsFirstRun )
	{
		IsFirstRun = false;

		try
		{
			using namespace boost::python;

			object UILoader = import( SceneName.c_str() );
			object LoadStartAnimation = UILoader.attr( "LoadStartAnimation" );
			IUIObject* root = pEngine->GetUIManager()->GetRootUIObject();
			LoadStartAnimation( boost::ref( root ) );
			
			//r->drop();	// ʹ��Python�������ڴ����
		}
		catch ( ... )
		{
			PyErr_Print();
		}

	}

	pEngine->GetClient()->QueryRoom();
	auto RoomList = pEngine->GetClient()->GetRooms();
	for ( auto iter = RoomList.begin(); iter != RoomList.end(); ++iter )
	{
		//iter->first;
		const Network::BroadcastRoomBag& bag = iter->second;
		/*UIStaticText* abc = (UIStaticText*)pEngine->GetUIManager()->GetUIObjectByName( "abc" );
		abc->SetText( "" );
		abc->SetText( bag.room_name );*/
	}
}


void MenuScene::Init()
{
	#pragma region fuck
using namespace scene;
	using namespace video;
	using namespace core;

	pEngine = MyIrrlichtEngine::GetEngine();
	driver = pEngine->GetVideoDriver();
	smgr = pEngine->GetSceneManager();
	smgr->clear();

	// ���������
	camera = smgr->addCameraSceneNode();
	camera->setFarValue( 1e5 );
	camera->setFOV( 0.8f );
	camera->setAspectRatio( (f32)driver->getScreenSize().Width / (f32)driver->getScreenSize().Height );

	// �����ǿ�ͼ
	ISceneNode* bg3D = smgr->addBillboardSceneNode( 0, dimension2df( 38400, 24000 ) );
	bg3D->setMaterialTexture( 0, driver->getTexture( "../media/UIResource/Menu/galaxy.jpg" ) );
	bg3D->setPosition( vector3df( 0, 0, 14000 ) );
	bg3D->setMaterialFlag( EMF_LIGHTING, false );

	// ��������1
	ISceneNode* planet1 = smgr->addSphereSceneNode( 5000, 64 );
	planet1->setPosition( vector3df( 3000, -4000, 8000) );
	planet1->setRotation( vector3df( 0, 0, -15 ) );
	planet1->setMaterialTexture( 0, driver->getTexture( "../media/Planets/neptune.jpg") );
	planet1->setMaterialTexture( 1, driver->getTexture( "../media/Planets/cloud2.jpg") );
	planet1->setMaterialTexture( 2, driver->getTexture( "../media/Planets/citylights2.png") );
	ShaderCallBack* cb = new ShaderCallBack( planet1 );
	shader.ApplyShaderToSceneNode( planet1, cb, "Shader/MenuPlanetGround.vert", "Shader/MenuPlanetGround.frag" );
	cb->drop();
	// ����1������
	ISceneNode* atmos1 = smgr->addSphereSceneNode( 5300, 64, planet1 );
	atmos1->setMaterialFlag( EMF_BACK_FACE_CULLING, false );
	atmos1->setMaterialFlag( EMF_FRONT_FACE_CULLING, true );
	cb = new ShaderCallBack( atmos1 );
	shader.ApplyShaderToSceneNode( atmos1, cb, "Shader/MenuAtmos.vert", "Shader/MenuAtmos.frag", EMT_TRANSPARENT_ADD_COLOR );
	cb->drop();

	// ����
	IBillboardSceneNode* sun = smgr->addBillboardSceneNode( 0, dimension2df(128, 128), vector3df(0,0,200) );
	sun->setMaterialTexture( 0, driver->getTexture( "../media/Space/flare1.tga" ) );
	cb = new ShaderCallBack( sun );
	shader.ApplyShaderToSceneNode( sun, cb, "", "Shader/MenuSun.frag", EMT_TRANSPARENT_ADD_COLOR );
	cb->drop();
	// ����
	IBillboardSceneNode* flare = smgr->addBillboardSceneNode( 0, dimension2df(128, 128), vector3df(20,-20,150) );
	flare->setMaterialTexture( 0, driver->getTexture( "../media/Space/rainbow.tga" ) );
	cb = new ShaderCallBack( flare );
	shader.ApplyShaderToSceneNode( flare, cb, "", "Shader/MenuSunFlare.frag", EMT_TRANSPARENT_ADD_COLOR );
	cb->drop();

	// �ɴ�
	IAnimatedMeshSceneNode* cfr1 = smgr->addAnimatedMeshSceneNode( smgr->getMesh( "../model/ship/cfr1.x" ) );
	cfr1->setScale( vector3df(0.3f) );
	cfr1->setRotation( vector3df(0,180,0) );
	cfr1->setPosition( vector3df( -300, 100, 1000 ) );
	cfr1->setMaterialTexture( 0, driver->getTexture( "../model/ship/cfr_tex_d.tga" ) );
	cfr1->setMaterialFlag( EMF_LIGHTING, false );
	cb = new ShaderCallBack( cfr1 );
	shader.ApplyShaderToSceneNode( cfr1, cb, "Shader/MenuShip.vert", "Shader/MenuShip.frag" );
	cb->drop();
	IAnimatedMeshSceneNode* cfr2 = (IAnimatedMeshSceneNode*)cfr1->clone();
	cfr2->setPosition( vector3df( -200, -200, 800 ) );
	IAnimatedMeshSceneNode* cfr3 = (IAnimatedMeshSceneNode*)cfr1->clone();
	cfr3->setPosition( vector3df( 0, -80, 1300 ) );
	


	std::cout << "===> " << this->SceneName << " construction" << std::endl;

	pEngine->SetUIManager( boost::shared_ptr<UIManager>( new UIManager( pEngine->GetDevice()->getTimer() ) ) );


	try
	{
		using namespace boost::python;

		object UILoader = import( SceneName.c_str() );
		object GetRoot = UILoader.attr( "GetRoot" );
		object root = GetRoot();
		
		//IUIObject* r = extract<IUIObject*>( root ); 
		//uiManager->SetRoot( r );
		//r->drop();	// ʹ��Python�������ڴ����
	}
	catch ( ... )
	{
		PyErr_Print();
	}

	/*try
	{
		server = boost::shared_ptr<Network::BoostServer>( new Network::BoostServer );
		client = boost::shared_ptr<Network::BoostClient>( new Network::BoostClient( &*m_playerManager ) );
	}
	catch ( std::exception& e )
	{
		std::cerr << e.what() << std::endl;
	}

	server->Start( 1990, 2012 );
	client->Start( 2012, 1990 );*/

	if ( SceneName == "MultiMenuIni")
	{
		IUIObject* root1 = pEngine->GetUIManager()->GetRootUIObject();
			IUIObject* house = pEngine->GetUIManager()->AddUIImage( 0, 200, 200 );
			 house->SetPosition(vector2df( 800, 400) );
			 house->LoadImage("../media/UIResource/Menu/scrollbar_hbackground.png");
			IUIObject* text1 = pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40, L"����", SColor( 255,255,255,255));
			IUIObject* text2 = pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40, L"�̺�", SColor( 255,255,255,255));
			IUIObject* text3 = pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40, L"��ͼ", SColor( 255,255,255,255));
			IUIObject* text4 = pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40, L"����", SColor( 255,255,255,255));
			IUIObject* text5 =pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40, L"����", SColor( 255,255,255,255));
			IUIObject* text6 = pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40,L"100", SColor( 255,255,255,255));
			IUIObject* text7 =pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40, L"�������", SColor( 255,255,255,255));
			IUIObject* text8 = pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40, L"200", SColor( 255,255,255,255));
			IUIObject* text9 = pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40, L"�ӳ�", SColor( 255,255,255,255));
			IUIObject* text10 = pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40, L"0", SColor( 255,255,255,255));
			f32 PosX = -50;
			f32 PosY = -50;
			f32 Base = 80;
			text1->SetPosition( vector2df( PosX, PosY));
			house->AddChild( text1 );
			text2->SetPosition( vector2df( PosX + Base, PosY ));
			house->AddChild( text2 );
			text3->SetPosition( vector2df( PosX, PosY + 30));
		    house->AddChild( text3 );
			text4->SetPosition( vector2df ( PosX + Base, PosY + 30));
			house->AddChild( text4 );
			text5->SetPosition( vector2df( PosX, PosY + 60));
			house->AddChild( text5 );
			text6->SetPosition( vector2df( PosX + Base , PosY + 60));
			house->AddChild( text6 );
			text7->SetPosition( vector2df( PosX, PosY + 90 ));
			house->AddChild( text7 );
			text8->SetPosition( vector2df( PosX + Base ,PosY + 90));
			house->AddChild( text8 );
			text9->SetPosition( vector2df( PosX, PosY + 120));
			house->AddChild( text9 );
			text10->SetPosition( vector2df( PosX +  Base, PosY + 120));
			house->AddChild( text10 );
		/*((CUIBox*)house)->test( 10 );*/
		
		//char buffer[255];
		//stringw str;
		//root = pEngine->GetUIManager()->GetRootUIObject();
		//UIStaticText* abc = new UIStaticText( root, 100, 20, L"����", SColor(255,255,255,255) );
		//abc->SetPosition( vector2df(200,200) );
		//abc->SetName( "abc" );
		//abc->SetText( L"�����˸���" );

		auto playerManager = boost::shared_ptr<PlayerManager>( new PlayerManager );
		auto client = boost::shared_ptr<Network::BoostClient>( new Network::BoostClient( playerManager ) );
		pEngine->SetClient( client );
		client->Start( 2012, 1990 );

		/*IGUIEnvironment* gui = MyIrrlichtEngine::GetEngine()->GetDevice()->getGUIEnvironment();
		IGUISkin* skin = gui->getSkin();
		IGUIFont* font = gui->getFont("../media/fonthaettenschweiler.bmp");
		if (font)
			skin->setFont(font);

		skin->setFont( gui->getBuiltInFont(), EGDF_TOOLTIP );

		IGUIEditBox* box = gui->addEditBox( _T("��gas����"), core::rect<s32>( 0, 0, 100, 50 ) );*/
	}
#pragma endregion fuck




	dynamic_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [this]( const SEvent& event )->void*
	{	
		pEngine->GetUIManager()->OnEvent( event );

		if ( event.KeyInput.PressedDown )
		{
			if ( event.KeyInput.Key == KEY_KEY_Y )
			{
				CreateRoom();
				auto smgr = MyIrrlichtEngine::GetEngine()->GetGameSceneManager();
				smgr->SetCurrentGameScene( smgr->GetSceneByName( "MultiplayerScene"  ) );
			}

		}

		return 0;
	} );

	

}

void MenuScene::Release()
{
	std::cout << "===> " << this->SceneName << " destruction" << std::endl;


	//uiManager = NULL;

	//try
	//{
	//	using namespace boost::python;

	//	object UILoader = import( "UILoader" );
	//	object DeleteTree = UILoader.attr( "DeleteTree" );
	//	DeleteTree();
	//}
	//catch ( ... )
	//{
	//	PyErr_Print();
	//}
}

void MenuScene::Draw()
{
	pEngine->GetUIManager()->DrawAll();
}

void MenuScene::ShaderCallBack::OnSetConstants( IMaterialRendererServices* services, s32 userData )
{
	using namespace scene;
	using namespace video;
	using namespace core;
	IVideoDriver* driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();

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

	//ʱ��
	f32 timeMs = (f32)MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
	services->setVertexShaderConstant( "TimeMs", (f32*)&timeMs, 1);
}
