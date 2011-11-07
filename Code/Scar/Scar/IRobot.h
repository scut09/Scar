/********************************************************************
    创建时间: 2011-11-6   22:38
    文件名:   IRobot.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     AI机器人

*********************************************************************/
#ifndef IRobot_h__
#define IRobot_h__


#include "CCameraSceneNode.h"
#include "NetworkBase.h"
#include "PlayerManager.h"
#include "GameBag.h"

using namespace Network;


/*
** 名字：
** 说明：为什么要继承irr::scene::CCameraSceneNode，这个是历史遗留问题导致，因为之前很多东西是和摄像机绑定在一起的
**
*/
class IRobot : public irr::scene::CCameraSceneNode
{
public:
	//************************************
	// 返回值:  
	// 参数:    IShip * ship								自己控制的船
	// 参数:    PlayerManager * mgr						包含所有玩家信息的玩家管理类
	// 参数:    std::shared_ptr<NetworkBase> server		服务端指针
	// 描述：   ctor
	//************************************
	IRobot( IShip* ship, PlayerManager* mgr, std::shared_ptr<NetworkBase> server );

	// 更新自己
	virtual void Update() = 0;

protected:
	// 发送自己的移动信息
	void SendMove( const vector3df& pos );
	// 发送自己的旋转信息
	void SendRotate( const core::vector3df& rot );

	// 模拟左键按下
	void DoLeftButtonDown();
	// 模拟左键弹起
	void DoLeftButtonUp();
	// 模拟按下键盘
	void DoPress( EKEY_CODE key )
	{
		SEvent ev;
		ev.EventType = EET_KEY_INPUT_EVENT;
		ev.KeyInput.Key = key;
		ev.KeyInput.PressedDown = true;

		OnEvent( ev );
	}
	// 模拟弹起键盘
	void DoUnpress( EKEY_CODE key )
	{
		SEvent ev;
		ev.EventType = EET_KEY_INPUT_EVENT;
		ev.KeyInput.Key = key;
		ev.KeyInput.PressedDown = false;

		OnEvent( ev );
	}
	

	// 搜索目标
	virtual IShip* SearchTarget( int range = 3500 );

protected:

	IShip*							RobotShip_;		// 自己控制的船
	PlayerManager*					Manager;		// 玩家飞船管理类
	std::shared_ptr<NetworkBase>	Server;			// 服务端
};



#endif // IRobot_h__
