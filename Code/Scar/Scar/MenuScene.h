#ifndef MenuScene_h__
#define MenuScene_h__

#include "GameScene.h"
#include "MyIrrlichtEngine.h"
#include "AllUIObjects.h"
#include "UIManager.h"
#include <string>

class MenuScene : public GameScene
{
	int count;
	MyIrrlichtEngine* pEngine;
	irr::video::IVideoDriver* driver;

	IUIObject* root;

	UIManager* uiManager;

	std::string SceneName;

	bool	IsFirstRun;

public:
	MenuScene( const std::string& sceneName ) : SceneName( sceneName ), IsFirstRun( true )
	{

	}

	virtual void Run();

	virtual void Init();

	virtual void Release();

	virtual void Draw();
};

#endif // MenuScene_h__
