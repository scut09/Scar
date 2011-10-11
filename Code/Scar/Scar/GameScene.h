/********************************************************************
    创建时间: 2011-10-8   15:51
    文件名:   GameScene.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     场景基类

*********************************************************************/

#ifndef GameScene_h__
#define GameScene_h__


class GameScene
{
public:
	virtual ~GameScene() {}

	virtual void Run() = 0;
	virtual void Init() = 0;
	virtual void Release() = 0;
	
};


#endif // GameScene_h__
