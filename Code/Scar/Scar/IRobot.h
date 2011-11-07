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


/*
** ���֣�
** ˵����ΪʲôҪ�̳�irr::scene::CCameraSceneNode���������ʷ�������⵼�£���Ϊ֮ǰ�ܶණ���Ǻ����������һ���
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



