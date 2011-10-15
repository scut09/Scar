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

	UIImage* u;//≤‚ ‘”√
	UIImage* v;//≤‚ ‘”√

	UIManager* uiManager;

public:
	StartScene();

	shared_ptr<GameScene> multiplayerScene;

	virtual void Run() ;

	virtual void Init() ;
	virtual void Release() ;

	virtual void Draw();
};