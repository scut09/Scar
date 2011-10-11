/********************************************************************
    创建时间: 2011-10-8   15:57
    文件名:   MultiplayerScene.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     多人游戏的游戏场景

*********************************************************************/

#ifndef MultiplayerScene_h__
#define MultiplayerScene_h__

#include "GameScene.h"

class MultiplayerScene : public GameScene
{
public:
	virtual void Run();
	virtual void Init();
	virtual void Release();

};


#endif // MultiplayerScene_h__