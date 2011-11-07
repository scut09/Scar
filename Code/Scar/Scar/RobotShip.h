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
		Fire,
		Idle
	};

public:
	RobotShip( IShip* ship, PlayerManager* mgr, std::shared_ptr<NetworkBase> server )
		: IRobot( ship, mgr, server )
	{
		State = Idle;
	}

	virtual void Update()
	{
		SendMove( getPosition() );

		u32 time = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
		this->OnAnimate( time );

		PACKAGE p;

		static bool fireOnce = true;

		switch ( State )
		{
			// ����״̬
		case Idle:			
			if ( IShip* ship = SearchTarget() )
			{
				State = Fire;

				setTarget( ship->getPosition() );

				SendRotate( getRotation() );
			}
			// ����״̬
		case Fire:
			if ( IShip* ship = SearchTarget() )
			{
				if ( fireOnce )
				{
					fireOnce = false;

					DoLeftButtonDown();	// ���¿��𰴼�
				}
			}
			else
			{
				State = Idle;
				fireOnce = true;

				DoLeftButtonUp();		// �ɿ����𰴼�
			}
		}
	}

private:
	RobotState		State;

};
#endif // RobotShip_h__