#include "Boost_Server.h"


void Network::BoostServer::Start( int listen_port, int target_port )
{
	// 创建网络
	m_network = std::shared_ptr<Network::CNetwork>( new Network::CNetwork( listen_port, target_port ) );
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
	PACKAGE pack;

	// 请求房间
	if ( cmd == QUERY_ROOM )
	{
		pack.SetCMD( BROADCAST_ROOM );

		BroadcastRoomBag room;
		wchar_t* room_name = L"XiGe";
		wcscpy( room.room_name, room_name );

		pack.SetData( (const char*)&room, sizeof( BroadcastRoomBag ) );

		m_network->Send( ip::address_v4().broadcast().to_ulong(), pack );

		

		std::cout << ip::address_v4( ip ).to_string() << " BoostServer receives REQUEST_ROOM\n";
	}
	// 广播房间
	else if ( cmd == BROADCAST_ROOM )
	{
		std::cout << "BoostServer receives BROADCAST_ROOM\n";
		BroadcastRoomBag room;
		room = *(BroadcastRoomBag*)p.GetData();
		std::wcout << "Room Name: " << room.room_name << std::endl;
	}
	// 英雄移动
	else if ( cmd == HERO_MOVE )
	{
		std::cout << "HERO_MOVE\n";
		HeroMove move;
		move = *(HeroMove*)p.GetData();
		std::cout << move.index << ' ' << move.x << ' ' << move.y << ' ' << move.z << std::endl;
	}
	else if ( cmd == REQUEST_ENTER_ROOM )
	{
		std::cout << ip::address_v4( ip ).to_string() << " ";
		std::cout << "BoostServer receives REQUEST_ENTER_ROOM\n";
		pack.SetCMD( ALLOW_JOIN_ROOM );
		m_network->Send( ip, pack );
	}
}
