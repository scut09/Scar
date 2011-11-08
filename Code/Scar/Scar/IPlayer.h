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
	IPlayer() : PlayerShip( NULL )
	{

	}

	virtual ~IPlayer()
	{
		if ( PlayerShip )	
			PlayerShip->drop();


	}

	void SetShip( IShip* ship )
	{
		if ( PlayerShip )
			PlayerShip->drop();

		PlayerShip = ship;
		if ( PlayerShip )
			PlayerShip->grab();
	}

	IShip* GetShip() const
	{
		return PlayerShip;
	}

	void SetKill( int kill )
	{
		KillCount = kill;
	}

	int GetKill() const
	{
		return KillCount;
	}

	void SetDeath( int death )
	{
		DeathCount = death;
	}

	int GetDeath() const
	{
		return DeathCount;
	}

	void SetID( int id )
	{
		ID = id;
	}

	int GetID() const
	{
		return ID;
	}

	void SetName( const std::wstring& name )
	{
		Name = name;
	}

	const std::wstring& GetName() const
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