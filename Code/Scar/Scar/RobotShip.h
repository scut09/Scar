/********************************************************************
创建时间: 2011-11-7   14:09
文件名:   RobotShip.h
作者:     华亮 Cedric Porter [ Stupid ET ]	
说明:     飞船机器人

*********************************************************************/

#ifndef RobotShip_h__
#define RobotShip_h__

#include "IAgentPlayer.h"

class ShipAgentPlayer : public IAgentPlayer
{
public:
	enum RobotState
	{
		Idle,		// 空闲状态
		Track,		// 跟踪状态
		Attack		// 攻击状态
	};

public:
	ShipAgentPlayer( IShip* ship, PlayerManager* mgr, boost::shared_ptr<Network::NetworkBase> server );

	virtual void Update();

private:
	RobotState		State;
	bool			fireOnce;
	u32				TimePoint;

};
#endif // RobotShip_h__