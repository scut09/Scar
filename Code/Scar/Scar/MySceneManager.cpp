#include "MySceneManager.h"
#include "MyIrrlichtEngine.h"

MySceneManager::MySceneManager()
{
	auto pEngine = MyIrrlichtEngine::GetEngine();
	smgr	= pEngine->GetSceneManager();
	driver	= pEngine->GetVideoDriver();
	timer	= pEngine->GetDevice()->getTimer();
}