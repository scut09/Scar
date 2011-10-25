/********************************************************************
����ʱ��: 2011-10-22   15:00
�ļ���:   Server.h
����:     �´���
˵��:     �ͻ�������ʵ��

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
		
#pragma region ��̬��Ա����

		// ������ʱʱ��(����)
		static int m_overtime;

		// �ͻ���ID
		static wstring m_ID;

		// ��������������
		static bool m_isSearch;

		// ��������������
		static int m_isJoinRoom;

		// �������б�
		static ServerInfoList m_serverList;

		// ��Ϸ�Ƿ�����
		static bool m_isStart;
		
		// client�б�
		static vector<clientInfo> m_clientList;

		// �����Socket�󶨵Ķ˿ں�
		static unsigned short m_serverPort;

		// �ͻ���Socket�󶨵Ķ˿ں�
		static unsigned short m_clientPort;

		// ����Socket
		static SOCKET m_socket;
		static SOCKADDR_IN m_targetAddr;

		// ��������С
		static const int m_bufferLength;

		// SOCKADDR_IN��С
		static const int m_tolen;

		// ��Ϸ����
		static wstring m_Scene;

	#pragma endregion ��̬��Ա����

	protected:
		
		//************************************
		// ������:  Network::Client::ListenThread
		// ����:    void* pArguments	NULL
		// ����ֵ:  unsigned
		// ��������:protected static WINAPI
		// ������   �����߳�
		//************************************
		static unsigned WINAPI ListenThread(void* pArguments);

		//************************************
		// ������:  Network::Client::RecvData
		// ����:    char *addr		��ַ
		// ����:    int port		�˿ں�
		// ����:    wchar_t *buf		��Ϣ
		// ����:    int size		��С
		// ����ֵ:  void
		// ��������:protected static
		// ������   ������յ�����Ϣ
		//************************************
		static void RecvData(char *addr, int port, wchar_t *buf, int size);
	
		//************************************
		// ������:  Network::Client::FeedbackThread
		// ����:    void* pArguments	NULL
		// ����ֵ:  unsigned
		// ��������:protected static WINAPI
		// ������   ��Ϣ�����߳�
		//************************************
		static unsigned WINAPI FeedbackThread(void* pArguments);

	public:

		char* ConvertLPWSTRToLPSTR (LPWSTR lpwszStrIn);
		
		//************************************
		// ������:  Network::Client::SetID
		// ����:    wstring name		�ͻ�����
		// ����ֵ:  void
		// ��������:public static
		// ������   ���ÿͻ�����
		//************************************
		static void SetID(wstring name);
		
		//************************************
		// ������:  Network::Client::SendMsgToServer
		// ����:    const wchar_t* buf		��������
		// ����ֵ:  ErrorCode
		// ��������:public static
		// ������   ������Ϣ��������
		//************************************
		static ErrorCode SendMsgToServer(const wchar_t* buf);

		//************************************
		// ������:  Network::Client::SetServerPort
		// ����:    unsigned short port	�˿ں�
		// ����ֵ:  void
		// ��������:public
		// ������   ���÷����������Ķ˿ں�
		//************************************
		void SetServerPort(unsigned short port);
		
		//************************************
		// ������:  Network::Client::SetClientPort
		// ����:    unsigned short port	�˿ں�
		// ����ֵ:  void
		// ��������:public
		// ������   ���ÿͻ��˼����Ķ˿ں�
		//************************************
		void SetClientPort(unsigned short port);

	#pragma region IClientʵ��

		static IClientOnMsgCallbackFuncType callback;

		//************************************
		// ������:  IClient::SearchGameRoom
		// ����ֵ:  ServerInfoList
		// ��������:
		// ������   ���ҵ�ǰ�������ķ��������������ݶ��˿ں�Ϊ 54321
		//************************************
		virtual ServerInfoList SearchGameRoom();

		//************************************
		// ������:  IClient::EnterGameRoom
		// ����ֵ:  int
		// ����:    const std::wstring & ip
		// ��������:
		// ������   ���������
		//************************************
		virtual int EnterGameRoom( const std::wstring& ip );

		//************************************
		// ������:  IClient::LeaveGameRoom
		// ����ֵ:  int
		// ����:    const std::wstring & ip
		// ��������:
		// ������   �˳�������
		//************************************
		virtual int LeaveGameRoom( const std::wstring& ip );

		//************************************
		// ������:  IClient::SetOnMsgCallbackFunc
		// ����ֵ:  void
		// ����:    IClientOnMsgCallbackFuncType func
		// ��������:
		// ������   ������Ϣ����ʱ�Ļص���������ÿ���ڿͻ�����Ϣ����ʱ���ͻ��˶�Ӧ����
		//			�˺������õĻص�������������Ϣ��
		//************************************
		virtual void SetOnMsgCallbackFunc( IClientOnMsgCallbackFuncType func );
	#pragma endregion IClientʵ��

	};

}