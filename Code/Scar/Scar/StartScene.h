#pragma once
#include "def.h"
#include "def.h"
#include "GameScene.h"
#include "AllUIObjects.h"
#include "UIManager.h"
#include "MyIrrlichtEngine.h"

class StartScene : public GameScene
{
	int count;
	MyIrrlichtEngine* pEngine;
	irr::video::IVideoDriver* driver;

	UIImage* u;//≤‚ ‘”√
	UIImage* v;//≤‚ ‘”√
	UIButton* bt; // ≤‚ ‘”√

	UIManager* uiManager;

public:
	StartScene();

	virtual void Run() ;

	virtual void Init() ;
	virtual void Release() ;

	virtual void Draw();
};