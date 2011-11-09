#ifndef MenuScene_h__
#define MenuScene_h__

#include "GameScene.h"
#include "MyIrrlichtEngine.h"
#include "AllUIObjects.h"
#include "UIManager.h"
#include "irrlicht.h"
#include <string>
#include "SceneNodeShader.h"
using namespace irr;

class MenuScene : public GameScene
{
	int count;
	MyIrrlichtEngine* pEngine;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	scene::ICameraSceneNode* camera;
	SceneNodeShader shader;

	IUIObject* root;

	std::string SceneName;

	bool	IsFirstRun;

	// Shader»Øµ÷º¯Êý
	class ShaderCallBack : public video::IShaderConstantSetCallBack
	{
	private:
		scene::ISceneNode* Node;

	public:
		ShaderCallBack( scene::ISceneNode* node )
			:Node( node )
		{

		}

		virtual void OnSetConstants( IMaterialRendererServices* services, s32 userData );
	};


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
