#pragma once

#include "GameScene.h"
#include "MyIrrlichtEngine.h"
#include "IUIObject.h"
#include "UIObject.h"
#include "UIManager.h"

class StartScene : public GameScene
{
	int count;
	MyIrrlichtEngine* pEngine;
	irr::video::IVideoDriver* driver;

	UIImage* u;//²âÊÔÓÃ
	UIImage* v;//²âÊÔÓÃ

	UIManager* uiManager;

public:
	StartScene() : count( 0 )
	{
		u = new UIImage( NULL, MyIrrlichtEngine::GetEngine()->GetVideoDriver(), 500, 750 );
		v = new UIImage( NULL, MyIrrlichtEngine::GetEngine()->GetVideoDriver(), 100, 150 ); 
		uiManager = new UIManager(MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer());
	}

	shared_ptr<GameScene> multiplayerScene;

	virtual void Run() ;

	virtual void Init() ;
	virtual void Release() ;

	virtual void Draw();
};