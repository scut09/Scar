#pragma once

#include "GameScene.h"
#include "MyIrrlichtEngine.h"
#include "UIObject.h"

class StartScene : public GameScene
{
	int count;
	MyIrrlichtEngine* pEngine;
	irr::video::IVideoDriver* driver;

	UIImage u;//²âÊÔÓÃ

public:
	StartScene() : count( 0 ), u( MyIrrlichtEngine::GetEngine()->GetVideoDriver(), vector2d<s32>(0,0), 500, 750 )
	{
	}

	shared_ptr<GameScene> multiplayerScene;

	virtual void Run() ;

	virtual void Init() ;
	virtual void Release() ;

	virtual void Draw();
};