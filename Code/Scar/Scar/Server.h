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

	// ·þÎñÆ÷
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
				system::error_code ec;
				
				sock.receive_from( buffer( buf ), ep, 0, ec );

				if ( ec && ec != error::message_size )
				{
					// error
				}

				ep.address();

				sock.sen
			}
		}

	private:
		io_service		io;

	};


}



#endif // Server_h__
