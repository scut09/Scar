/********************************************************************
    创建时间: 2011-10-8   15:51
    文件名:   GameScene.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     场景基类

*********************************************************************/

#ifndef GameScene_h__
#define GameScene_h__

#include <vector>
#include <string>

/*
** 名字：GameScene
** 说明：所有游戏场景的抽象基类
**		 在游戏引擎的总循环中，
**
*/
class GameScene
{
public:
	GameScene() : Scenes( 20, 0 ) {}

	virtual ~GameScene() {}

	std::vector<GameScene*> Scenes;

	std::string	Name;

	const std::string& GetName() const
	{
		return Name;
	}

	void SetName( const std::string& name )
	{
		Name = name;
	}

	//************************************
	// 函数名:  GameScene::Run
	// 返回值:  void
	// 函数修饰:
	// 描述：   在游戏总循环中，每次都会被调用的
	//************************************
	virtual void Run() = 0;

	//************************************
	// 函数名:  GameScene::Init
	// 返回值:  void
	// 函数修饰:
	// 描述：   初始化场景，在里面加载资源
	//************************************
	virtual void Init() = 0;

	//************************************
	// 函数名:  GameScene::Release
	// 返回值:  void
	// 函数修饰:
	// 描述：   释放这个场景所加载的资源
	//************************************
	virtual void Release() = 0;

	virtual void Draw() {}
	
};


#endif // GameScene_h__
