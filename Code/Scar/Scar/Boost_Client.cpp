/********************************************************************
    ����ʱ��: 2011-10-25   20:26
    �ļ���:   Client.cpp
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     �ͻ���

*********************************************************************/

#include "Boost_Client.h"

Network::BoostClient::BoostClient( int port ) : m_port( port )
{
	// ��������
	m_network = std::shared_ptr<Network::CNetwork>( new Network::CNetwork( port, 12345 ) );
	// ע����ܻص�����
	m_network->Start( [this]( unsigned long ip, const PACKAGE& p )
	{
		OnReceive( ip, p );
	} );
}

void Network::BoostClient::OnReceive( unsigned long ip, const PACKAGE& p )
{

}

void Network::BoostClient::Send( std::string ip )
{
	PACKAGE p;
	p.SetCMD( REQUEST_ROOM );
	m_network->Send( ip, m_port, p );
}
