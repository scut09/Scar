/********************************************************************
    ����ʱ��: 2011-10-25   20:26
    �ļ���:   Client.cpp
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     �ͻ���

*********************************************************************/

#include "Boost_Client.h"


void Network::BoostClient::OnReceive( unsigned long ip, const PACKAGE& p )
{
	int cmd = p.GetCMD();

	std::cout << "BoostClient cmd = " << cmd << std::endl;

	if ( cmd == BROADCAST_ROOM )		// �յ�����㲥�����浽�����б���
	{
		BroadcastRoomBag bag = *(BroadcastRoomBag*)p.GetData();
		m_roomMap[ boost::asio::ip::address_v4( ip ).to_string() ] = bag;

		std::cout << "Server broadcast room: ip= " 
			<< boost::asio::ip::address_v4( ip ).to_string() 
			<< " room name= ";
		std::wcout << ((BroadcastRoomBag*)p.GetData())->room_name
			<< std::endl;

		std::cout << "<current rooms>\n";
		for ( auto iter = m_roomMap.begin(); iter != m_roomMap.end(); ++iter )
		{
			std::cout << "ip " << iter->first << std::endl;
		}
		std::cout << "</current rooms>\n";
	}
	else if ( cmd == ALLOW_JOIN_ROOM )	// �յ�������뷿�����Ϣ����ʼ��Ϸ
	{
		std::cout << boost::asio::ip::address_v4( ip ).to_string() << " ==>BoostClient receives ALLOW_JOIN_ROOM\n";

		m_server_IP = ip;

		PlayerInfo player;
		player = *(PlayerInfo*)p.GetData();

		m_index = player.index;


	}
	else if ( cmd == HERO_MOVE )
	{
		HeroMove move;
		move = *(HeroMove*)p.GetData();
		if ( move.index != m_index )
		{
			std::cout << "=> HERO_MOVE " << move.index << ' ' << move.x << ' ' << move.y << ' ' << move.z << std::endl;
		}
	}
}

void Network::BoostClient::Send( std::string ip )
{
	PACKAGE p;
	p.SetCMD( ALLOW_JOIN_ROOM );
	//m_network->Send( ip, p );
}

void Network::BoostClient::Start( int listen_port, int target_port )
{
	// ��������
	m_network = std::shared_ptr<Network::CNetwork>( new Network::CNetwork( listen_port, target_port ) );
	// ע����ܻص�����
	m_network->Start( [this]( unsigned long ip, const PACKAGE& p )
	{
		OnReceive( ip, p );
	} );
}

void Network::BoostClient::QueryRoom()
{
	PACKAGE p;
	p.SetCMD( QUERY_ROOM );
	m_network->Broadcast( p );
}

void Network::BoostClient::EnterRoom( const std::string& ip )
{
	PACKAGE pack;
	pack.SetCMD( REQUEST_ENTER_ROOM );
	m_network->Send( ip, pack );
}

void Network::BoostClient::SendHeroMove( int index, float x, float y, float z )
{
	PACKAGE pack;
	pack.SetCMD( HERO_MOVE );

	HeroMove move( index, x, y, z );

	pack.SetData( (char*)&move, sizeof( HeroMove ) );

	m_network->Send( m_server_IP, pack );
}
