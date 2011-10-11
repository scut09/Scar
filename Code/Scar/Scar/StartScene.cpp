#include "StartScene.h"


void StartScene::Run() 
{
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();

	irr::video::IVideoDriver* driver = pEngine->GetVideoDriver();

	if ( count++ > 5000 )
	{
		pEngine->currentScene = multiplayerScene;
		Release();
		pEngine->currentScene->Init();
	}
}

void StartScene::Init() 
{
}

void StartScene::Release() 
{
}


