/********************************************************************
    创建时间: 2011-11-8   20:57
    文件名:   IPlayer.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     玩家基类，派生类可以为真正玩家或者是电脑人

*********************************************************************/

#ifndef IPlayer_h__
#define IPlayer_h__

#include <string>
#include "IShip.h"
//#include <irrlicht.h>

/*
** 名字：IPlayer
** 说明：base class of player, both human player and agent player
**
*/
class IPlayer /*: public irr::IReferenceCounted*/
{
public:
	enum Player_State
	{
		PS_Alive,			// 存活
		PS_Dead				// 死亡
	};

protected:
	int				Money;			// 金钱
	int				ID;				// 玩家ID
	std::wstring	Name;			// 玩家名称
	int				KillCount;		// 玩家杀敌数
	int				DeathCount;		// 玩家死亡次数
	s32				Team;			// 玩家队伍编号
	Player_State	State;			// 玩家状态

	bool			Confirm;		// 确认标志位，为了解决一些历史遗留问题

	std::wstring	ShipName;		// 玩家飞机代号
	IShip*			PlayerShip;		// 玩家拥有的飞机


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

	// 设置确认标志位
	virtual void SetConfirm( bool confirm )
	{
		Confirm = confirm;
	}
	virtual bool GetConfirm() const
	{
		return Confirm;
	}


	// 设置飞船代号
	virtual void SetShipName( const std::wstring& shipName )
	{
		ShipName = shipName;
	}
	virtual const std::wstring& GetShipName() const
	{
		return ShipName;
	}

	// 设置队伍
	virtual void SetTeam( s32 team )
	{
		Team = team;
	}
	virtual s32 GetTeam()
	{
		return Team;
	}

	// 设置玩家状态
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

	// 设置击杀数
	virtual void SetKill( int kill )
	{
		KillCount = kill;
	}

	virtual int GetKill() const
	{
		return KillCount;
	}

	// 设置死亡数
	virtual void SetDeath( int death )
	{
		DeathCount = death;
	}

	virtual int GetDeath() const
	{
		return DeathCount;
	}

	// 设置玩家的ID
	virtual void SetID( int id )
	{
		ID = id;
	}

	virtual int GetID() const
	{
		return ID;
	}

	// 设置玩家的名称
	virtual void SetName( const std::wstring& name )
	{
		Name = name;
	}

	virtual const std::wstring& GetName() const
	{
		return Name;
	}

	// 响应事件
	virtual void OnEvent( const SEvent& event )
	{
		PlayerShip->OnEvent( event );
	}

	// 是否为机器人
	virtual bool IsRobot() const
	{
		return false;
	}

	// 更新
	virtual void Update() = 0;
};


#endif // IPlayer_h__