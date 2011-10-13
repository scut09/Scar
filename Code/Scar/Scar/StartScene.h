#pragma once

#include "GameScene.h"
#include "MyIrrlichtEngine.h"
#include "UIObject.h"
#include "IUIObject.h"

class StartScene : public GameScene
{
	int count;
	MyIrrlichtEngine* pEngine;
	irr::video::IVideoDriver* driver;

	UIImage* u;//²âÊÔÓÃ
	UIImage* v;//²âÊÔÓÃ

public:
	StartScene() : count( 0 ), u( new UIImage( MyIrrlichtEngine::GetEngine()->GetVideoDriver(), vector2d<f32>(0,0), 500, 750 ) ),
		v( new UIImage( MyIrrlichtEngine::GetEngine()->GetVideoDriver(), vector2d<f32>(50,50), 250, 375 ) )
	{
	}

	shared_ptr<GameScene> multiplayerScene;

	virtual void Run() ;

	virtual void Init() ;
	virtual void Release() ;

	virtual void Draw();
};