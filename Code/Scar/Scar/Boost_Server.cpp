#include "Boost_Server.h"


Network::BoostServer::BoostServer( int port ) : m_port( port )
{
	// 创建网络
	m_network = std::shared_ptr<Network::CNetwork>( new Network::CNetwork( port, port ) );
	// 注册接受回调函数
	m_network->Start( [this]( unsigned long ip, const PACKAGE& p )
	{
		OnReceive( ip, p );
	} );
}

void Network::BoostServer::OnReceive( unsigned long ip, const PACKAGE& p )
{
	using namespace boost::asio;

	int cmd = p.GetCMD();

	// 请求房间
	if ( cmd == REQUEST_ROOM )
	{
		PACKAGE pack;

		pack.SetCMD( BROADCAST_ROOM );

		BroadcastRoomBag room;
		wchar_t* room_name = L"ETET";
		wcscpy( room.room_name, room_name );

		pack.SetData( (const char*)&room, sizeof( BroadcastRoomBag ) );

		m_network->Send( ip::address_v4().broadcast().to_ulong(), m_port, pack );

		std::cout << "REQUEST_ROOM\n";
	}
	// 广播房间
	else if ( cmd == BROADCAST_ROOM )
	{
		std::cout << "BROADCAST_ROOM\n";
		BroadcastRoomBag room;
		room = *(BroadcastRoomBag*)p.GetData();
		std::wcout << "Room Name: " << room.room_name << std::endl;
	}
	// 英雄移动
	else if ( cmd == HERO_MOVE )
	{
		std::cout << "HERO_MOVE\n";
	}
}
