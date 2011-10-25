/********************************************************************
创建时间: 2011-10-22   15:00
文件名:   Server.cpp
作者:     陈存腾
说明:     服务器网络实现

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

#pragma region 静态数据定义及初始化

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

#pragma endregion 静态数据定义及初始化

//************************************
// 函数名:  Network::Server::SetServerPort
// 参数:    unsigned short port	端口号
// 返回值:  void
// 函数修饰:public
// 描述：   设置服务器监听的端口号
//************************************
void Server::SetServerPort(unsigned short port)
{
	m_serverPort = port;
}
		
//************************************
// 函数名:  Network::Server::SetClientPort
// 参数:    unsigned short port	端口号
// 返回值:  void
// 函数修饰:public
// 描述：   设置客户端监听的端口号
//************************************
void Server::SetClientPort(unsigned short port)
{
	m_clientPort = port;
}

////************************************
//// 函数名:  GetIp
//// 返回值:  wchar_t*
//// 函数修饰:protected static 
//// 描述：   用于获取本机IP地址
////************************************
//wchar_t* Server::GetIp(void)
//{
//	WSADATA wsaData;
//	wchar_t name[255]; //定义用于存放获得的主机名的变量 
//	wchar_t *ip; //定义IP地址变量 
//	PHOSTENT hostinfo; 
//
//	//调用MAKEWORD（）获得Winsock版本的正确值，用于加载Winsock库 
//	if ( WSAStartup( MAKEWORD(2,0), &wsaData ) == 0 )
//	{ 
//		//现在是加载Winsock库，如果WSAStartup（）函数返回值为0，说明加载成功，程序可以继续 
//		if( gethostname ( name, sizeof(name)) == 0)
//		{ 
//			//如果成功地将本地主机名存放入由name参数指定的缓冲区中 
//			if((hostinfo = gethostbyname(name)) != NULL)
//			{ 
//				//这是获取主机名，如果获得主机名成功的话，将返回一个指针，指向hostinfo，hostinfo
//				//为PHOSTENT型的变量，下面即将用到这个结构体 
//				ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list); 
//				//调用inet_ntoa（）函数，将hostinfo结构变量中的h_addr_list转化为标准的点分表示的IP
//			} 
//		} 
//		WSACleanup( ); //卸载Winsock库，并释放所有资源 
//	}
//	return ip;
//} 

//************************************
// 函数名:  Network::Server::SendMsg
// 参数1:   const wchar_t* dwIP		对方IP
// 参数2:   wchar_t* buf		发送数据
// 返回值:  ErrorCode
// 函数修饰:protected static
// 描述：   发送消息
//************************************
ErrorCode Server::SendMsg(const char* dwIP, const wchar_t* buf)
{
	m_targetAddr.sin_family = AF_INET;
	m_targetAddr.sin_port = htons(m_clientPort);
	m_targetAddr.sin_addr.S_un.S_addr = inet_addr(dwIP);

	int nSendSize = sendto(m_socket, (char*)buf, sizeof(wchar_t)*(wcslen(buf)+1), 0, (SOCKADDR *) &m_targetAddr, m_tolen);

	if (nSendSize == -1)
	{
		return ErrorCode::消息发送失败;
	}

	return ErrorCode::ACCEPT;
}

//************************************
// 函数名:  Network::Server::Broadcast
// 参数:    const wchar_t* msg		要发送的消息
// 返回值:  ErrorCode
// 函数修饰:public static
// 描述：   广播消息
//************************************
ErrorCode Server::Broadcast(const wchar_t* msg)
{
	int nSendSize = sendto(m_broadcastSocket, (char*)msg, sizeof(wchar_t)*(wcslen(msg)+1), 0, (SOCKADDR*)&m_broadcastAddr, m_tolen);

	if (nSendSize == -1)
	{
		return ErrorCode::消息发送失败;
	}

	return ErrorCode::ACCEPT;
}

//************************************
// 函数名:  Network::Server::ListenThread
// 参数:    void* pArguments	NULL
// 返回值:  unsigned
// 函数修饰:protected WINAPI
// 描述：   监听线程
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

			// 处理接收到的消息
			RecvData(addr, port, buffer, size);
		}
		Sleep(1);
	}

	delete []addr;
	delete []buffer;
	return 0;
}


//************************************
// 函数名:  Network::Server::UserListToString
// 参数:    void
// 返回值:  wstring			格式化后的用户列表
// 函数修饰:protected static
// 描述：   把userlist转为wstring
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
// 函数名:  Network::Server::RecvData
// 参数:    wchar_t *addr		地址
// 参数:    int port		端口号
// 参数:    wchar_t *buf		消息
// 参数:    int size		大小
// 返回值:  void
// 函数修饰:protected static
// 描述：   处理接收到的消息
//************************************
void Server::RecvData(char *addr, int port, wchar_t *buf, int size)
{
	//printf("收到%s\t%d\t%d\t%s\n", addr, port, size, buf);

	wstring data = buf;
	int pos = data.find_first_of(L"?");
	if (pos == -1)
	{
		return;
	}

	wstring type = data.substr(0, pos);
	wstring result;
	wstringstream strStream;

	if (type == L"scene")			// 场景变更
	{
#pragma region 场景变更
		// 接收 scene?
		if (m_isStart)
		{
			// 解析场景
			//printf("场景变更:%s\n", buf);
		}
#pragma endregion 场景变更
	}
	else if (type == L"room")	// 查找房间
	{
#pragma region 查找房间或请求房间信息
		// 接收 room?
		// 发送 room:info{name:房间名;maxNumber:最大玩家数;nowNumber:当前玩家数;start:是否开始游戏}";
		strStream << "room:info{name:" << m_gameRoomName << ";maxNumber:" << m_maxPlayerNumber << ";nowNumber:" << m_nowPlayerNumber<< ";start:" << m_isStart << "}";
		SendMsg(addr, strStream.str().c_str());
#pragma endregion 查找房间或请求房间信息
	}
	else if (type == L"join")	// 申请加入
	{
#pragma region 加入游戏
		// 接收 join?{name:玩家名}";
		// 发送 join:yes;userlist:{用户名:用户地址;用户名:用户地址;用户名:用户地址}	或	join:no;
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
#pragma endregion 加入游戏
	}
	else if (type == L"exit")	// 退出游戏
	{
#pragma region 退出游戏
		// 接收 exit?{name:玩家名}";
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
#pragma endregion 退出游戏
	}
	else if (type == L"userlist")// 请求用户列表
	{
#pragma region 请求用户列表
		// userlist:{用户名:用户地址;用户名:用户地址;用户名:用户地址}
		SendMsg(addr, UserListToString().c_str());
#pragma endregion 请求用户列表
	}
	else
	{
		return;
	}

}

//************************************
// 函数名:  Network::Server::FeedbackThread
// 参数:    void* pArguments	NULL
// 返回值:  unsigned
// 函数修饰:protected static WINAPI
// 描述：   信息反馈线程
//************************************
unsigned WINAPI Server::FeedbackThread(void* pArguments)
{
	while(m_isCreate)
	{
		// 用户列表变更
		if (m_userListChange)
		{
			// 广播用户列表
			m_userListChange = false;
			Broadcast(UserListToString().c_str());
		}

		// 游戏已启动
		if (m_isStart)
		{
			// 广播游戏场景
			Broadcast((L"scene:" + m_Scene).c_str());
		}

		Sleep(1);
	}
	return 0;
}


//************************************
// 函数名:  Network::IServer::CreateGameRoom
// 返回值:  int
// 参数:    int maxPlayerNumber					最大玩家数量
// 参数:    const std::wstring & gameRoomName		游戏房间的名字
// 函数修饰:
// 描述：   创建游戏房间
//************************************
int Server::CreateGameRoom(int maxPlayerNumber, const std::wstring& gameRoomName)
{
	if(m_isCreate)
	{
		return ErrorCode::不能创建多个房间;
	}

	// 初始化房间
	m_maxPlayerNumber = maxPlayerNumber;
	m_nowPlayerNumber = 0;
	m_gameRoomName = gameRoomName;
	m_clientList.clear();
	m_isCreate = true;

#pragma region 初始化Socket

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR)
	{
		return ErrorCode::初始化Winsock失败;
	}

	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == m_socket)
	{
		return ErrorCode::创建Socket失败;
	}
	SOCKADDR_IN socketSrv;
	socketSrv.sin_family = AF_INET;
	socketSrv.sin_port = htons(m_serverPort);
	socketSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	if (SOCKET_ERROR == bind(m_socket, (SOCKADDR*)&socketSrv, sizeof(SOCKADDR)))
	{
		closesocket(m_socket);
		return ErrorCode::绑定Socket失败;
	}

	m_broadcastSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == m_broadcastSocket)
	{
		return ErrorCode::创建Socket失败;
	}
	m_broadcastAddr.sin_family = AF_INET;
	m_broadcastAddr.sin_port = htons(m_clientPort);
	m_broadcastAddr.sin_addr.s_addr = INADDR_BROADCAST;
	bool bOpt = true;
	//设置该套接字为广播类型
	setsockopt(m_broadcastSocket, SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));

#pragma endregion 初始化Socket

	// 创建监听线程
	if (_beginthreadex(NULL, 0, &ListenThread, NULL, 0, 0) == -1)
	{
		closesocket(m_socket);
		closesocket(m_broadcastSocket);
		return ErrorCode::线程启动失败;
	}

	// 创建信息反馈线程
	if (_beginthreadex(NULL, 0, &FeedbackThread, NULL, 0, 0) == -1)
	{
		closesocket(m_socket);
		closesocket(m_broadcastSocket);
		return ErrorCode::线程启动失败;
	}

	wstringstream strStream;
	strStream << "room:setup;info{name:" << m_gameRoomName << ";maxNumber:" << m_maxPlayerNumber << ";nowNumber:" << m_nowPlayerNumber<< ";start:" << m_isStart << "}";
	Broadcast(strStream.str().c_str());
	

	return ErrorCode::ACCEPT;
}

//************************************
// 函数名:  Network::IServer::CloseGameRoom
// 返回值:  int
// 参数:    const std::wstring & gameRoomName		游戏房间的名字
// 函数修饰:
// 描述：   关闭游戏房间
//************************************
int Server::CloseGameRoom(const std::wstring& gameRoomName)
{
	if(m_isCreate)
	{
		// 初始化房间
		m_clientList.clear();
		m_isCreate = false;

		Broadcast(L"room:close;");

		// 关闭socket
		closesocket(m_socket);
		closesocket(m_broadcastSocket);
	}

	return ErrorCode::ACCEPT;
}

//************************************
// 函数名:  Network::IServer::Start
// 返回值:  int
// 函数修饰:
// 描述：   启动游戏房间，开始接受客户端连接
//************************************
int Server::Start()
{
	m_isStart = true;

	// 发送消息通知游戏开始
	Broadcast(L"game:start;");

	return 0;
}

//************************************
// 函数名:  Network::IServer::Stop
// 返回值:  int
// 函数修饰:
// 描述：   停止游戏房间
//************************************
int Server::Stop()
{
	m_isStart = false;

	// 发送消息通知游戏结束
	Broadcast(L"game:stop;");

	return 0;
}
