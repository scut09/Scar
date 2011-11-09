/********************************************************************
    创建时间: 2011-11-9   16:07
    文件名:   GameSceneManager.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     场景管理类

*********************************************************************/

#ifndef GameSceneManager_h__
#define GameSceneManager_h__

#include "GameScene.h"
#include <list>
#include <boost/thread.hpp>

/*
** 名字：GameSceneManager
** 说明：场景管理类，用于创建场景
**
*/
class GameSceneManager
{
public:
	GameSceneManager();

	~GameSceneManager();

	// 通过名字获取场景
	GameScene* GetSceneByName( const std::string& name );

	// 获取当前场景
	GameScene* GetCurrentGameScene()
	{
		return CurrentGameScene;
	}

	// 设置当期场景
	void SetCurrentGameScene( GameScene* scene );

	/************************************************************************/
	/* 添加菜单用                                                            */
	/************************************************************************/
	// 添加菜单场景
	GameScene* AddMenuScene( const std::string& menusceneName );

	// 添加多人游戏场景
	GameScene* AddMutilplayerScene();

	// 添加开始场景，暂时没用
	GameScene* AddStartScene();

private:
	GameScene*	CurrentGameScene;		// 当前场景

	std::list<GameScene*> Scenes;		// 所有的场景

	boost::mutex ChangeGameSceneMutex;	// 互斥

};

#endif // GameSceneManager_h__