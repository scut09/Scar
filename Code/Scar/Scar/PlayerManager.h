/********************************************************************
    ����ʱ��: 2011-11-4   20:21
    �ļ���:   PlayerManager.h
    ����:     ���� ������
    ˵��:     ���������Ϣ����

*********************************************************************/

#ifndef PlayerManager_h__
#define PlayerManager_h__

#include "IPlayer.h"
#include <algorithm>
#include <list>
#include <boost/smart_ptr.hpp>


/*
** ���֣�PlayerManager
** ˵������ҹ�����
**
*/
class PlayerManager
{
	typedef std::list< boost::shared_ptr<IPlayer> >		PlayerListType;

	PlayerListType		PlayerList;

public:
	// ���������¼�
	void OnEvent( const SEvent& event )
	{
		for ( PlayerListType::iterator iter = PlayerList.begin(); iter != PlayerList.end(); ++iter )
		{
			// ������Ҳ���Ҫ�����ⲿ��������Ϣ
			if ( ! (*iter)->IsRobot() )
				(*iter)->OnEvent( event );
		}
	}

	// ������
	void AddPlayer( boost::shared_ptr<IPlayer> player )
	{
		PlayerList.push_back( player );
	}

	// �Ƴ����
	void RemovePlayer( boost::shared_ptr<IPlayer> player )
	{
		PlayerList.remove( player );
	}

	// �Ƴ��������
	void RemoveAll()
	{
		PlayerList.clear();
	}


	void Update()
	{
		for ( PlayerListType::iterator iter = PlayerList.begin(); iter != PlayerList.end(); ++iter )
		{
			if ( (*iter)->IsRobot() )	// �����˲���Ҫ����
				(*iter)->Update();
		}
	}

	// ��ȡ����б�
	const PlayerListType& GetPlayers() const
	{
		return PlayerList;
	}

	// ͨ��ID��ȡ���
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

	// ͨ�����ֻ�ȡ���
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