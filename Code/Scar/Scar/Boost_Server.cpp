#include "Boost_Server.h"


Network::BoostServer::BoostServer() : m_sock( io )
{
	socket_base::broadcast option( true );

	// Broadcast
	m_sock.open( boost::asio::ip::udp::v4() );
	m_sock.set_option( option );

	//
	m_broadcast_ep = udp::endpoint( address::from_string( "255.255.255.255" ), PORT );
}

void Network::BoostServer::Inti()
{

}

void Network::BoostServer::Broadcast( const PACKAGE& p )
{
	m_sock.send_to( buffer( &p, p.GetLength() ), m_broadcast_ep );
}

void Network::BoostServer::Run()
{
	udp::socket sock( io, udp::endpoint( udp::v4(), PORT ) );

	std::vector<char> buf( 1600 );

	while ( 1 )
	{
		udp::endpoint ep;
		//system::error_code ec;

		//sock.receive_from( buffer( buf ), ep, 0, ec );

		//if ( ec && ec != error::message_size )
		//{
		//	// error
		//}

		//ep.address();

		//boost::asio::socket_base::broadcast option(true);
		//socket.set_option(option);

		//std::string ip;
		//std::set<unsigned int> result;
		//getlocalip(result,ip,io_service);//得到主机ip地址

		//ipinfo->count=1;
		//ipinfo->iplist[0].ipaddr=ip;

		//udp::endpoint destination(boost::asio::ip::address::from_string("255.255.255.255"), PORT);

		//socket.send_to(boost::asio::buffer(ipinfo,(sizeof(_ipinfo)+sizeof(_ipinfo().iplist[0]))),destination);
	}
}
