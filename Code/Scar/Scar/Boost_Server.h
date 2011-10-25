/********************************************************************
    ����ʱ��: 2011-10-25   20:25
    �ļ���:   Server.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     �����

*********************************************************************/

#ifndef Server_h__
#define Server_h__

#include "NetworkPacket.h"
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <vector>
#include <string>

namespace Network
{
	using namespace boost;
	using namespace boost::asio;
	using namespace boost::asio::ip;

	const int PORT = 1234;

	// ������
	class BoostServer
	{
		io_service	io;
		udp::socket m_sock;

	public:
		BoostServer();

		void Inti();

		void Broadcast( const PACKAGE& p );

		void Run();

		void OnReceive( const PACKAGE& p )
		{
			if ( p.GetCMD() == REQUEST_ROOM )
			{
				PACKAGE pack;

				pack.SetCMD( BROADCAST_ROOM );

				BroadcastRoomBag room;
				wchar_t* room_name = L"ETET";
				wcscpy( room.room_name, room_name );

				Broadcast( pack );
			}
		}

	private:

		udp::endpoint	m_broadcast_ep;

	};


}



#endif // Server_h__
