#include "StartScene.h"
#include "def.h"




void StartScene::Run() 
{
	if ( count++ > 200 )
	{
		count = 0;
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

void StartScene::Draw()
{
	driver->draw2DImage(gImg, vector2d<s32>(0,0));
}


