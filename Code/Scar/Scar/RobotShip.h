/********************************************************************
����ʱ��: 2011-11-7   14:09
�ļ���:   RobotShip.h
����:     ���� Cedric Porter [ Stupid ET ]	
˵��:     �ɴ�������

*********************************************************************/

#ifndef RobotShip_h__
#define RobotShip_h__

#include "IAgentPlayer.h"

class ShipAgentPlayer : public IAgentPlayer
{
public:
	enum RobotState
	{
		Idle,		// ����״̬
		Track,		// ����״̬
		Attack		// ����״̬
	};

public:
	ShipAgentPlayer( IShip* ship, PlayerManager* mgr, boost::shared_ptr<Network::NetworkBase> server );

	virtual void Update();

private:
	RobotState		State;
	bool			fireOnce;


};
#endif // RobotShip_h__