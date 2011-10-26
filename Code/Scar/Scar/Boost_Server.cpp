#include "Boost_Server.h"


void Network::BoostServer::Start( int listen_port, int target_port )
{
	// ��������
	m_network = std::shared_ptr<Network::CNetwork>( new Network::CNetwork( listen_port, target_port ) );
	// ע����ܻص�����
	m_network->Start( [this]( unsigned long ip, const PACKAGE& p )
	{
		OnReceive( ip, p );
	} );
}


void Network::BoostServer::OnReceive( unsigned long ip, const PACKAGE& p )
{
	using namespace boost::asio;

	int cmd = p.GetCMD();

	// ���󷿼�
	if ( cmd == QUERY_ROOM )
	{
		PACKAGE pack;

		pack.SetCMD( BROADCAST_ROOM );

		BroadcastRoomBag room;
		wchar_t* room_name = L"ETET";
		wcscpy( room.room_name, room_name );

		pack.SetData( (const char*)&room, sizeof( BroadcastRoomBag ) );

		m_network->Send( ip::address_v4().broadcast().to_ulong(), pack );

		std::cout << "BoostServer receives REQUEST_ROOM\n";
	}
	// �㲥����
	else if ( cmd == BROADCAST_ROOM )
	{
		std::cout << "BoostServer receives BROADCAST_ROOM\n";
		BroadcastRoomBag room;
		room = *(BroadcastRoomBag*)p.GetData();
		std::wcout << "Room Name: " << room.room_name << std::endl;
	}
	// Ӣ���ƶ�
	else if ( cmd == HERO_MOVE )
	{
		std::cout << "HERO_MOVE\n";
	}
}
