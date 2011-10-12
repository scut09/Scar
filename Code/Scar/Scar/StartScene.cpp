#include "StartScene.h"
#include "def.h"

UIImage u( MyIrrlichtEngine::GetEngine()->GetVideoDriver(), vector2d<s32>(100,100), 200, 200 );
ITexture * gImg = MyIrrlichtEngine::GetEngine()->GetVideoDriver()->getTexture("D:\\f.jpg");


void StartScene::Run() 
{
	//driver->beginScene(true, true, video::SColor(255,255,255,255));
	driver->draw2DImage(gImg, vector2d<s32>(0,0));
	//driver->endScene();
	//u.Draw();
	if ( count++ > 200 )
	{
		pEngine->currentScene = multiplayerScene;
		Release();
		pEngine->currentScene->Init();
	}

}

void StartScene::Init() 
{
	pEngine = MyIrrlichtEngine::GetEngine();
	driver = pEngine->GetVideoDriver();

	u.SetImage("D:\\f.jpg");
	//driver->getTexture("pic1.jpg");


}

void StartScene::Release() 
{


}


