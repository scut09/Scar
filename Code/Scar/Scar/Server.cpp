/********************************************************************
����ʱ��: 2011-10-22   15:00
�ļ���:   Server.cpp
����:     �´���
˵��:     ����������ʵ��

*********************************************************************/


#include <string>
#include <sstream>
#include "Server.h"

using namespace Network;

Server::Server(void)
{
}


Server::~Server(void)
{
	closesocket(m_socket);
	closesocket(m_broadcastSocket);
}

#pragma region ��̬���ݶ��弰��ʼ��

SOCKET Server::m_socket;
SOCKET Server::m_broadcastSocket;
SOCKADDR_IN Server::m_targetAddr;
SOCKADDR_IN Server::m_broadcastAddr;
bool Server::m_isCreate = false;
bool Server::m_isStart = false;
bool Server::m_userListChange = false;
wchar_t* Server::m_serverIP = NULL;
unsigned short Server::m_serverPort (54321);
unsigned short Server::m_clientPort (55555);
const int Server::m_bufferLength(0X4000);
const int Server::m_tolen(sizeof(SOCKADDR));
wstring Server::m_Scene = L"";
wstring Server::m_gameRoomName = L"";
int Server::m_maxPlayerNumber = 0;
int Server::m_nowPlayerNumber = 0;
vector<clientInfo> Server::m_clientList;

#pragma endregion ��̬���ݶ��弰��ʼ��

//************************************
// ������:  Network::Server::SetServerPort
// ����:    unsigned short port	�˿ں�
// ����ֵ:  void
// ��������:public
// ������   ���÷����������Ķ˿ں�
//************************************
void Server::SetServerPort(unsigned short port)
{
	m_serverPort = port;
}
		
//************************************
// ������:  Network::Server::SetClientPort
// ����:    unsigned short port	�˿ں�
// ����ֵ:  void
// ��������:public
// ������   ���ÿͻ��˼����Ķ˿ں�
//************************************
void Server::SetClientPort(unsigned short port)
{
	m_clientPort = port;
}

////************************************
//// ������:  GetIp
//// ����ֵ:  wchar_t*
//// ��������:protected static 
//// ������   ���ڻ�ȡ����IP��ַ
////************************************
//wchar_t* Server::GetIp(void)
//{
//	WSADATA wsaData;
//	wchar_t name[255]; //�������ڴ�Ż�õ��������ı��� 
//	wchar_t *ip; //����IP��ַ���� 
//	PHOSTENT hostinfo; 
//
//	//����MAKEWORD�������Winsock�汾����ȷֵ�����ڼ���Winsock�� 
//	if ( WSAStartup( MAKEWORD(2,0), &wsaData ) == 0 )
//	{ 
//		//�����Ǽ���Winsock�⣬���WSAStartup������������ֵΪ0��˵�����سɹ���������Լ��� 
//		if( gethostname ( name, sizeof(name)) == 0)
//		{ 
//			//����ɹ��ؽ������������������name����ָ���Ļ������� 
//			if((hostinfo = gethostbyname(name)) != NULL)
//			{ 
//				//���ǻ�ȡ���������������������ɹ��Ļ���������һ��ָ�룬ָ��hostinfo��hostinfo
//				//ΪPHOSTENT�͵ı��������漴���õ�����ṹ�� 
//				ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list); 
//				//����inet_ntoa������������hostinfo�ṹ�����е�h_addr_listת��Ϊ��׼�ĵ�ֱ�ʾ��IP
//			} 
//		} 
//		WSACleanup( ); //ж��Winsock�⣬���ͷ�������Դ 
//	}
//	return ip;
//} 

//************************************
// ������:  Network::Server::SendMsg
// ����1:   const wchar_t* dwIP		�Է�IP
// ����2:   wchar_t* buf		��������
// ����ֵ:  ErrorCode
// ��������:protected static
// ������   ������Ϣ
//************************************
ErrorCode Server::SendMsg(const char* dwIP, const wchar_t* buf)
{
	m_targetAddr.sin_family = AF_INET;
	m_targetAddr.sin_port = htons(m_clientPort);
	m_targetAddr.sin_addr.S_un.S_addr = inet_addr(dwIP);

	int nSendSize = sendto(m_socket, (char*)buf, sizeof(wchar_t)*(wcslen(buf)+1), 0, (SOCKADDR *) &m_targetAddr, m_tolen);

	if (nSendSize == -1)
	{
		return ErrorCode::��Ϣ����ʧ��;
	}

	return ErrorCode::ACCEPT;
}

//************************************
// ������:  Network::Server::Broadcast
// ����:    const wchar_t* msg		Ҫ���͵���Ϣ
// ����ֵ:  ErrorCode
// ��������:public static
// ������   �㲥��Ϣ
//************************************
ErrorCode Server::Broadcast(const wchar_t* msg)
{
	int nSendSize = sendto(m_broadcastSocket, (char*)msg, sizeof(wchar_t)*(wcslen(msg)+1), 0, (SOCKADDR*)&m_broadcastAddr, m_tolen);

	if (nSendSize == -1)
	{
		return ErrorCode::��Ϣ����ʧ��;
	}

	return ErrorCode::ACCEPT;
}

//************************************
// ������:  Network::Server::ListenThread
// ����:    void* pArguments	NULL
// ����ֵ:  unsigned
// ��������:protected WINAPI
// ������   �����߳�
//************************************
unsigned WINAPI Server::ListenThread(void* pArguments)
{
	char *addr = new char[16];
	int port;
	wchar_t *buffer = new wchar_t[m_bufferLength];
	struct sockaddr_in from;
	int fromlen = sizeof(from);
	int size;
	
	while (m_isCreate)
	{
		size = recvfrom(m_socket, (char*)buffer, m_bufferLength, 0, (SOCKADDR *)&from, &fromlen);
		if (size > 0)
		{
			memset(addr,0,16);

			addr = inet_ntoa(from.sin_addr);
			
			port = ntohl(from.sin_addr.s_addr);

			// ������յ�����Ϣ
			RecvData(addr, port, buffer, size);
		}
		Sleep(1);
	}

	delete []addr;
	delete []buffer;
	return 0;
}


//************************************
// ������:  Network::Server::UserListToString
// ����:    void
// ����ֵ:  wstring			��ʽ������û��б�
// ��������:protected static
// ������   ��userlistתΪwstring
//************************************
wstring Server::UserListToString(void)
{
	wstring strList= L"userlist:{";
	for (vector<Network::clientInfo>::iterator iter = m_clientList.begin(); iter != m_clientList.end(); iter++)
	{
		strList.append(iter->userID + L":" + iter->dwIP + L";");
	}
	if (strList[strList.length() - 1] == L';')
	{
		strList[strList.length() - 1] = L'}';
	}
	else
	{
		strList.append(L"}");
	}
	return strList;
}

//************************************
// ������:  Network::Server::RecvData
// ����:    wchar_t *addr		��ַ
// ����:    int port		�˿ں�
// ����:    wchar_t *buf		��Ϣ
// ����:    int size		��С
// ����ֵ:  void
// ��������:protected static
// ������   ������յ�����Ϣ
//************************************
void Server::RecvData(char *addr, int port, wchar_t *buf, int size)
{
	//printf("�յ�%s\t%d\t%d\t%s\n", addr, port, size, buf);

	wstring data = buf;
	int pos = data.find_first_of(L"?");
	if (pos == -1)
	{
		return;
	}

	wstring type = data.substr(0, pos);
	wstring result;
	wstringstream strStream;

	if (type == L"scene")			// �������
	{
#pragma region �������
		// ���� scene?
		if (m_isStart)
		{
			// ��������
			//printf("�������:%s\n", buf);
		}
#pragma endregion �������
	}
	else if (type == L"room")	// ���ҷ���
	{
#pragma region ���ҷ�������󷿼���Ϣ
		// ���� room?
		// ���� room:info{name:������;maxNumber:��������;nowNumber:��ǰ�����;start:�Ƿ�ʼ��Ϸ}";
		strStream << "room:info{name:" << m_gameRoomName << ";maxNumber:" << m_maxPlayerNumber << ";nowNumber:" << m_nowPlayerNumber<< ";start:" << m_isStart << "}";
		SendMsg(addr, strStream.str().c_str());
#pragma endregion ���ҷ�������󷿼���Ϣ
	}
	else if (type == L"join")	// �������
	{
#pragma region ������Ϸ
		// ���� join?{name:�����}";
		// ���� join:yes;userlist:{�û���:�û���ַ;�û���:�û���ַ;�û���:�û���ַ}	��	join:no;
		if (m_nowPlayerNumber < m_maxPlayerNumber)
		{
			m_nowPlayerNumber++;
			clientInfo cli;
			pos = data.find_first_of(L":");
			cli.userID = data.substr(pos+1, data.find_first_of(L"}")-pos-1);



			size_t len = strlen(addr) + 1;   
			size_t converted = 0;   
			wchar_t *WStr;   
			WStr=(wchar_t*)malloc(len*sizeof(wchar_t));   
			mbstowcs_s(&converted, WStr, len, addr, _TRUNCATE); 
			cli.dwIP = WStr;

			m_clientList.push_back(cli);
			m_userListChange = true;

			strStream << "join:yes;" << UserListToString();
		}
		else
		{
			strStream << "join:no;";
		}
		SendMsg(addr, strStream.str().c_str());
#pragma endregion ������Ϸ
	}
	else if (type == L"exit")	// �˳���Ϸ
	{
#pragma region �˳���Ϸ
		// ���� exit?{name:�����}";
		pos = data.find_first_of(L":");
		wstring uid = data.substr(pos+1, data.find_first_of(L"}")-pos-1);
		for (vector<Network::clientInfo>::iterator iter = m_clientList.begin(); iter != m_clientList.end(); iter++)
		{
			if (iter->userID == uid)
			{
				m_clientList.erase(iter);
				m_nowPlayerNumber--;
				m_userListChange = true;
				break;
			}
		}
#pragma endregion �˳���Ϸ
	}
	else if (type == L"userlist")// �����û��б�
	{
#pragma region �����û��б�
		// userlist:{�û���:�û���ַ;�û���:�û���ַ;�û���:�û���ַ}
		SendMsg(addr, UserListToString().c_str());
#pragma endregion �����û��б�
	}
	else
	{
		return;
	}

}

//************************************
// ������:  Network::Server::FeedbackThread
// ����:    void* pArguments	NULL
// ����ֵ:  unsigned
// ��������:protected static WINAPI
// ������   ��Ϣ�����߳�
//************************************
unsigned WINAPI Server::FeedbackThread(void* pArguments)
{
	while(m_isCreate)
	{
		// �û��б���
		if (m_userListChange)
		{
			// �㲥�û��б�
			m_userListChange = false;
			Broadcast(UserListToString().c_str());
		}

		// ��Ϸ������
		if (m_isStart)
		{
			// �㲥��Ϸ����
			Broadcast((L"scene:" + m_Scene).c_str());
		}

		Sleep(1);
	}
	return 0;
}


//************************************
// ������:  Network::IServer::CreateGameRoom
// ����ֵ:  int
// ����:    int maxPlayerNumber					����������
// ����:    const std::wstring & gameRoomName		��Ϸ���������
// ��������:
// ������   ������Ϸ����
//************************************
int Server::CreateGameRoom(int maxPlayerNumber, const std::wstring& gameRoomName)
{
	if(m_isCreate)
	{
		return ErrorCode::���ܴ����������;
	}

	// ��ʼ������
	m_maxPlayerNumber = maxPlayerNumber;
	m_nowPlayerNumber = 0;
	m_gameRoomName = gameRoomName;
	m_clientList.clear();
	m_isCreate = true;

#pragma region ��ʼ��Socket

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR)
	{
		return ErrorCode::��ʼ��Winsockʧ��;
	}

	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == m_socket)
	{
		return ErrorCode::����Socketʧ��;
	}
	SOCKADDR_IN socketSrv;
	socketSrv.sin_family = AF_INET;
	socketSrv.sin_port = htons(m_serverPort);
	socketSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	if (SOCKET_ERROR == bind(m_socket, (SOCKADDR*)&socketSrv, sizeof(SOCKADDR)))
	{
		closesocket(m_socket);
		return ErrorCode::��Socketʧ��;
	}

	m_broadcastSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == m_broadcastSocket)
	{
		return ErrorCode::����Socketʧ��;
	}
	m_broadcastAddr.sin_family = AF_INET;
	m_broadcastAddr.sin_port = htons(m_clientPort);
	m_broadcastAddr.sin_addr.s_addr = INADDR_BROADCAST;
	bool bOpt = true;
	//���ø��׽���Ϊ�㲥����
	setsockopt(m_broadcastSocket, SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));

#pragma endregion ��ʼ��Socket

	// ���������߳�
	if (_beginthreadex(NULL, 0, &ListenThread, NULL, 0, 0) == -1)
	{
		closesocket(m_socket);
		closesocket(m_broadcastSocket);
		return ErrorCode::�߳�����ʧ��;
	}

	// ������Ϣ�����߳�
	if (_beginthreadex(NULL, 0, &FeedbackThread, NULL, 0, 0) == -1)
	{
		closesocket(m_socket);
		closesocket(m_broadcastSocket);
		return ErrorCode::�߳�����ʧ��;
	}

	wstringstream strStream;
	strStream << "room:setup;info{name:" << m_gameRoomName << ";maxNumber:" << m_maxPlayerNumber << ";nowNumber:" << m_nowPlayerNumber<< ";start:" << m_isStart << "}";
	Broadcast(strStream.str().c_str());
	

	return ErrorCode::ACCEPT;
}

//************************************
// ������:  Network::IServer::CloseGameRoom
// ����ֵ:  int
// ����:    const std::wstring & gameRoomName		��Ϸ���������
// ��������:
// ������   �ر���Ϸ����
//************************************
int Server::CloseGameRoom(const std::wstring& gameRoomName)
{
	if(m_isCreate)
	{
		// ��ʼ������
		m_clientList.clear();
		m_isCreate = false;

		Broadcast(L"room:close;");

		// �ر�socket
		closesocket(m_socket);
		closesocket(m_broadcastSocket);
	}

	return ErrorCode::ACCEPT;
}

//************************************
// ������:  Network::IServer::Start
// ����ֵ:  int
// ��������:
// ������   ������Ϸ���䣬��ʼ���ܿͻ�������
//************************************
int Server::Start()
{
	m_isStart = true;

	// ������Ϣ֪ͨ��Ϸ��ʼ
	Broadcast(L"game:start;");

	return 0;
}

//************************************
// ������:  Network::IServer::Stop
// ����ֵ:  int
// ��������:
// ������   ֹͣ��Ϸ����
//************************************
int Server::Stop()
{
	m_isStart = false;

	// ������Ϣ֪ͨ��Ϸ����
	Broadcast(L"game:stop;");

	return 0;
}
