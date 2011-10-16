#ifndef MenuScene_h__
#define MenuScene_h__

#include "GameScene.h"
#include "MyIrrlichtEngine.h"
#include "AllUIObjects.h"
#include "UIManager.h"

class MenuScene : public GameScene
{
	int count;
	MyIrrlichtEngine* pEngine;
	irr::video::IVideoDriver* driver;

	IUIObject* root;

	UIManager* uiManager;

public:
	MenuScene()
	{

	}

	virtual void Run() 
	{

	}

	virtual void Init() 
	{

	}

	virtual void Release() 
	{

	}

	virtual void Draw()
	{

	}
};

#endif // MenuScene_h__
