#include "PlayerManager.h"
#include <iostream>
#include <string>


//////////////////////////////////////////////////////////////////////////
//
// Class PlayerManager
// 

void PlayerManager::RemovePlayer( boost::shared_ptr<IPlayer> player )
{
	PlayerList.remove( player );
}

void PlayerManager::RemoveAll()
{
	for ( auto iter = PlayerList.begin(); iter != PlayerList.end(); ++iter )
	{
		(*iter)->GetShip()->remove();
	}
	PlayerList.clear();
}

void PlayerManager::Update()
{
	for ( PlayerListType::iterator iter = PlayerList.begin(); iter != PlayerList.end(); ++iter )
	{
		if ( (*iter)->IsRobot() )	// 机器人才需要更新
			(*iter)->Update();
	}
}

bool PlayerManager::GetPlayerByID( int id, boost::shared_ptr<IPlayer>& outPlayer )
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

bool PlayerManager::GetPlayerByName( const std::wstring& name, boost::shared_ptr<IPlayer>& outPlayer )
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
