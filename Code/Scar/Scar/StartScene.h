#pragma once

#include "GameScene.h"
#include "MyIrrlichtEngine.h"
#include "UIObject.h"

class StartScene : public GameScene
{
	int count;
	MyIrrlichtEngine* pEngine;
	irr::video::IVideoDriver* driver;

	UIImage u;
	ITexture * gImg;

public:
	StartScene() : count( 0 ), u( MyIrrlichtEngine::GetEngine()->GetVideoDriver(), vector2d<s32>(100,100), 200, 200 )
	{
		gImg = MyIrrlichtEngine::GetEngine()->GetVideoDriver()->getTexture("D:\\f.jpg");
	}

	shared_ptr<GameScene> multiplayerScene;

	virtual void Run() ;

	virtual void Init() ;
	virtual void Release() ;

	virtual void Draw();
};