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


/*
** 名字：
** 说明：为什么要继承irr::scene::CCameraSceneNode，这个是历史遗留问题导致，因为之前很多东西是和摄像机绑定在一起的
**
*/
class IRobot : public irr::scene::CCameraSceneNode
{
public:

	enum RobotState
	{
		Fire,
		Idle
	};

	IRobot( IShip* ship, PlayerManager* mgr, std::shared_ptr<NetworkBase> server );

	void Update();

	void SendMove( const vector3df& pos );

	void SendRotate( const core::vector3df& rot );

	void DoLeftButtonDown();

	void DoLeftButtonUp();

	IShip* SearchTarget();

	RobotState		State;

	IShip*			RobotShip;
	PlayerManager*	Manager;
	std::shared_ptr<NetworkBase>	Server;
};



