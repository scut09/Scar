/********************************************************************
    ����ʱ��: 2011-11-6   22:38
    �ļ���:   IRobot.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     AI������

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



