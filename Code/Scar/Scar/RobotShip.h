/********************************************************************
����ʱ��: 2011-11-7   14:09
�ļ���:   RobotShip.h
����:     ���� Cedric Porter [ Stupid ET ]	
˵��:     �ɴ�������

*********************************************************************/

#ifndef RobotShip_h__
#define RobotShip_h__

#include "IRobot.h"

class RobotShip : public IRobot
{
public:
	enum RobotState
	{
		Idle,		// ����״̬
		Track,		// ����״̬
		Attack		// ����״̬
	};

public:
	RobotShip( IShip* ship, PlayerManager* mgr, boost::shared_ptr<NetworkBase> server );

	virtual void Update();

private:
	RobotState		State;
	bool			fireOnce;


};
#endif // RobotShip_h__