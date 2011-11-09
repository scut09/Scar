/********************************************************************
    创建时间: 2011-11-9   1:05
    文件名:   AgentPlayer.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     代理玩家，也就是电脑人

*********************************************************************/

#ifndef AgentPlayer_h__
#define AgentPlayer_h__

#include "IPlayer.h"
#include "PlayerManager.h"
#include "NetworkBase.h"

/*
** 名字：AgentPlayer
** 说明：Computer controls this player, just like agent in a film
**
*/
class IAgentPlayer : public IPlayer
{
public:
	IAgentPlayer( IShip* playerShip, PlayerManager* mgr, boost::shared_ptr<Network::NetworkBase> server );

	virtual bool IsRobot()
	{
		return true;
	}

	//virtual void Update()
	//{
	//	// Do some control here
	//}


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
	virtual bool SearchTarget( boost::shared_ptr<IPlayer>& outPlayer, int range = 3500 );

protected:

	PlayerManager*					Manager;		// 玩家飞船管理类
	boost::shared_ptr<Network::NetworkBase>	Server;			// 服务端
};


#endif // AgentPlayer_h__