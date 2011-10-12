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

	u.SetCenter( vector2d<s32>( count, count ) );

}

void StartScene::Draw()
{
	u.Draw();
}

void StartScene::Init() 
{
	pEngine = MyIrrlichtEngine::GetEngine();
	driver = pEngine->GetVideoDriver();

	u.SetImage("pic1.jpg");
}

void StartScene::Release() 
{


}


