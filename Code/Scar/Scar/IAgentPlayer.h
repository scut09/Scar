/********************************************************************
    ����ʱ��: 2011-11-9   1:05
    �ļ���:   AgentPlayer.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     ������ң�Ҳ���ǵ�����

*********************************************************************/

#ifndef AgentPlayer_h__
#define AgentPlayer_h__

#include "IPlayer.h"
#include "PlayerManager.h"
#include "NetworkBase.h"

/*
** ���֣�AgentPlayer
** ˵����Computer controls this player, just like agent in a film
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
	virtual bool SearchTarget( boost::shared_ptr<IPlayer>& outPlayer, int range = 3500 );

protected:

	PlayerManager*					Manager;		// ��ҷɴ�������
	boost::shared_ptr<Network::NetworkBase>	Server;			// �����
};


#endif // AgentPlayer_h__