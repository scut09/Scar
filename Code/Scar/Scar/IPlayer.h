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
	IPlayer( IShip* playerShip ) : PlayerShip( playerShip )
	{
		if ( PlayerShip )
			PlayerShip->grab();
	}

	virtual ~IPlayer()
	{
		if ( PlayerShip )	
			PlayerShip->drop();


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

protected:
	int				Money;			// ��Ǯ
	int				ID;				// ���ID
	std::wstring	Name;			// �������
	int				KillCount;		// ���ɱ����
	int				DeathCount;		// �����������

	IShip*			PlayerShip;		// ���ӵ�еķɻ�
};


#endif // IPlayer_h__