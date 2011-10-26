///********************************************************************
//创建时间: 2011-10-22   15:00
//文件名:   Server.h
//作者:     陈存腾
//说明:     服务器网络实现
//
//*********************************************************************/
//
//#pragma once
//#include <vector>
//#include <process.h>
//#include "IServer.h"
//#include "Network.h"
//#include <WinSock2.h>
//#pragma comment(lib,"wsock32.lib")
//
//
//using namespace std;
//
//namespace Network
//{
//	class Server :
//		public IServer
//	{
//	public:
//		Server(void);
//		~Server(void);
//
//#pragma region 服务器状态
//
//	public:
//
//		// 房间是否创建
//		static bool m_isCreate;
//
//		// 游戏是否启动
//		static bool m_isStart;
//
//		// 用户列表变动
//		static bool m_userListChange;
//
//		// 房间名
//		static std::wstring m_gameRoomName;
//
//		// 最大游戏人数
//		static int m_maxPlayerNumber;
//
//		// 当前游戏人数
//		static int m_nowPlayerNumber;
//		
//		// client列表
//		static vector<clientInfo> m_clientList;
//
//		// 服务器地址
//		static wchar_t* m_serverIP;
//
//		// 服务端Socket绑定的端口号
//		static unsigned short m_serverPort;
//
//		// 客户端Socket绑定的端口号
//		static unsigned short m_clientPort;
//
//		// 监听Socket
//		static SOCKET m_socket;
//		static SOCKADDR_IN m_targetAddr;
//
//		// 广播Socket
//		static SOCKET m_broadcastSocket;
//		static SOCKADDR_IN m_broadcastAddr;
//
//		// 缓冲区大小
//		static const int m_bufferLength;
//
//		// SOCKADDR_IN大小
//		static const int m_tolen;
//
//		// 游戏场景
//		static wstring m_Scene;
//
//	#pragma endregion 服务器状态
//
//	protected:
//		
//		//************************************
//		// 函数名:  Network::Server::ListenThread
//		// 参数:    void* pArguments	NULL
//		// 返回值:  unsigned
//		// 函数修饰:protected static WINAPI
//		// 描述：   监听线程
//		//************************************
//		static unsigned WINAPI ListenThread(void* pArguments);
//
//#pragma region 处理接收到的信息
//
//		//************************************
//		// 函数名:  Network::Server::RecvData
//		// 参数:    wchar_t *addr		地址
//		// 参数:    int port		端口号
//		// 参数:    wchar_t *buf		消息
//		// 参数:    int size		大小
//		// 返回值:  void
//		// 函数修饰:protected static
//		// 描述：   处理接收到的消息
//		//************************************
//		static void RecvData(char *addr, int port, wchar_t *buf, int size);
//
//		//************************************
//		// 函数名:  Network::Server::UserListToString
//		// 参数:    void
//		// 返回值:  void
//		// 函数修饰:protected static
//		// 描述：   处理接收到的消息
//		//************************************
//		static std::wstring UserListToString(void);
//	
//#pragma endregion 处理接收到的信息
//
//		//************************************
//		// 函数名:  Network::Server::FeedbackThread
//		// 参数:    void* pArguments	NULL
//		// 返回值:  unsigned
//		// 函数修饰:protected static WINAPI
//		// 描述：   信息反馈线程
//		//************************************
//		static unsigned WINAPI FeedbackThread(void* pArguments);
//
//		////************************************
//		//// 函数名:  Network::Server::GetIp
//		//// 返回值:  wchar_t*		本机IP
//		//// 函数修饰:protected static
//		//// 描述：   用于获取本机IP地址
//		////************************************
//		//static wchar_t* GetIp(void);
//
//
//	public:
//		
//		//************************************
//		// 函数名:  Network::Server::SendMsg
//		// 参数1:   const wchar_t* dwIP		对方IP
//		// 参数2:   const wchar_t* buf		发送数据
//		// 返回值:  ErrorCode
//		// 函数修饰:public static
//		// 描述：   发送消息
//		//************************************
//		static ErrorCode SendMsg(const char* dwIP, const wchar_t* buf);
//
//		//************************************
//		// 函数名:  Network::Server::Broadcast
//		// 参数:    const wchar_t* msg		要发送的消息
//		// 返回值:  ErrorCode
//		// 函数修饰:public static
//		// 描述：   广播消息
//		//************************************
//		static ErrorCode Broadcast(const wchar_t* msg);
//		
//		//************************************
//		// 函数名:  Network::Server::SetServerPort
//		// 参数:    unsigned short port	端口号
//		// 返回值:  void
//		// 函数修饰:public
//		// 描述：   设置服务器监听的端口号
//		//************************************
//		void SetServerPort(unsigned short port);
//		
//		//************************************
//		// 函数名:  Network::Server::SetClientPort
//		// 参数:    unsigned short port	端口号
//		// 返回值:  void
//		// 函数修饰:public
//		// 描述：   设置客户端监听的端口号
//		//************************************
//		void SetClientPort(unsigned short port);
//	
//	#pragma region IServer实现
//
//		//************************************
//		// 函数名:  Network::IServer::CreateGameRoom
//		// 返回值:  int
//		// 参数:    int maxPlayerNumber					最大玩家数量
//		// 参数:    const std::wstring & gameRoomName		游戏房间的名字
//		// 函数修饰:
//		// 描述：   创建游戏房间
//		//************************************
//		virtual int CreateGameRoom( 
//			int maxPlayerNumber, 
//			const std::wstring& gameRoomName 
//			);
//
//		//************************************
//		// 函数名:  Network::IServer::CloseGameRoom
//		// 返回值:  int
//		// 参数:    const std::wstring & gameRoomName		游戏房间的名字
//		// 函数修饰:
//		// 描述：   关闭游戏房间
//		//************************************
//		virtual int CloseGameRoom(
//			const std::wstring& gameRoomName 
//			);
//
//		//************************************
//		// 函数名:  Network::IServer::Start
//		// 返回值:  int
//		// 函数修饰:
//		// 描述：   启动游戏房间，开始接受客户端连接
//		//************************************
//		virtual int Start();
//
//		//************************************
//		// 函数名:  Network::IServer::Stop
//		// 返回值:  int
//		// 函数修饰:
//		// 描述：   停止游戏房间
//		//************************************
//		virtual int Stop();
//
//	#pragma endregion IServer实现
//	};
//
//}