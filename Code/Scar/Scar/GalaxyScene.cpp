/********************************************************************
    创建时间: 2011-11-10   15:57
    文件名:   GalaxyScene.h
    作者:     杨旭瑜 Hurrman
    说明:     阵营选择场景

*********************************************************************/
#include "GalaxyScene.h"
#include "AllAnimators.h"
#include "AllUIObjects.h"
#include "BulletNode.h"
#include "CSceneNodeAnimatorSelfDelFlyStraight.h"
#include "EngineHeader.h"
#include "Flame.h"
#include "Frigate.h"
#include "MultiplayerScene.h"
#include "MySceneManager.h"
#include "PythonManager.h"
#include "RobotShip.h"
#include "Robot_Client.h"
#include "SpriteFlame.h"
#include "UIAnimators.h"
#include "UIManager.h"
#include <iostream>



#define PRINT_POS( pos ) std::cout << #pos ## " " << pos.X << ' ' << pos.Y << ' ' << pos.Z << std::endl;

void GalaxyScene::Init()
{
		// 获取引擎
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	scene::ISceneManager* smgr = pEngine->GetSceneManager();
	smgr->clear();

	m_pModelMan = pEngine->GetModelManager();
	auto driver = pEngine->GetVideoDriver();

	pEngine->SetUIManager( boost::shared_ptr<UIManager>( new UIManager( pEngine->GetDevice()->getTimer() ) ) );

	shader = new SceneNodeShader();
	//m_pCamera = smgr->addCameraSceneNode(0, vector3df(0.0, 0.0, -1000));
	m_pCamera = smgr->addCameraSceneNodeFPS();
	m_pCamera->setFarValue(10000);
	m_pCamera->setFOV( 1 );

	pEngine->GetDevice()->getCursorControl()->setVisible(true);

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
		m_pSkyBox->setScale( vector3df( .1f, .1f, .1f ) );
		m_pSkyBox->setMaterialTexture( 1, driver->getTexture("../media/Space/stars.png") );
		GeneralCallBack* cb = new GeneralCallBack(m_pSkyBox);
		shader->ApplyShaderToSceneNode( m_pSkyBox, cb, "Shader/universeV.txt", "Shader/universeF.txt" );
		cb->drop();
	}

	// 恒星
	auto Sun = smgr->addSphereSceneNode( 100, 100 );

	if ( Sun )
	{
		// 设置名称
		Sun->setName( "planet1" );
		// 加载纹理
		Sun->setMaterialTexture( 0, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/planet5.jpg") ) );
		Sun->setMaterialTexture( 1, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/night0.jpg") ) );
		Sun->setMaterialTexture( 2, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/a.tga") ) );

		// Shader
		GeneralCallBack* cb = new GeneralCallBack( Sun );
		shader->ApplyShaderToSceneNode( Sun, cb, "Shader/PlanetGroundV.txt", "Shader/PlanetGroundF.txt" );
		cb->drop();
	}

	// 阵营1
	auto Planet1 = smgr->addSphereSceneNode( 50, 64 );

	if ( Planet1 )
	{
		// 设置名称
		Planet1->setName( "planet1" );
		Planet1->setPosition(Sun->getPosition() + vector3df(-700.0, 350.0, -10.0)); 
		// 加载纹理
		Planet1->setMaterialTexture( 0, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/planet5.jpg") ) );
		Planet1->setMaterialTexture( 1, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/night0.jpg") ) );
		Planet1->setMaterialTexture( 2, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/a.tga") ) );

		// Shader
		GeneralCallBack* cb = new GeneralCallBack( Planet1 );
		shader->ApplyShaderToSceneNode( Planet1, cb, "Shader/PlanetGroundV.txt", "Shader/PlanetGroundF.txt" );
		cb->drop();
	}

	// 阵营1卫星
	auto satellite1 = smgr->addSphereSceneNode( 20, 64 );

	if ( satellite1 )
	{
		// 设置名称
		satellite1->setName( "satellite1" );
		satellite1->setPosition(Planet1->getPosition() + vector3df(200, -100, -10.0));
		// 加载纹理
		satellite1->setMaterialTexture( 0, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/planet5.jpg") ) );
		satellite1->setMaterialTexture( 1, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/night0.jpg") ) );
		satellite1->setMaterialTexture( 2, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/a.tga") ) );

		// Shader
		GeneralCallBack* cb = new GeneralCallBack( satellite1 );
		shader->ApplyShaderToSceneNode( satellite1, cb, "Shader/PlanetGroundV.txt", "Shader/PlanetGroundF.txt" );
		cb->drop();
	}




	// 阵营1
	auto Planet2 = smgr->addSphereSceneNode( 50, 64 );

	if ( Planet2 )
	{
		// 设置名称
		Planet2->setName( "planet2" );
		Planet2->setPosition(Sun->getPosition() + vector3df(700.0, -350.0, -10.0)); 
		// 加载纹理
		Planet2->setMaterialTexture( 0, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/planet5.jpg") ) );
		Planet2->setMaterialTexture( 1, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/night0.jpg") ) );
		Planet2->setMaterialTexture( 2, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/a.tga") ) );

		// Shader
		GeneralCallBack* cb = new GeneralCallBack( Planet2 );
		shader->ApplyShaderToSceneNode( Planet2, cb, "Shader/PlanetGroundV.txt", "Shader/PlanetGroundF.txt" );
		cb->drop();
	}

	// 阵营1卫星
	auto Satellite2 = smgr->addSphereSceneNode( 20, 64 );

	if ( Satellite2 )
	{
		// 设置名称
		Satellite2->setName( "Satellite2" );
		Satellite2->setPosition(Planet2->getPosition() + vector3df(200, -100, -10.0));
		// 加载纹理
		Satellite2->setMaterialTexture( 0, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/planet5.jpg") ) );
		Satellite2->setMaterialTexture( 1, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/night0.jpg") ) );
		Satellite2->setMaterialTexture( 2, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/a.tga") ) );

		auto rot = smgr->createFlyCircleAnimator(Planet2->getPosition(),200.f, 0.01);
		Satellite2->addAnimator( rot );
		rot->drop();

		// Shader
		GeneralCallBack* cb = new GeneralCallBack( Satellite2 );
		shader->ApplyShaderToSceneNode( Satellite2, cb, "Shader/PlanetGroundV.txt", "Shader/PlanetGroundF.txt" );
		cb->drop();
	}



	//auto billboard = smgr->addBillboardSceneNode();
	//billboard->setPosition(vector3df(0, 0, -500));
	//billboard->setMaterialTexture(0, pEngine->GetVideoDriver()->getTexture("../media/Galaxy/galaxy1.png"));
	//billboard->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
	//billboard->setMaterialFlag(video::EMF_LIGHTING, false);
	//billboard->setMaterialFlag(video::EMF_ZBUFFER, false);
	//billboard->setSize(core::dimension2d<f32>(200.0f, 200.0f));

	//auto billboard1 = smgr->addBillboardSceneNode();
	//billboard1->setPosition(vector3df(0, 500, -500));
	//billboard1->setMaterialTexture(0, pEngine->GetVideoDriver()->getTexture("../media/Galaxy/galaxy2.jpg"));
	//billboard1->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
	//billboard1->setMaterialFlag(video::EMF_LIGHTING, false);
	//billboard1->setMaterialFlag(video::EMF_ZBUFFER, false);
	//billboard1->setSize(core::dimension2d<f32>(200.0f, 200.0f));

	//auto billboard2 = smgr->addBillboardSceneNode();
	//billboard2->setPosition(vector3df(0, 0, 500));
	//billboard2->setMaterialTexture(0, pEngine->GetVideoDriver()->getTexture("../media/Galaxy/galaxy3.jpg"));
	//billboard2->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
	//billboard2->setMaterialFlag(video::EMF_LIGHTING, false);
	//billboard2->setMaterialFlag(video::EMF_ZBUFFER, false);
	//billboard2->setSize(core::dimension2d<f32>(200.0f, 200.0f));

	//auto billboard3 = smgr->addBillboardSceneNode();
	//billboard3->setPosition(vector3df(500, 0, -500));
	//billboard3->setMaterialTexture(0, pEngine->GetVideoDriver()->getTexture("../media/Galaxy/galaxy4.jpg"));
	//billboard3->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
	//billboard3->setMaterialFlag(video::EMF_LIGHTING, false);
	//billboard3->setMaterialFlag(video::EMF_ZBUFFER, false);
	//billboard3->setSize(core::dimension2d<f32>(200.0f, 200.0f));

	//auto billboard4 = smgr->addBillboardSceneNode();
	//billboard4->setPosition(vector3df(0, 690, 500));
	//billboard4->setMaterialTexture(0, pEngine->GetVideoDriver()->getTexture("../media/Galaxy/galaxy5.jpg"));
	//billboard4->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
	//billboard4->setMaterialFlag(video::EMF_LIGHTING, false);
	//billboard4->setMaterialFlag(video::EMF_ZBUFFER, false);
	//billboard4->setSize(core::dimension2d<f32>(200.0f, 200.0f));


}


void GalaxyScene::Draw()
{
	
}


void GalaxyScene::Run()
{
	//MessageBox(0, L"f", L"f", MB_OK);

	std::cout << m_pCamera->getPosition().X << m_pCamera->getPosition().Y << m_pCamera->getPosition().Z << std::endl;
}

void GalaxyScene::Release()
{
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	scene::ISceneManager* smgr = pEngine->GetSceneManager();
	smgr->clear();
}