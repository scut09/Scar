#ifndef Server_h__
#define Server_h__

#include "NetworkPacket.h"
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <vector>

namespace Network
{
	using namespace boost::asio;
	using namespace boost::thread;

	// 服务器
	class Server
	{
	public:
		Server()
		{

		}

		void Inti()
		{

		}

		void Run()
		{

			ip::udp::socket sock( io, ip::udp::endpoint( ip::udp::v4(), 12345 ) );

			std::vector<char> buf( 1600 );

			while ( 1 )
			{
				ip::udp::endpoint ep;
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

	private:
		io_service		io;

	};


}



#endif // Server_h__
