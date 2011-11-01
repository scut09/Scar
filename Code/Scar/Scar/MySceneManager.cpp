#include "MySceneManager.h"
#include "MyIrrlichtEngine.h"

MySceneManager::MySceneManager()
{
	smgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();
}