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
	void RemovePlayer( boost::shared_ptr<IPlayer> player );

	// �Ƴ��������
	void RemoveAll();


	void Update();

	// ��ȡ����б�
	const PlayerListType& GetPlayers() const
	{
		return PlayerList;
	}

	// ͨ��ID��ȡ���
	bool GetPlayerByID( int id, boost::shared_ptr<IPlayer>& outPlayer );

	// ͨ�����ֻ�ȡ���
	bool GetPlayerByName( const std::wstring& name, boost::shared_ptr<IPlayer>& outPlayer );

private:

};

#endif // PlayerManager_h__