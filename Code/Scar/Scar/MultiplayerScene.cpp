/********************************************************************
    ����ʱ��: 2011-10-8   16:01
    �ļ���:   MultiplayerScene.cpp
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     ������Ϸ����

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
	// ʹ��Pythonģ�����ģ��
	PythonManager* p = PythonManager::GetPythonManager();

	// ��ȡ����
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	scene::ISceneManager* smgr = pEngine->GetSceneManager();
	m_pModelMan = pEngine->GetModelManager();
	auto driver = pEngine->GetVideoDriver();

	//  ���������
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

	//��������
	auto planet = smgr->addSphereSceneNode( 4e5 );
	if ( planet )
	{
		// ��������
		planet->setName( "planet1" );
		// ��������
		planet->setMaterialTexture( 0, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/planet6.jpg") ) );
		// ������ת
		auto rot = smgr->createRotationAnimator( vector3df( 0, 0.003f, 0) );
		planet->addAnimator( rot );
		rot->drop();
		// ���ó�ʼ��С
		planet->setScale( vector3df( .01f ) );
		// ���Ŷ���
		auto sca = new MySceneNodeAnimatorScale( 0, 8000, vector3df( 1.99f ), AS_MT_LOG );
		planet->addAnimator( sca );
		sca->drop();
		// ������Զ��Ծ�ͷ
		auto relstayAni = new RelateCameraAnimatorStay( 0, 1000, m_pCamera, vector3df( -2e5, 0, 8e5 ) );
		planet->addAnimator( relstayAni );
		relstayAni->drop();
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
		// ���ó�ʼ��С
		moon->setScale( vector3df( .001f ) );
		//moon->setVisible( false );
		// ���Ŷ���
		auto sca = new MySceneNodeAnimatorScale( 2000, 6000, vector3df( 1.999f ), AS_MT_LOG, 500 );
		moon->addAnimator( sca );
		sca->drop();
		// ��Ծ����Ч��
		auto relmovAni = new RelateCameraAnimatorMove( 2000, 6000, m_pCamera,
			vector3df(1e5, 0, 2.5e5), vector3df(1e5, 0, -2.5e5), RM_MT_LOG, 800 );
		moon->addAnimator( relmovAni );
		relmovAni->drop();
	}



	//���ؿռ�վģ��
	IMeshSceneNode* station = smgr->addMeshSceneNode( smgr->getMesh( _T("../modle/station/cs1.obj") ) );
	if ( station )
	{
		// ��������
		station->setName( "station1" );
		// ���ó�ʼ��С
		//station->setScale( vector3df( .001f));
		//station->setVisible(false);
		// ���Ŷ���
		//auto sca = new MySceneNodeAnimatorLogScale( 5000, 5000, vector3df( 1.999f ), 500 );
		//moon->addAnimator( sca );
		//sca->drop();
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

	/*m_pSkyBox = smgr->addSkyBoxSceneNode(
		driver->getTexture("../media/irrlicht2_up.jpg"),
		driver->getTexture("../media/irrlicht2_dn.jpg"),
		driver->getTexture("../media/irrlicht2_lf.jpg"),
		driver->getTexture("../media/irrlicht2_rt.jpg"),
		driver->getTexture("../media/irrlicht2_ft.jpg"),
		driver->getTexture("../media/irrlicht2_bk.jpg"));*/

	// ��պ�
	m_pSkyBox = smgr->addSkyBoxSceneNode(
		driver->getTexture( _T("../media/Space/c07_up.jpg") ),
		driver->getTexture( _T("../media/Space/c07_dn.jpg") ),
		driver->getTexture( _T("../media/Space/c07_lt.jpg") ),
		driver->getTexture( _T("../media/Space/c07_rt.jpg") ),
		driver->getTexture( _T("../media/Space/c07_ft.jpg") ),
		driver->getTexture( _T("../media/Space/c07_bk.jpg") ));	
	//��֪��Ϊʲô����պ���Сһ�㷴��������ڱ�
	m_pSkyBox->setScale( vector3df( .1f, .1f, .1f ) );

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


	// ������ע��receiver���¼�����ص�����
	static_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [ pEngine ]( const SEvent& event )->void*
	{	
		//control.OnEvent( event );
		pEngine;		// ����ָ��
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

