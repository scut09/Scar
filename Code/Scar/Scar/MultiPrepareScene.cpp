#include "MultiPrepareScene.h"
#include "MyIrrlichtEngine.h"
#include "AllUIObjects.h"
#include "UIAnimators.h"

#include <iostream>

using namespace irr;
using namespace irr::video;
using namespace irr::scene;

void MultiPrepareScene::Run()
{
	std::cout<<"!";
}

void MultiPrepareScene::Init()
{
	using namespace irr::core;
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	IVideoDriver* driver = pEngine->GetVideoDriver();
	ISceneManager* smgr = pEngine->GetSceneManager();

	//// 增加摄像机
	//m_pCamera = smgr->addCameraSceneNode( 0, vector3df(0), vector3df( 0, -1, -1 ));
	//m_pCamera->setAspectRatio( (f32)driver->getScreenSize().Width / (f32)driver->getScreenSize().Height);
	//m_pCamera->setFOV( 1 );

	//// 增加天空盒
	//m_pSkyBox = smgr->addSkyBoxSceneNode( 
	//	driver->getTexture( "../media/Dock/cd_up.tga" ),
	//	driver->getTexture( "../media/Dock/cd_dn.tga" ),
	//	driver->getTexture( "../media/Dock/cd_lt.tga" ),
	//	driver->getTexture( "../media/Dock/cd_rt.tga" ),
	//	driver->getTexture( "../media/Dock/cd_ft.tga" ),
	//	driver->getTexture( "../media/Dock/cd_bk.tga" ) );
	//m_pSkyBox->setMaterialFlag( EMF_ANTI_ALIASING, true );

	uiManager = new UIManager( pEngine->GetDevice()->getTimer() );
	UIImage* root = new UIImage( 0, 0, 0 );
	uiManager->SetRoot( root );

	UIImage* bg = new UIImage( root, 1024, 1024, 0, 0, vector2df( 512, 512 ) );
	bg->LoadImage( "../media/UIResource/Menu/fw_500001_background.tga" );
}

void MultiPrepareScene::Release()
{
	
}

void MultiPrepareScene::Draw()
{
	uiManager->RunTree();
}
