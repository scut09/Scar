///********************************************************************
//����ʱ��: 2011-10-22   15:00
//�ļ���:   Server.h
//����:     �´���
//˵��:     ����������ʵ��
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
//#pragma region ������״̬
//
//	public:
//
//		// �����Ƿ񴴽�
//		static bool m_isCreate;
//
//		// ��Ϸ�Ƿ�����
//		static bool m_isStart;
//
//		// �û��б�䶯
//		static bool m_userListChange;
//
//		// ������
//		static std::wstring m_gameRoomName;
//
//		// �����Ϸ����
//		static int m_maxPlayerNumber;
//
//		// ��ǰ��Ϸ����
//		static int m_nowPlayerNumber;
//		
//		// client�б�
//		static vector<clientInfo> m_clientList;
//
//		// ��������ַ
//		static wchar_t* m_serverIP;
//
//		// �����Socket�󶨵Ķ˿ں�
//		static unsigned short m_serverPort;
//
//		// �ͻ���Socket�󶨵Ķ˿ں�
//		static unsigned short m_clientPort;
//
//		// ����Socket
//		static SOCKET m_socket;
//		static SOCKADDR_IN m_targetAddr;
//
//		// �㲥Socket
//		static SOCKET m_broadcastSocket;
//		static SOCKADDR_IN m_broadcastAddr;
//
//		// ��������С
//		static const int m_bufferLength;
//
//		// SOCKADDR_IN��С
//		static const int m_tolen;
//
//		// ��Ϸ����
//		static wstring m_Scene;
//
//	#pragma endregion ������״̬
//
//	protected:
//		
//		//************************************
//		// ������:  Network::Server::ListenThread
//		// ����:    void* pArguments	NULL
//		// ����ֵ:  unsigned
//		// ��������:protected static WINAPI
//		// ������   �����߳�
//		//************************************
//		static unsigned WINAPI ListenThread(void* pArguments);
//
//#pragma region ������յ�����Ϣ
//
//		//************************************
//		// ������:  Network::Server::RecvData
//		// ����:    wchar_t *addr		��ַ
//		// ����:    int port		�˿ں�
//		// ����:    wchar_t *buf		��Ϣ
//		// ����:    int size		��С
//		// ����ֵ:  void
//		// ��������:protected static
//		// ������   ������յ�����Ϣ
//		//************************************
//		static void RecvData(char *addr, int port, wchar_t *buf, int size);
//
//		//************************************
//		// ������:  Network::Server::UserListToString
//		// ����:    void
//		// ����ֵ:  void
//		// ��������:protected static
//		// ������   ������յ�����Ϣ
//		//************************************
//		static std::wstring UserListToString(void);
//	
//#pragma endregion ������յ�����Ϣ
//
//		//************************************
//		// ������:  Network::Server::FeedbackThread
//		// ����:    void* pArguments	NULL
//		// ����ֵ:  unsigned
//		// ��������:protected static WINAPI
//		// ������   ��Ϣ�����߳�
//		//************************************
//		static unsigned WINAPI FeedbackThread(void* pArguments);
//
//		////************************************
//		//// ������:  Network::Server::GetIp
//		//// ����ֵ:  wchar_t*		����IP
//		//// ��������:protected static
//		//// ������   ���ڻ�ȡ����IP��ַ
//		////************************************
//		//static wchar_t* GetIp(void);
//
//
//	public:
//		
//		//************************************
//		// ������:  Network::Server::SendMsg
//		// ����1:   const wchar_t* dwIP		�Է�IP
//		// ����2:   const wchar_t* buf		��������
//		// ����ֵ:  ErrorCode
//		// ��������:public static
//		// ������   ������Ϣ
//		//************************************
//		static ErrorCode SendMsg(const char* dwIP, const wchar_t* buf);
//
//		//************************************
//		// ������:  Network::Server::Broadcast
//		// ����:    const wchar_t* msg		Ҫ���͵���Ϣ
//		// ����ֵ:  ErrorCode
//		// ��������:public static
//		// ������   �㲥��Ϣ
//		//************************************
//		static ErrorCode Broadcast(const wchar_t* msg);
//		
//		//************************************
//		// ������:  Network::Server::SetServerPort
//		// ����:    unsigned short port	�˿ں�
//		// ����ֵ:  void
//		// ��������:public
//		// ������   ���÷����������Ķ˿ں�
//		//************************************
//		void SetServerPort(unsigned short port);
//		
//		//************************************
//		// ������:  Network::Server::SetClientPort
//		// ����:    unsigned short port	�˿ں�
//		// ����ֵ:  void
//		// ��������:public
//		// ������   ���ÿͻ��˼����Ķ˿ں�
//		//************************************
//		void SetClientPort(unsigned short port);
//	
//	#pragma region IServerʵ��
//
//		//************************************
//		// ������:  Network::IServer::CreateGameRoom
//		// ����ֵ:  int
//		// ����:    int maxPlayerNumber					����������
//		// ����:    const std::wstring & gameRoomName		��Ϸ���������
//		// ��������:
//		// ������   ������Ϸ����
//		//************************************
//		virtual int CreateGameRoom( 
//			int maxPlayerNumber, 
//			const std::wstring& gameRoomName 
//			);
//
//		//************************************
//		// ������:  Network::IServer::CloseGameRoom
//		// ����ֵ:  int
//		// ����:    const std::wstring & gameRoomName		��Ϸ���������
//		// ��������:
//		// ������   �ر���Ϸ����
//		//************************************
//		virtual int CloseGameRoom(
//			const std::wstring& gameRoomName 
//			);
//
//		//************************************
//		// ������:  Network::IServer::Start
//		// ����ֵ:  int
//		// ��������:
//		// ������   ������Ϸ���䣬��ʼ���ܿͻ�������
//		//************************************
//		virtual int Start();
//
//		//************************************
//		// ������:  Network::IServer::Stop
//		// ����ֵ:  int
//		// ��������:
//		// ������   ֹͣ��Ϸ����
//		//************************************
//		virtual int Stop();
//
//	#pragma endregion IServerʵ��
//	};
//
//}