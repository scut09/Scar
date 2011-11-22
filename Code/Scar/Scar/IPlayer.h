/********************************************************************
    ����ʱ��: 2011-11-8   20:57
    �ļ���:   IPlayer.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     ��һ��࣬���������Ϊ������һ����ǵ�����

*********************************************************************/

#ifndef IPlayer_h__
#define IPlayer_h__

#include <string>
#include "IShip.h"
//#include <irrlicht.h>

/*
** ���֣�IPlayer
** ˵����base class of player, both human player and agent player
**
*/
class IPlayer /*: public irr::IReferenceCounted*/
{
public:
	enum Player_State
	{
		PS_Alive,			// ���
		PS_Dead				// ����
	};

protected:
	int				Money;			// ��Ǯ
	int				ID;				// ���ID
	std::wstring	Name;			// �������
	int				KillCount;		// ���ɱ����
	int				DeathCount;		// �����������
	s32				Team;			// ��Ҷ�����
	Player_State	State;			// ���״̬

	bool			Confirm;		// ȷ�ϱ�־λ��Ϊ�˽��һЩ��ʷ��������

	std::wstring	ShipName;		// ��ҷɻ�����
	IShip*			PlayerShip;		// ���ӵ�еķɻ�


public:
	IPlayer( IShip* playerShip ) : PlayerShip( playerShip )
	{
		if ( PlayerShip )
			PlayerShip->grab();

		Money = 0;
		ID = -1;
		Name = L"New Player";
		KillCount = 0;
		DeathCount = 0;
		Team = 0;
		State = PS_Alive;
	}

	virtual ~IPlayer()
	{
		if ( PlayerShip )	
			PlayerShip->drop();


	}

	// ����ȷ�ϱ�־λ
	virtual void SetConfirm( bool confirm )
	{
		Confirm = confirm;
	}
	virtual bool GetConfirm() const
	{
		return Confirm;
	}


	// ���÷ɴ�����
	virtual void SetShipName( const std::wstring& shipName )
	{
		ShipName = shipName;
	}
	virtual const std::wstring& GetShipName() const
	{
		return ShipName;
	}

	// ���ö���
	virtual void SetTeam( s32 team )
	{
		Team = team;
	}
	virtual s32 GetTeam()
	{
		return Team;
	}

	// �������״̬
	virtual void SetState( Player_State state )
	{
		State = state;
	}
	virtual Player_State GetState()
	{
		return State;
	}

	virtual void SetShip( IShip* ship )
	{
		if ( PlayerShip )
			PlayerShip->drop();

		PlayerShip = ship;
		if ( PlayerShip )
			PlayerShip->grab();
	}

	virtual IShip* GetShip() const
	{
		return PlayerShip;
	}

	// ���û�ɱ��
	virtual void SetKill( int kill )
	{
		KillCount = kill;
	}

	virtual int GetKill() const
	{
		return KillCount;
	}

	// ����������
	virtual void SetDeath( int death )
	{
		DeathCount = death;
	}

	virtual int GetDeath() const
	{
		return DeathCount;
	}

	// ������ҵ�ID
	virtual void SetID( int id )
	{
		ID = id;
	}

	virtual int GetID() const
	{
		return ID;
	}

	// ������ҵ�����
	virtual void SetName( const std::wstring& name )
	{
		Name = name;
	}

	virtual const std::wstring& GetName() const
	{
		return Name;
	}

	// ��Ӧ�¼�
	virtual void OnEvent( const SEvent& event )
	{
		PlayerShip->OnEvent( event );
	}

	// �Ƿ�Ϊ������
	virtual bool IsRobot() const
	{
		return false;
	}

	// ����
	virtual void Update() = 0;
};


#endif // IPlayer_h__