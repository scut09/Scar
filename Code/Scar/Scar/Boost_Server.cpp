#include "Boost_Server.h"
#include "GameBag.h"

Network::BoostServer::BoostServer()
{
	RegisterMessageHandler( QUERY_ROOM, 
		[this]( unsigned long ip, const PACKAGE& p ){ QueryRoomHandler( ip, p ); });
	RegisterMessageHandler( REQUEST_ENTER_ROOM, 
		[this]( unsigned long ip, const PACKAGE& p ){ RequestEnterRoomHandler( ip, p ); });
}

void Network::BoostServer::QueryRoomHandler( unsigned long ip, const PACKAGE& p )
{
	PACKAGE pack;

	pack.SetCMD( BROADCAST_ROOM );

	BroadcastRoomBag room;
	wchar_t* room_name = L"TWX";
	wcscpy( room.room_name, room_name );

	pack.SetData( (const char*)&room, sizeof( BroadcastRoomBag ) );

	m_network->Broadcast( pack );

	std::cout << ip::address_v4( ip ).to_string() << " BoostServer receives REQUEST_ROOM\n";
}

void Network::BoostServer::RequestEnterRoomHandler( unsigned long ip, const PACKAGE& p )
{
	if ( m_playerList.size() > 10 )	
	{
		// ʧ��
	}

	// Ϊ����ҷ���id
	int index = m_playerList.size();

	std::cout << ip::address_v4( ip ).to_string() << " ";
	std::cout << "==> BoostServer receives REQUEST_ENTER_ROOM\n"
		<< "allocate index " << index << std::endl;

	PACKAGE pack;

	// �������������Ϣ
	pack.SetCMD( ALLOW_JOIN_ROOM );
	AllowJoinRoomBag allowBag( index, 0, 0, 0 );
	pack.SetData( (char*)&allowBag, sizeof( AllowJoinRoomBag ) );

	m_network->Send( ip, pack );

	// ������������Ϣ
	PlayerInfo player( index, ip );
	m_playerList.push_back( player );

	Sleep( 2000 );

	// �������������Ϣ������ң������Ҫ�Ľ�
	for ( auto iter = m_playerList.begin(); iter != m_playerList.end(); ++iter )
	{
		OnePlayerInfoBag oneplayer;
		oneplayer.player_index = iter->index;

		pack.SetCMD( NEW_PLAYER_JOIN );
		pack.SetData( (char*)&oneplayer, sizeof( OnePlayerInfoBag ) );

		m_network->Send( ip, pack );
	}

	Sleep( 2000 );

	OnePlayerInfoBag oneplayer;
	oneplayer.player_index = index;

	pack.SetCMD( NEW_PLAYER_JOIN );
	pack.SetData( (char*)&oneplayer, sizeof( OnePlayerInfoBag ) );

	m_network->Broadcast( pack );
}

void Network::BoostServer::OtherMessageHandler( unsigned long ip, const PACKAGE& p )
{
	// ���������͸����
	for ( auto iter = m_playerList.begin(); iter != m_playerList.end(); ++iter )
	{
		m_network->Send( iter->ip, p );
	}
	//m_network->Broadcast( p );
}
