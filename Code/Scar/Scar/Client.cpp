/********************************************************************
����ʱ��: 2011-10-22   15:00
�ļ���:   Server.h
����:     �´���
˵��:     �ͻ�������ʵ��

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


	// ���������߳�
	if (_beginthreadex(NULL, 0, &ListenThread, NULL, 0, 0) == -1)
	{
		closesocket(m_socket);
		MessageBox(NULL,_T("�߳�����ʧ��"),_T("����"),MB_OK);
	}
}


Client::~Client(void)
{
	closesocket(m_socket);
}


#pragma region ��̬���ݶ��弰��ʼ��

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

#pragma endregion ��̬���ݶ��弰��ʼ��

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
// ������:  Network::Client::SetID
// ����:    wstring name		�ͻ�����
// ����ֵ:  void
// ��������:public static
// ������   ���ÿͻ�����
//************************************
void Client::SetID(wstring name)
{
	if(name != L"")
	{
		m_ID = name;
	}
}

//************************************
// ������:  Network::Client::SetServerPort
// ����:    unsigned short port	�˿ں�
// ����ֵ:  void
// ��������:public
// ������   ���÷����������Ķ˿ں�
//************************************
void Client::SetServerPort(unsigned short port)
{
	m_serverPort = port;
}
		
//************************************
// ������:  Network::Client::SetClientPort
// ����:    unsigned short port	�˿ں�
// ����ֵ:  void
// ��������:public
// ������   ���ÿͻ��˼����Ķ˿ں�
//************************************
void Client::SetClientPort(unsigned short port)
{
	m_clientPort = port;
}

//************************************
// ������:  Network::Client::SendMsgToServer
// ����:    const wchar_t* buf		��������
// ����ֵ:  ErrorCode
// ��������:protected static
// ������   ������Ϣ��������
//************************************
ErrorCode Client::SendMsgToServer(const wchar_t* buf)
{
	int nSendSize = sendto(m_socket, (char*)buf, sizeof(wchar_t)*(wcslen(buf)+1), 0, (SOCKADDR *) &m_targetAddr, m_tolen);

	if (nSendSize == -1)
	{
		return ErrorCode::��Ϣ����ʧ��;
	}

	return ErrorCode::ACCEPT;
}

//************************************
// ������:  Network::Client::ListenThread
// ����:    void* pArguments	NULL
// ����ֵ:  unsigned
// ��������:protected WINAPI
// ������   �����߳�
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
// ������:  Network::Client::RecvData
// ����:    char *addr		��ַ
// ����:    int port		�˿ں�
// ����:    wchar_t *buf		��Ϣ
// ����:    int size		��С
// ����ֵ:  void
// ��������:protected static
// ������   ������յ�����Ϣ
//************************************
void Client::RecvData(char *addr, int port, wchar_t *buf, int size)
{
	static int i =0;
	//printf("%d\t�յ�%s\t%d\t%d\t%s\n", i++, addr, port, size, buf);


	wstring data = buf;
	int pos = data.find_first_of(L":");
	int pos2;
	if (pos == -1)
	{
		return;
	}

	wstring type = data.substr(0, pos);
	wstring result;

	if (type == L"scene")			// �������
	{
#pragma region �������
		// ���� scene:������Ϣ
		if (m_isStart)
		{
			// �ص�
			callback(buf);
			// ��������
			//printf("�������:%s\n", buf);
		}
#pragma endregion �������
	}
	else if (type == L"room")	// ������Ϣ
	{
#pragma region ���ҷ�������󷿼���Ϣ
		// �������� room:setup;info{name:������;maxNumber:����û�����;nowNumber:��ǰ�û���;start:�Ƿ�ʼ��Ϸ};
		// �رշ��� room:close;
		// ��Ϣ room:info{name:������;maxNumber:��������;nowNumber:��ǰ�����;start:�Ƿ�ʼ��Ϸ};
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
#pragma endregion ���ҷ�������󷿼���Ϣ
	}
	else if (type == L"join")	// �������Ӧ��
	{
#pragma region �������Ӧ��
		// ���� join:yes;userlist:{�û���:�û���ַ;�û���:�û���ַ;�û���:�û���ַ}	��	join:no;
		if (data[pos+1] == 'y')
		{
			m_isJoinRoom = 1;
		}
		else
		{
			m_isJoinRoom = -1;
		}


#pragma endregion �������Ӧ��
	}
	else if (type == L"game")	// ��Ϸ��ʼ��ر�
	{
#pragma region ��Ϸ��ʼ��ر�
		// ��Ϸ��ʼ game:start;
		// ��Ϸ���� game:stop;
		// ����
#pragma endregion ��Ϸ��ʼ��ر�
	}
	else if (type == L"userlist")	// �û��б�
	{
#pragma region �û��б�
		// userlist:{�û���:�û���ַ;�û���:�û���ַ;�û���:�û���ַ}
		// �����û��б�
#pragma endregion �����û��б�
	}
	else if (type == L"result")// ��Ϸ���
	{
	}
	else
	{
		// �ص�
		callback(buf);
		return;
	}
}

//************************************
// ������:  Network::Client::FeedbackThread
// ����:    void* pArguments	NULL
// ����ֵ:  unsigned
// ��������:protected static WINAPI
// ������   ��Ϣ�����߳�
//************************************
unsigned WINAPI Client::FeedbackThread(void* pArguments)
{
	// �Ѽ��뷿��
	while(m_isJoinRoom)
	{
		// ��Ϸ������
		if (m_isStart)
		{
			// �ύ��Ϸ�������
			SendMsgToServer(m_Scene.c_str());
		}

		Sleep(1);
	}
	return 0;
}


//************************************
// ������:  IClient::SearchGameRoom
// ����ֵ:  ServerInfoList
// ��������:
// ������   ���ҵ�ǰ�������ķ��������������ݶ��˿ں�Ϊ 54321
//************************************
ServerInfoList Client::SearchGameRoom()
{
	m_serverList.clear();
	// �㲥Socket
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
	
	// �ȴ���������Ϣ����
	while (m_isSearch)
	{
		Sleep(1);
	}

	return m_serverList;
}

//************************************
// ������:  IClient::EnterGameRoom
// ����ֵ:  int
// ����:    const std::wstring & ip
// ��������:
// ������   ���������
//************************************
int Client::EnterGameRoom( const std::wstring& ip )
{
	m_isJoinRoom = 0;
	// ���� join?{name:�����}";

	size_t len = wcslen(ip.c_str()) + 1;   
	size_t converted = 0;   
	char *CStr;   
	CStr=(char*)malloc(len*sizeof(char));   
	wcstombs_s(&converted, CStr, len, ip.c_str(), _TRUNCATE);  

	m_targetAddr.sin_addr.S_un.S_addr = inet_addr(CStr);
	SendMsgToServer((L"join?{name:" + m_ID + L"}").c_str());

	time_t t_start;
	t_start = time(NULL);

	// �ȴ���������Ϣ����
	while (!m_isJoinRoom)
	{
		// ��ʱ�˳�
		if (time(NULL) - t_start > m_overtime)
		{
			return 0;
		}
		Sleep(1);
	}

	// ����ɹ�
	if (m_isJoinRoom == 1)
	{
		// ������Ϣ�����߳�
		if (_beginthreadex(NULL, 0, &FeedbackThread, NULL, 0, 0) == -1)
		{
			return 0;
			MessageBox(NULL,_T("�߳�����ʧ��"),_T("����"),MB_OK);
		}
	}
	
	return m_isJoinRoom;
}

//************************************
// ������:  IClient::LeaveGameRoom
// ����ֵ:  int
// ����:    const std::wstring & ip
// ��������:
// ������   �˳�������
//************************************
int Client::LeaveGameRoom( const std::wstring& ip )
{
	SendMsgToServer(L"leave");
	m_isJoinRoom = 0;
	return 0;
}

//************************************
// ������:  IClient::SetOnMsgCallbackFunc
// ����ֵ:  void
// ����:    IClientOnMsgCallbackFuncType func
// ��������:
// ������   ������Ϣ����ʱ�Ļص���������ÿ���ڿͻ�����Ϣ����ʱ���ͻ��˶�Ӧ����
//			�˺������õĻص�������������Ϣ��
//************************************
void Client::SetOnMsgCallbackFunc( IClientOnMsgCallbackFuncType func )
{
	if(func != NULL)
	{
		callback = func;
	}
}
