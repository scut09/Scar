/********************************************************************
    创建时间: 2011-11-6   22:38
    文件名:   IRobot.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     AI机器人

*********************************************************************/

#include "CCameraSceneNode.h"
#include "NetworkBase.h"
#include "PlayerManager.h"
#include "GameBag.h"

using namespace Network;



class IRobot : public irr::scene::CCameraSceneNode
{
public:

	enum RobotState
	{
		Fire,
		Idle
	};

	IRobot( IShip* ship, PlayerManager* mgr, NetworkBase* server );

	void Update();

	IShip* SearchTarget();

	RobotState		State;

	IShip*			RobotShip;
	PlayerManager*	Manager;
	NetworkBase*	Server;
};



