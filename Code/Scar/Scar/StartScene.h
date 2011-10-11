#pragma once

#include "GameScene.h"
#include "MyIrrlichtEngine.h"

class StartScene : public GameScene
{
	int count;


public:
	StartScene() : count( 0 )
	{}

	GameScene* multiplayerScene;

	virtual void Run() ;

	virtual void Init() ;
	virtual void Release() ;


};