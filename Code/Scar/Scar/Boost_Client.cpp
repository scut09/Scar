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

	if ( cmd == BROADCAST_ROOM )		// �յ�����㲥�����浽�����б���
	{
		BroadcastRoomBag bag = *(BroadcastRoomBag*)p.GetData();
		m_roomMap[ boost::asio::ip::address_v4( ip ).to_string() ] = bag;

		std::cout << "Server broadcast room: ip= " 
			<< boost::asio::ip::address_v4( ip ).to_string() 
			<< " room name= ";
		std::wcout << ((BroadcastRoomBag*)p.GetData())->room_name
			<< std::endl;
	}
	else if ( cmd == ALLOW_JOIN_ROOM )	// �յ�������뷿�����Ϣ����ʼ��Ϸ
	{
		std::cout << "BoostClient receives ALLOW_JOIN_ROOM\n";
		m_server_IP = ip;
	}
}

void Network::BoostClient::Send( std::string ip )
{
	//PACKAGE p;
	//p.SetCMD( REQUEST_ROOM );
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
	m_network->Send( 0, p );
}

void Network::BoostClient::EnterRoom( const std::string& ip )
{
	PACKAGE pack;
	pack.SetCMD( REQUEST_ENTER_ROOM );
	m_network->Send( 0, pack );
}

void Network::BoostClient::SendHeroMove( int index, float x, float y, float z )
{
	PACKAGE pack;
	pack.SetCMD( HERO_MOVE );

	HeroMove move( index, x, y, z );

	pack.SetData( (char*)&move, sizeof( HeroMove ) );

	m_network->Send( m_server_IP, pack );
}
