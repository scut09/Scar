/********************************************************************
创建时间: 2011-10-22   15:00
文件名:   Server.h
作者:     陈存腾
说明:     客户端网络实现

*********************************************************************/

#pragma once
#include <vector>
#include <process.h>
#include <time.h>
#include "IClient.h"
#include "Network.h"
#include <WinSock2.h>
#pragma comment(lib,"wsock32.lib")

using namespace std;

namespace Network
{

	class Client :
		public Network::IClient
	{
	public:
		Client(void);
		~Client(void);

		
	protected:
		
#pragma region 静态成员变量

		// 监听超时时间(毫秒)
		static int m_overtime;

		// 客户端ID
		static wstring m_ID;

		// 正在搜索服务器
		static bool m_isSearch;

		// 正在搜索服务器
		static int m_isJoinRoom;

		// 服务器列表
		static ServerInfoList m_serverList;

		// 游戏是否启动
		static bool m_isStart;
		
		// client列表
		static vector<clientInfo> m_clientList;

		// 服务端Socket绑定的端口号
		static unsigned short m_serverPort;

		// 客户端Socket绑定的端口号
		static unsigned short m_clientPort;

		// 监听Socket
		static SOCKET m_socket;
		static SOCKADDR_IN m_targetAddr;

		// 缓冲区大小
		static const int m_bufferLength;

		// SOCKADDR_IN大小
		static const int m_tolen;

		// 游戏场景
		static wstring m_Scene;

	#pragma endregion 静态成员变量

	protected:
		
		//************************************
		// 函数名:  Network::Client::ListenThread
		// 参数:    void* pArguments	NULL
		// 返回值:  unsigned
		// 函数修饰:protected static WINAPI
		// 描述：   监听线程
		//************************************
		static unsigned WINAPI ListenThread(void* pArguments);

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
		static void RecvData(char *addr, int port, wchar_t *buf, int size);
	
		//************************************
		// 函数名:  Network::Client::FeedbackThread
		// 参数:    void* pArguments	NULL
		// 返回值:  unsigned
		// 函数修饰:protected static WINAPI
		// 描述：   信息反馈线程
		//************************************
		static unsigned WINAPI FeedbackThread(void* pArguments);

	public:

		char* ConvertLPWSTRToLPSTR (LPWSTR lpwszStrIn);
		
		//************************************
		// 函数名:  Network::Client::SetID
		// 参数:    wstring name		客户端名
		// 返回值:  void
		// 函数修饰:public static
		// 描述：   设置客户端名
		//************************************
		static void SetID(wstring name);
		
		//************************************
		// 函数名:  Network::Client::SendMsgToServer
		// 参数:    const wchar_t* buf		发送数据
		// 返回值:  ErrorCode
		// 函数修饰:public static
		// 描述：   发送消息给服务器
		//************************************
		static ErrorCode SendMsgToServer(const wchar_t* buf);

		//************************************
		// 函数名:  Network::Client::SetServerPort
		// 参数:    unsigned short port	端口号
		// 返回值:  void
		// 函数修饰:public
		// 描述：   设置服务器监听的端口号
		//************************************
		void SetServerPort(unsigned short port);
		
		//************************************
		// 函数名:  Network::Client::SetClientPort
		// 参数:    unsigned short port	端口号
		// 返回值:  void
		// 函数修饰:public
		// 描述：   设置客户端监听的端口号
		//************************************
		void SetClientPort(unsigned short port);

	#pragma region IClient实现

		static IClientOnMsgCallbackFuncType callback;

		//************************************
		// 函数名:  IClient::SearchGameRoom
		// 返回值:  ServerInfoList
		// 函数修饰:
		// 描述：   查找当前局域网的服务器，我们先暂定端口号为 54321
		//************************************
		virtual ServerInfoList SearchGameRoom();

		//************************************
		// 函数名:  IClient::EnterGameRoom
		// 返回值:  int
		// 参数:    const std::wstring & ip
		// 函数修饰:
		// 描述：   加入服务器
		//************************************
		virtual int EnterGameRoom( const std::wstring& ip );

		//************************************
		// 函数名:  IClient::LeaveGameRoom
		// 返回值:  int
		// 参数:    const std::wstring & ip
		// 函数修饰:
		// 描述：   退出服务器
		//************************************
		virtual int LeaveGameRoom( const std::wstring& ip );

		//************************************
		// 函数名:  IClient::SetOnMsgCallbackFunc
		// 返回值:  void
		// 参数:    IClientOnMsgCallbackFuncType func
		// 函数修饰:
		// 描述：   设置消息到达时的回调处理函数，每次在客户端消息到达时，客户端都应调用
		//			此函数设置的回调函数来处理消息。
		//************************************
		virtual void SetOnMsgCallbackFunc( IClientOnMsgCallbackFuncType func );
	#pragma endregion IClient实现

	};

}