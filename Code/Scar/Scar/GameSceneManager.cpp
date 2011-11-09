#include "GameSceneManager.h"
#include "MultiplayerScene.h"
#include "MenuScene.h"
#include "StartScene.h"
#include "MyIrrlichtEngine.h"
#include "EventListener.h"


GameSceneManager::GameSceneManager() : CurrentGameScene( NULL )
{

}

GameSceneManager::~GameSceneManager()
{
	for ( auto iter = Scenes.begin(); iter != Scenes.end(); ++iter )
	{
		delete *iter;
	}
}

void GameSceneManager::SetCurrentGameScene( GameScene* scene )
{
	boost::mutex::scoped_lock lock( ChangeGameSceneMutex );

	if ( CurrentGameScene )
	{
		//MyIrrlichtEngine::currentScene->Release();
		// 延迟删除
		MyIrrlichtEngine::GetEngine()->AddToDeletionQueue( CurrentGameScene );
		// 清除掉自己注册的回调函数，否则会因为引用销毁的东西而导致崩溃
		static_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( 
			[]( const SEvent& event )->void*
		{	
			return 0;
		} );
	}

	CurrentGameScene = scene;

	if ( CurrentGameScene )
	{
		CurrentGameScene->Init();
	}
}

GameScene* GameSceneManager::GetSceneByName( const std::string& name )
{
	std::list<GameScene*>::iterator iter = Scenes.begin();
	for ( ; iter != Scenes.end(); ++iter )
	{
		if ( (*iter)->GetName() == name )
		{
			break;
		}
	}

	if ( iter != Scenes.end() )
	{
		return *iter;
	}

	return NULL;
}

GameScene* GameSceneManager::AddMenuScene( const std::string& sceneName )
{
	GameScene* scene = new MenuScene( sceneName );
	Scenes.push_back( scene );
	return scene;
}

GameScene* GameSceneManager::AddMutilplayerScene()
{
	GameScene* scene = new MultiplayerScene;
	Scenes.push_back( scene );
	return scene;
}

GameScene* GameSceneManager::AddStartScene()
{
	GameScene* scene = new StartScene;
	Scenes.push_back( scene );
	return scene;
}
