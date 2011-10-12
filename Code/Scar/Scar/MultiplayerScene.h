/********************************************************************
    ����ʱ��: 2011-10-8   15:57
    �ļ���:   MultiplayerScene.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     ������Ϸ����Ϸ����

*********************************************************************/

#ifndef MultiplayerScene_h__
#define MultiplayerScene_h__

#include "GameScene.h"
#include "MyIrrlichtEngine.h"

class MultiplayerScene : public GameScene
{
	AnimationManager*			m_pAnimationMan;
	scene::ICameraSceneNode*	m_pCamera;
	scene::ISceneNode*			m_pSkyBox;
	ModelManager*				m_pModelMan;

public:
	shared_ptr<GameScene> startScene;

public:
	MultiplayerScene() : m_pAnimationMan( 0 ), m_pCamera( 0 ), m_pModelMan( 0 )
	{	
	}

	virtual void Run();
	virtual void Init();
	virtual void Release();

};


#endif // MultiplayerScene_h__