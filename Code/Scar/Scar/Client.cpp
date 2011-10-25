/********************************************************************
创建时间: 2011-10-22   15:00
文件名:   Server.h
作者:     陈存腾
说明:     客户端网络实现

*********************************************************************/


#include "Client.h"

using namespace Network;

Client::Client(void)
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);

	m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	SOCKADDR_IN socketSrv;
	socketSrv.sin_family = AF_INET;
	socketSrv.sin_port = htons(m_clientPort);
	socketSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	::bind(m_socket, (SOCKADDR*)&socketSrv, sizeof(SOCKADDR));

	m_targetAddr.sin_family = AF_INET;
	m_targetAddr.sin_port = htons(m_serverPort);


	// 创建监听线程
	if (_beginthreadex(NULL, 0, &ListenThread, NULL, 0, 0) == -1)
	{
		closesocket(m_socket);
		MessageBox(NULL,_T("线程启动失败"),_T("错误"),MB_OK);
	}
}


Client::~Client(void)
{
	closesocket(m_socket);
}


#pragma region 静态数据定义及初始化

int Client::m_overtime = 5000;
SOCKET Client::m_socket;
SOCKADDR_IN Client::m_targetAddr;
bool Client::m_isStart = false;
int Client::m_isJoinRoom = 0;
bool Client::m_isSearch = false;
unsigned short Client::m_serverPort (54321);
unsigned short Client::m_clientPort (55555);
const int Client::m_bufferLength(0X4000);
const int Client::m_tolen(sizeof(SOCKADDR));
wstring Client::m_Scene = L"";
wstring Client::m_ID = L"";
ServerInfoList Client::m_serverList;
IClientOnMsgCallbackFuncType Client::callback;

#pragma endregion 静态数据定义及初始化

char* Client::ConvertLPWSTRToLPSTR (LPWSTR lpwszStrIn)
{
	LPSTR pszOut = NULL;
	if (lpwszStrIn != NULL)
	{
		int nInputStrLen = wcslen (lpwszStrIn);

		// Double NULL Termination
		int nOutputStrLen = WideCharToMultiByte (CP_ACP, 0, lpwszStrIn, nInputStrLen, NULL, 0, 0, 0) + 2;
		pszOut = new char [nOutputStrLen];

		if (pszOut)
		{
			memset (pszOut, 0x00, nOutputStrLen);
			WideCharToMultiByte(CP_ACP, 0, lpwszStrIn, nInputStrLen, pszOut, nOutputStrLen, 0, 0);
		}
	}
	return pszOut;
}


//************************************
// 函数名:  Network::Client::SetID
// 参数:    wstring name		客户端名
// 返回值:  void
// 函数修饰:public static
// 描述：   设置客户端名
//************************************
void Client::SetID(wstring name)
{
	if(name != L"")
	{
		m_ID = name;
	}
}

//************************************
// 函数名:  Network::Client::SetServerPort
// 参数:    unsigned short port	端口号
// 返回值:  void
// 函数修饰:public
// 描述：   设置服务器监听的端口号
//************************************
void Client::SetServerPort(unsigned short port)
{
	m_serverPort = port;
}
		
//************************************
// 函数名:  Network::Client::SetClientPort
// 参数:    unsigned short port	端口号
// 返回值:  void
// 函数修饰:public
// 描述：   设置客户端监听的端口号
//************************************
void Client::SetClientPort(unsigned short port)
{
	m_clientPort = port;
}

//************************************
// 函数名:  Network::Client::SendMsgToServer
// 参数:    const wchar_t* buf		发送数据
// 返回值:  ErrorCode
// 函数修饰:protected static
// 描述：   发送消息给服务器
//************************************
ErrorCode Client::SendMsgToServer(const wchar_t* buf)
{
	int nSendSize = sendto(m_socket, (char*)buf, sizeof(wchar_t)*(wcslen(buf)+1), 0, (SOCKADDR *) &m_targetAddr, m_tolen);

	if (nSendSize == -1)
	{
		return ErrorCode::消息发送失败;
	}

	return ErrorCode::ACCEPT;
}

//************************************
// 函数名:  Network::Client::ListenThread
// 参数:    void* pArguments	NULL
// 返回值:  unsigned
// 函数修饰:protected WINAPI
// 描述：   监听线程
//************************************
unsigned WINAPI Client::ListenThread(void* pArguments)
{
	char *addr = new char[16];
	int port;
	wchar_t *buffer = new wchar_t[m_bufferLength];
	struct sockaddr_in from;
	int fromlen = sizeof(from);
	int size;
	
	while (1)
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
// 函数名:  Network::Client::RecvData
// 参数:    char *addr		地址
// 参数:    int port		端口号
// 参数:    wchar_t *buf		消息
// 参数:    int size		大小
// 返回值:  void
// 函数修饰:protected static
// 描述：   处理接收到的消息
//************************************
void Client::RecvData(char *addr, int port, wchar_t *buf, int size)
{
	static int i =0;
	//printf("%d\t收到%s\t%d\t%d\t%s\n", i++, addr, port, size, buf);


	wstring data = buf;
	int pos = data.find_first_of(L":");
	int pos2;
	if (pos == -1)
	{
		return;
	}

	wstring type = data.substr(0, pos);
	wstring result;

	if (type == L"scene")			// 场景变更
	{
#pragma region 场景变更
		// 接收 scene:场景信息
		if (m_isStart)
		{
			// 回调
			callback(buf);
			// 解析场景
			//printf("场景变更:%s\n", buf);
		}
#pragma endregion 场景变更
	}
	else if (type == L"room")	// 房间信息
	{
#pragma region 查找房间或请求房间信息
		// 创建房间 room:setup;info{name:房间名;maxNumber:最大用户容量;nowNumber:当前用户数;start:是否开始游戏};
		// 关闭房间 room:close;
		// 信息 room:info{name:房间名;maxNumber:最大玩家数;nowNumber:当前玩家数;start:是否开始游戏};
		if (data[pos+1] == 'c')
		{
		}
		else if (data[pos+1] == 's')
		{
			ServerInfo info;

			size_t len = strlen(addr) + 1;   
			size_t converted = 0;   
			wchar_t *WStr;   
			WStr=(wchar_t*)malloc(len*sizeof(wchar_t));   
			mbstowcs_s(&converted, WStr, len, addr, _TRUNCATE); 

			info.ip = WStr;

			pos = data.find_first_of(':', pos+1);
			pos2 = data.find_first_of(';', pos);
			info.roomName = data.substr(pos+1, pos2-pos-1);

			pos = data.find_first_of(':', pos2);
			pos2 = data.find_first_of(';', pos);
			info.maxPlayerNumber = _wtoi(data.substr(pos+1, pos2-pos-1).c_str());

			pos = data.find_first_of(':', pos2);
			pos2 = data.find_first_of(';', pos);
			info.currentPlayerNumber = _wtoi(data.substr(pos+1, pos2-pos-1).c_str());

			m_serverList.push_back(info);
		}
		else if (data[pos+1] == 'i')
		{
			ServerInfo info;

			size_t len = strlen(addr) + 1;   
			size_t converted = 0;   
			wchar_t *WStr;   
			WStr=(wchar_t*)malloc(len*sizeof(wchar_t));   
			mbstowcs_s(&converted, WStr, len, addr, _TRUNCATE); 

			info.ip = WStr;

			pos = data.find_first_of(':', pos+1);
			pos2 = data.find_first_of(';', pos);
			info.roomName = data.substr(pos+1, pos2-pos-1);

			pos = data.find_first_of(':', pos2);
			pos2 = data.find_first_of(';', pos);
			info.maxPlayerNumber = _wtoi(data.substr(pos+1, pos2-pos-1).c_str());

			pos = data.find_first_of(':', pos2);
			pos2 = data.find_first_of(';', pos);
			info.currentPlayerNumber = _wtoi(data.substr(pos+1, pos2-pos-1).c_str());

			m_serverList.push_back(info);
		}
		m_isSearch = false;
#pragma endregion 查找房间或请求房间信息
	}
	else if (type == L"join")	// 申请加入应答
	{
#pragma region 申请加入应答
		// 发送 join:yes;userlist:{用户名:用户地址;用户名:用户地址;用户名:用户地址}	或	join:no;
		if (data[pos+1] == 'y')
		{
			m_isJoinRoom = 1;
		}
		else
		{
			m_isJoinRoom = -1;
		}


#pragma endregion 申请加入应答
	}
	else if (type == L"game")	// 游戏开始或关闭
	{
#pragma region 游戏开始或关闭
		// 游戏开始 game:start;
		// 游戏结束 game:stop;
		// 解析
#pragma endregion 游戏开始或关闭
	}
	else if (type == L"userlist")	// 用户列表
	{
#pragma region 用户列表
		// userlist:{用户名:用户地址;用户名:用户地址;用户名:用户地址}
		// 解析用户列表
#pragma endregion 请求用户列表
	}
	else if (type == L"result")// 游戏结果
	{
	}
	else
	{
		// 回调
		callback(buf);
		return;
	}
}

//************************************
// 函数名:  Network::Client::FeedbackThread
// 参数:    void* pArguments	NULL
// 返回值:  unsigned
// 函数修饰:protected static WINAPI
// 描述：   信息反馈线程
//************************************
unsigned WINAPI Client::FeedbackThread(void* pArguments)
{
	// 已加入房间
	while(m_isJoinRoom)
	{
		// 游戏已启动
		if (m_isStart)
		{
			// 提交游戏场景变更
			SendMsgToServer(m_Scene.c_str());
		}

		Sleep(1);
	}
	return 0;
}


//************************************
// 函数名:  IClient::SearchGameRoom
// 返回值:  ServerInfoList
// 函数修饰:
// 描述：   查找当前局域网的服务器，我们先暂定端口号为 54321
//************************************
ServerInfoList Client::SearchGameRoom()
{
	m_serverList.clear();
	// 广播Socket
	SOCKET search_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	SOCKADDR_IN sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(m_serverPort);
	sin.sin_addr.s_addr = INADDR_BROADCAST;
	bool bOpt = true;
	setsockopt(search_socket, SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));

	m_isSearch = true;
	wchar_t buf[] = {L"room?"};
	int nSendSize = sendto(search_socket, (char*)buf, sizeof(wchar_t)*(wcslen(buf)+1), 0, (SOCKADDR*)&sin, m_tolen);
	
	// 等待服务器信息返回
	while (m_isSearch)
	{
		Sleep(1);
	}

	return m_serverList;
}

//************************************
// 函数名:  IClient::EnterGameRoom
// 返回值:  int
// 参数:    const std::wstring & ip
// 函数修饰:
// 描述：   加入服务器
//************************************
int Client::EnterGameRoom( const std::wstring& ip )
{
	m_isJoinRoom = 0;
	// 发送 join?{name:玩家名}";

	size_t len = wcslen(ip.c_str()) + 1;   
	size_t converted = 0;   
	char *CStr;   
	CStr=(char*)malloc(len*sizeof(char));   
	wcstombs_s(&converted, CStr, len, ip.c_str(), _TRUNCATE);  

	m_targetAddr.sin_addr.S_un.S_addr = inet_addr(CStr);
	SendMsgToServer((L"join?{name:" + m_ID + L"}").c_str());

	time_t t_start;
	t_start = time(NULL);

	// 等待服务器信息返回
	while (!m_isJoinRoom)
	{
		// 超时退出
		if (time(NULL) - t_start > m_overtime)
		{
			return 0;
		}
		Sleep(1);
	}

	// 加入成功
	if (m_isJoinRoom == 1)
	{
		// 创建信息反馈线程
		if (_beginthreadex(NULL, 0, &FeedbackThread, NULL, 0, 0) == -1)
		{
			return 0;
			MessageBox(NULL,_T("线程启动失败"),_T("错误"),MB_OK);
		}
	}
	
	return m_isJoinRoom;
}

//************************************
// 函数名:  IClient::LeaveGameRoom
// 返回值:  int
// 参数:    const std::wstring & ip
// 函数修饰:
// 描述：   退出服务器
//************************************
int Client::LeaveGameRoom( const std::wstring& ip )
{
	SendMsgToServer(L"leave");
	m_isJoinRoom = 0;
	return 0;
}

//************************************
// 函数名:  IClient::SetOnMsgCallbackFunc
// 返回值:  void
// 参数:    IClientOnMsgCallbackFuncType func
// 函数修饰:
// 描述：   设置消息到达时的回调处理函数，每次在客户端消息到达时，客户端都应调用
//			此函数设置的回调函数来处理消息。
//************************************
void Client::SetOnMsgCallbackFunc( IClientOnMsgCallbackFuncType func )
{
	if(func != NULL)
	{
		callback = func;
	}
}
