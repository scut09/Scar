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
	AnimationManager* m_pAnimation;

public:
	MultiplayerScene() : m_pAnimation( 0 )
	{	
	}

	virtual void Run();
	virtual void Init();
	virtual void Release();

};


#endif // MultiplayerScene_h__