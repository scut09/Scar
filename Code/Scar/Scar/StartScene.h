#pragma once

#include "GameScene.h"
#include "AllUIObjects.h"
#include "UIManager.h"

class boost::python::object;

class StartScene : public GameScene
{
	int count;
	MyIrrlichtEngine* pEngine;
	irr::video::IVideoDriver* driver;

	UIImage* u;//������
	UIImage* v;//������
	UIButton* bt; // ������

	UIManager* uiManager;

	boost::python::object root;

public:
	StartScene();

	shared_ptr<GameScene> multiplayerScene;

	virtual void Run() ;

	virtual void Init() ;
	virtual void Release() ;

	virtual void Draw();
};