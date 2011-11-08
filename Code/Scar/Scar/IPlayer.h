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

protected:
	int				Money;			// 金钱
	int				ID;				// 玩家ID
	std::wstring	Name;			// 玩家名称
	int				KillCount;		// 玩家杀敌数
	int				DeathCount;		// 玩家死亡次数

	IShip*			PlayerShip;		// 玩家拥有的飞机
};


#endif // IPlayer_h__