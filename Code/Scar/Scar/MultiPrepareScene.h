#ifndef MultiPrepare_h__
#define MultiPrepare_h__

/********************************************************************
	创建日期:	2011/11/06
	文件名: 	C:\Users\Administrator\Desktop\工作\SCAR项目组\opengl-scut\Code\Scar\Scar\MultiPrepare.h
	作者:		屠文翔
	
	描述:		多人游戏准备场景
				选择飞船、武器、装备
*********************************************************************/

#include "GameScene.h"
#include "MyIrrlichtEngine.h"

class MultiPrepareScene : public GameScene
{
	scene::ICameraSceneNode*	m_pCamera;
	scene::ISceneNode*			m_pSkyBox;

public:
	MultiPrepareScene() : m_pCamera( 0 )
	{
	}

	~MultiPrepareScene()
	{
		Release();
	}

	virtual void Run();

	virtual void Init();

	virtual void Release();

	virtual void Draw();

};

#endif // MultiPrepare_h__
