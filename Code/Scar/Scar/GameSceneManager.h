/********************************************************************
    ����ʱ��: 2011-11-9   16:07
    �ļ���:   GameSceneManager.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     ����������

*********************************************************************/

#ifndef GameSceneManager_h__
#define GameSceneManager_h__

#include "GameScene.h"
#include <list>
#include <boost/thread.hpp>

/*
** ���֣�GameSceneManager
** ˵�������������࣬���ڴ�������
**
*/
class GameSceneManager
{
public:
	GameSceneManager();

	~GameSceneManager();

	// ͨ�����ֻ�ȡ����
	GameScene* GetSceneByName( const std::string& name );

	// ��ȡ��ǰ����
	GameScene* GetCurrentGameScene()
	{
		return CurrentGameScene;
	}

	// ���õ��ڳ���
	void SetCurrentGameScene( GameScene* scene );

	/************************************************************************/
	/* ��Ӳ˵���                                                            */
	/************************************************************************/
	// ��Ӳ˵�����
	GameScene* AddMenuScene( const std::string& menusceneName );

	// ��Ӷ�����Ϸ����
	GameScene* AddMutilplayerScene();

	// ��ӿ�ʼ��������ʱû��
	GameScene* AddStartScene();

private:
	GameScene*	CurrentGameScene;		// ��ǰ����

	std::list<GameScene*> Scenes;		// ���еĳ���

	boost::mutex ChangeGameSceneMutex;	// ����

};

#endif // GameSceneManager_h__