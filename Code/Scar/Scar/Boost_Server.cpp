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
	PACKAGE pack;

	// ���󷿼�
	if ( cmd == QUERY_ROOM )
	{
		pack.SetCMD( BROADCAST_ROOM );

		BroadcastRoomBag room;
		wchar_t* room_name = L"TWX";
		wcscpy( room.room_name, room_name );

		pack.SetData( (const char*)&room, sizeof( BroadcastRoomBag ) );

		m_network->Broadcast( pack );

		std::cout << ip::address_v4( ip ).to_string() << " BoostServer receives REQUEST_ROOM\n";
	}
	// �㲥����
	else if ( cmd == BROADCAST_ROOM )
	{
		std::cout << "BoostServer receives BROADCAST_ROOM\n";
		BroadcastRoomBag room;
		room = *(BroadcastRoomBag*)p.GetData();
		std::wcout << "Room Name: " << room.room_name << std::endl;
	}
	// �������뷿��
	else if ( cmd == REQUEST_ENTER_ROOM )
	{
		if ( m_playerList.size() > 10 )	;

		int index = m_playerList.size();

		std::cout << ip::address_v4( ip ).to_string() << " ";
		std::cout << "==> BoostServer receives REQUEST_ENTER_ROOM\n"
			<< "allocate index " << index << std::endl;

		pack.SetCMD( ALLOW_JOIN_ROOM );
		AllowJoinRoomBag allowBag( index, 0, 0, 0 );
		pack.SetData( (char*)&allowBag, sizeof( AllowJoinRoomBag ) );

		m_network->Send( ip, pack );

		PlayerInfo player( index, ip );
		m_playerList.push_back( player );
	}
	else
	{
		// �������㲥
		m_network->Broadcast( p );

	}
}