/********************************************************************
    ����ʱ��: 2011-10-25   20:25
    �ļ���:   Server.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     �����

*********************************************************************/

#ifndef Boost_Server_h__
#define Boost_Server_h__

#include "CNetwork.h"
#include "NetworkBase.h"
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

namespace Network
{
	// ������
	class BoostServer : public NetworkBase
	{
	public:
		BoostServer();

		// ��Ϣ������
		virtual void OtherMessageHandler( unsigned long ip, const PACKAGE& p );
		void QueryRoomHandler( unsigned long ip, const PACKAGE& p );
		void RequestEnterRoomHandler( unsigned long ip, const PACKAGE& p );

	private:
		std::list<PlayerInfo>					m_playerList;	// ����б�
		std::set<std::string>					m_localIP;		// ����IP
	};


}

#endif // Boost_Server_h__
