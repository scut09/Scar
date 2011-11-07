/********************************************************************
    ����ʱ��: 2011-11-6   22:38
    �ļ���:   IRobot.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     AI������

*********************************************************************/
#ifndef IRobot_h__
#define IRobot_h__


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
	//************************************
	// ����ֵ:  
	// ����:    IShip * ship								�Լ����ƵĴ�
	// ����:    PlayerManager * mgr						�������������Ϣ����ҹ�����
	// ����:    std::shared_ptr<NetworkBase> server		�����ָ��
	// ������   ctor
	//************************************
	IRobot( IShip* ship, PlayerManager* mgr, std::shared_ptr<NetworkBase> server );

	// �����Լ�
	virtual void Update() = 0;

protected:
	// �����Լ����ƶ���Ϣ
	void SendMove( const vector3df& pos );
	// �����Լ�����ת��Ϣ
	void SendRotate( const core::vector3df& rot );

	// ģ���������
	void DoLeftButtonDown();
	// ģ���������
	void DoLeftButtonUp();
	// ģ�ⰴ�¼���
	void DoPress( EKEY_CODE key )
	{
		SEvent ev;
		ev.EventType = EET_KEY_INPUT_EVENT;
		ev.KeyInput.Key = key;
		ev.KeyInput.PressedDown = true;

		OnEvent( ev );
	}
	// ģ�ⵯ�����
	void DoUnpress( EKEY_CODE key )
	{
		SEvent ev;
		ev.EventType = EET_KEY_INPUT_EVENT;
		ev.KeyInput.Key = key;
		ev.KeyInput.PressedDown = false;

		OnEvent( ev );
	}
	

	// ����Ŀ��
	virtual IShip* SearchTarget( int range = 3500 );

protected:

	IShip*							RobotShip_;		// �Լ����ƵĴ�
	PlayerManager*					Manager;		// ��ҷɴ�������
	std::shared_ptr<NetworkBase>	Server;			// �����
};



#endif // IRobot_h__
