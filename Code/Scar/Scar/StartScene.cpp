#include "StartScene.h"


void StartScene::Run() 
{
	

	/*if ( count++ > 5000 )
	{
		pEngine->currentScene = multiplayerScene;
		Release();
		pEngine->currentScene->Init();
	}*/
}

void StartScene::Init() 
{
	pEngine = MyIrrlichtEngine::GetEngine();
	driver = pEngine->GetVideoDriver();
}

void StartScene::Release() 
{
}


