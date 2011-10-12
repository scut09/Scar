#pragma once

#include "GameScene.h"
#include "MyIrrlichtEngine.h"
#include "UIObject.h"

class StartScene : public GameScene
{
	int count;
	MyIrrlichtEngine* pEngine;
	irr::video::IVideoDriver* driver;

public:
	StartScene() : count( 0 )
	{}

	shared_ptr<GameScene> multiplayerScene;

	virtual void Run() ;

	virtual void Init() ;
	virtual void Release() ;

	virtual void Draw();
};