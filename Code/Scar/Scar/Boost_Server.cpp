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
		// 失败
	}

	// 为新玩家分配id
	int index = m_playerList.size();

	std::cout << ip::address_v4( ip ).to_string() << " ";
	std::cout << "==> BoostServer receives REQUEST_ENTER_ROOM\n"
		<< "allocate index " << index << std::endl;

	PACKAGE pack;

	// 发送允许加入消息
	pack.SetCMD( ALLOW_JOIN_ROOM );
	AllowJoinRoomBag allowBag( index, 0, 0, 0 );
	pack.SetData( (char*)&allowBag, sizeof( AllowJoinRoomBag ) );

	//m_network->SendTo( ip, pack );
	TcpSendTo( ip, m_target_port, pack );

	// 保存这个玩家信息
	PlayerInfo player( index, ip );
	m_playerList.push_back( player );

	//Sleep( 2000 );

	// 发送已有玩家信息给新玩家，这个需要改进
	for ( auto iter = m_playerList.begin(); iter != m_playerList.end(); ++iter )
	{
		OnePlayerInfoBag oneplayer;
		oneplayer.player_index = iter->index;

		pack.SetCMD( NEW_PLAYER_JOIN );
		pack.SetData( (char*)&oneplayer, sizeof( OnePlayerInfoBag ) );

		//m_network->SendTo( ip, pack );
		TcpSendTo( ip, m_target_port, pack );
	}

	//Sleep( 2000 );

	OnePlayerInfoBag oneplayer;
	oneplayer.player_index = index;

	pack.SetCMD( NEW_PLAYER_JOIN );
	pack.SetData( (char*)&oneplayer, sizeof( OnePlayerInfoBag ) );

	//m_network->Broadcast( pack );
	TcpSendToPlayers( pack );
}

void Network::BoostServer::OtherMessageHandler( unsigned long ip, const PACKAGE& p )
{
	// 其他，发送给玩家
	UdpSendToPlayers( p );
}

void Network::BoostServer::TcpSendToPlayers( const PACKAGE& p )
{
	for ( auto iter = m_playerList.begin(); iter != m_playerList.end(); ++iter )
	{
		TcpSendTo( iter->ip, m_target_port, p );
	}
}

void Network::BoostServer::UdpSendToPlayers( const PACKAGE& p )
{
	for ( auto iter = m_playerList.begin(); iter != m_playerList.end(); ++iter )
	{
		m_network->SendTo( iter->ip, p );
	}
}

void Network::BoostServer::Start( int listen_port, int target_port )
{
	m_target_port = target_port;

	NetworkBase::Start( listen_port, target_port );
}
