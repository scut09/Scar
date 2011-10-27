#include "Boost_Server.h"
#include "GameBag.h"


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

	//std::cout << "BoostClient cmd = " << cmd << std::endl;

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
	// ������뷿��
	else if ( cmd == REQUEST_ENTER_ROOM )
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
	else
	{
		// ���������͸����
		for ( auto iter = m_playerList.begin(); iter != m_playerList.end(); ++iter )
		{
			m_network->Send( iter->ip, p );
		}
		//m_network->Broadcast( p );

	}
}
