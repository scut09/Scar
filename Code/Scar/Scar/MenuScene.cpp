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
			
			//r->drop();	// 使用Python对象不用内存管理
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

	// 加入摄像机
	camera = smgr->addCameraSceneNode();
	camera->setFarValue( 1e5 );
	camera->setFOV( 0.8f );
	camera->setAspectRatio( (f32)driver->getScreenSize().Width / (f32)driver->getScreenSize().Height );

	// 背景星空图
	ISceneNode* bg3D = smgr->addBillboardSceneNode( 0, dimension2df( 38400, 24000 ) );
	bg3D->setMaterialTexture( 0, driver->getTexture( "../media/UIResource/Menu/galaxy.jpg" ) );
	bg3D->setPosition( vector3df( 0, 0, 14000 ) );
	bg3D->setMaterialFlag( EMF_LIGHTING, false );

	// 背景星球1
	ISceneNode* planet1 = smgr->addSphereSceneNode( 5000, 64 );
	planet1->setPosition( vector3df( 3000, -4000, 8000) );
	planet1->setRotation( vector3df( 0, 0, -15 ) );
	planet1->setMaterialTexture( 0, driver->getTexture( "../media/Planets/neptune.jpg") );
	planet1->setMaterialTexture( 1, driver->getTexture( "../media/Planets/cloud2.jpg") );
	planet1->setMaterialTexture( 2, driver->getTexture( "../media/Planets/citylights2.png") );
	ShaderCallBack* cb = new ShaderCallBack( planet1 );
	shader.ApplyShaderToSceneNode( planet1, cb, "Shader/MenuPlanetGround.vert", "Shader/MenuPlanetGround.frag" );
	cb->drop();
	// 星球1大气层
	ISceneNode* atmos1 = smgr->addSphereSceneNode( 5300, 64, planet1 );
	atmos1->setMaterialFlag( EMF_BACK_FACE_CULLING, false );
	atmos1->setMaterialFlag( EMF_FRONT_FACE_CULLING, true );
	cb = new ShaderCallBack( atmos1 );
	shader.ApplyShaderToSceneNode( atmos1, cb, "Shader/MenuAtmos.vert", "Shader/MenuAtmos.frag", EMT_TRANSPARENT_ADD_COLOR );
	cb->drop();

	// 恒星
	IBillboardSceneNode* sun = smgr->addBillboardSceneNode( 0, dimension2df(128, 128), vector3df(0,0,200) );
	sun->setMaterialTexture( 0, driver->getTexture( "../media/Space/flare1.tga" ) );
	cb = new ShaderCallBack( sun );
	shader.ApplyShaderToSceneNode( sun, cb, "", "Shader/MenuSun.frag", EMT_TRANSPARENT_ADD_COLOR );
	cb->drop();
	// 光晕
	IBillboardSceneNode* flare = smgr->addBillboardSceneNode( 0, dimension2df(128, 128), vector3df(20,-20,150) );
	flare->setMaterialTexture( 0, driver->getTexture( "../media/Space/rainbow.tga" ) );
	cb = new ShaderCallBack( flare );
	shader.ApplyShaderToSceneNode( flare, cb, "", "Shader/MenuSunFlare.frag", EMT_TRANSPARENT_ADD_COLOR );
	cb->drop();

	// 飞船
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
		//r->drop();	// 使用Python对象不用内存管理
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
		/*IUIObject* root1 = pEngine->GetUIManager()->GetRootUIObject();
		IUIObject * house = pEngine->GetUIManager()->AddUIBox(root1, 400, 400 );
		house->SetPosition( vector2df( 800, 400 ) );
		house->LoadImage( "../media/UIResource/Menu/scrollbar_hbackground.png" );
		((CUIBox*)house)->test( 10 );*/

		//char buffer[255];
		//stringw str;
		//root = pEngine->GetUIManager()->GetRootUIObject();
		//UIStaticText* abc = new UIStaticText( root, 100, 20, L"你妹", SColor(255,255,255,255) );
		//abc->SetPosition( vector2df(200,200) );
		//abc->SetName( "abc" );
		//abc->SetText( L"尼玛了隔壁" );

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

		IGUIEditBox* box = gui->addEditBox( _T("发gas发的"), core::rect<s32>( 0, 0, 100, 50 ) );*/
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

	//时钟
	f32 timeMs = (f32)MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
	services->setVertexShaderConstant( "TimeMs", (f32*)&timeMs, 1);
}
