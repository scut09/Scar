/********************************************************************
    创建时间: 2011-10-25   20:26
    文件名:   Client.cpp
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     客户端

*********************************************************************/

#include "Boost_Client.h"

Network::BoostClient::BoostClient( int port ) : m_port( port )
{
	// 创建网络
	m_network = std::shared_ptr<Network::CNetwork>( new Network::CNetwork( port, 12345 ) );
	// 注册接受回调函数
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
