/********************************************************************
    创建时间: 2011-11-4   20:21
    文件名:   PlayerManager.h
    作者:     华亮 屠文翔
    说明:     其他玩家信息管理

*********************************************************************/

#ifndef PlayerManager_h__
#define PlayerManager_h__

#include "IPlayer.h"
#include <algorithm>
#include <list>
#include <boost/smart_ptr.hpp>


/*
** 名字：PlayerManager
** 说明：玩家管理类
**
*/
class PlayerManager
{
	typedef std::list< boost::shared_ptr<IPlayer> >		PlayerListType;

	PlayerListType		PlayerList;

public:
	// 接收引擎事件
	void OnEvent( const SEvent& event )
	{
		for ( PlayerListType::iterator iter = PlayerList.begin(); iter != PlayerList.end(); ++iter )
		{
			// 人类玩家才需要接收外部产生的消息
			if ( ! (*iter)->IsRobot() )
				(*iter)->OnEvent( event );
		}
	}

	// 添加玩家
	void AddPlayer( boost::shared_ptr<IPlayer> player )
	{
		PlayerList.push_back( player );
	}

	// 移除玩家
	void RemovePlayer( boost::shared_ptr<IPlayer> player )
	{
		PlayerList.remove( player );
	}

	// 移除所有玩家
	void RemoveAll()
	{
		PlayerList.clear();
	}


	void Update()
	{
		for ( PlayerListType::iterator iter = PlayerList.begin(); iter != PlayerList.end(); ++iter )
		{
			if ( (*iter)->IsRobot() )	// 机器人才需要更新
				(*iter)->Update();
		}
	}

	// 获取玩家列表
	const PlayerListType& GetPlayers() const
	{
		return PlayerList;
	}

	// 通过ID获取玩家
	bool GetPlayerByID( int id, boost::shared_ptr<IPlayer>& outPlayer ) 
	{
		PlayerListType::iterator iter = std::find_if( PlayerList.begin(), PlayerList.end(), 
			[ id ]( boost::shared_ptr<IPlayer> player )->bool
		{
			if ( player->GetID() == id )
				return true;
			return false;
		} );

		if ( iter != PlayerList.end() )
		{
			outPlayer = *iter;
			return true;
		}
		else
			return false;
	}

	// 通过名字获取玩家
	bool GetPlayerByName( const std::wstring& name, boost::shared_ptr<IPlayer>& outPlayer ) 
	{
		PlayerListType::iterator iter = std::find_if( PlayerList.begin(), PlayerList.end(), 
			[ name ]( boost::shared_ptr<IPlayer> player )->bool
		{
			if ( player->GetName() == name )
				return true;
			return false;
		} );

		if ( iter != PlayerList.end() )
		{
			outPlayer = *iter;
			return true;
		}
		else
			return false;
	}

private:

};

#endif // PlayerManager_h__