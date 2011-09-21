#include "NetWork.h"

namespace Net
{

	in_addr		CNetWork::g_Localaddr;				//本机地址
	in_addr		CNetWork::g_Broadcastaddr;			//广播地址
	SOCKET		CNetWork::g_SendSocket = 0;				//发送数据的Socket

	//发送数据
	extern "C" INETWORK_API bool SendMessage_char( PACKAGE& msg, int port /*= 3250*/, const char* RecverIP /*= NULL*/ )	
	{
		if (0 == CNetWork::g_SendSocket)
		{			
			CNetWork::InitWinSokcet();
		}

		SOCKADDR_IN addrSrv;
		if(NULL == RecverIP)
		{
			addrSrv.sin_addr = CNetWork::g_Broadcastaddr;
		}
		else
		{
			addrSrv.sin_addr.S_un.S_addr=inet_addr(RecverIP);
		}

		addrSrv.sin_family=AF_INET;
		addrSrv.sin_port=htons(port);

		int len = sendto(CNetWork::g_SendSocket, msg.Getdata(0), msg.GetLength(), 0,
			(SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
		return true;
	}

	//发送数据
	extern "C" INETWORK_API bool SendMessage( PACKAGE& msg, int port /*= 3250*/, unsigned long RecverIP /*= NULL*/ )	
	{
		if (0 == CNetWork::g_SendSocket)
		{
			CNetWork::InitWinSokcet();
		}

		SOCKADDR_IN addrSrv;
		if(0 == RecverIP)
		{
			addrSrv.sin_addr = CNetWork::g_Broadcastaddr;
		}
		else
		{
			addrSrv.sin_addr.S_un.S_addr= RecverIP;
		}

		addrSrv.sin_family=AF_INET;
		addrSrv.sin_port=htons(port);

		int len = sendto(CNetWork::g_SendSocket, msg.Getdata(0), msg.GetLength(), 0,
			(SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
		return true;
	}
	
	extern "C" INETWORK_API INetWork* CreateNetWork()
	{
		return (INetWork*)new CNetWork();
	}

	extern "C" INETWORK_API unsigned long GetIP_long()
	{
		return CNetWork::g_Localaddr.S_un.S_addr;
	}

	extern "C" INETWORK_API in_addr GetIP_Addr()
	{
		return CNetWork::g_Localaddr;
	}

	DWORD WINAPI ThreadProc(LPVOID lpParameter)		//接收数据包线程函数
	{
		ThreadParam* param = (ThreadParam*) lpParameter;
		SOCKET s = param->m_s;
		OnMsgComeEvent callback =  param->m_fun;
			
		delete param;
		
		PACKAGE package;

		SOCKADDR_IN addrClient;
		int len=sizeof(SOCKADDR);

		int revlength = 0;
		int length;
		
		int recvlen = 0;

		while (true)
		{
			int recvlen = recvfrom(s, package.Getdata(0),sizeof(PACKAGE), 0, (SOCKADDR*)&addrClient, &len);	//接收包中的前四个字节 得到包长度		
			
			if (recvlen == package.GetLength())		//接收到一个包	UDP不会粘包
			{
				callback(addrClient.sin_addr.S_un.S_addr, package);
			}
		}
		return 0;
	}

	CNetWork::CNetWork(void)
	{
		
	}

	CNetWork::~CNetWork(void)
	{
		//--------------------------
		//des:这里要杀死线程
		//--------------------------
		TerminateThread(m_hThread, 0);

		closesocket(m_ListenSocket);
		
		
	}

	void CNetWork::Run( OnMsgComeEvent OnMsgCome , int port /*= 3250*/)
	{
		m_port = port;

		InitSocket(port);

 		m_callBack = OnMsgCome;
 
		ThreadParam* param = new ThreadParam();
		param->m_s = m_ListenSocket;
		param->m_fun = m_callBack;
		m_hThread = CreateThread(NULL,0,ThreadProc,(LPVOID)param,0,NULL);
	}

	bool CNetWork::InitSocket(int port)		//初始化套接字
	{
		m_ListenSocket = socket(AF_INET,SOCK_DGRAM,0);
		SOCKADDR_IN addrSrv;
		addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
		addrSrv.sin_family = AF_INET;
		addrSrv.sin_port = htons(port);

		if (bind(m_ListenSocket,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR)) != 0)
		{
			MessageBox(0,L"网络监听失败，可能是端口已被其他程序占用！\n请确定你没有开启多个客户端",L"提示",0);
		}		

		return true;
	}

	bool CNetWork::InitWinSokcet()
	{
		CNetWork::g_SendSocket = socket(AF_INET,SOCK_DGRAM,0);

		//计算广播地址
		char host_name[255];
		//获取本地主机名称  
		if (gethostname(host_name, sizeof(host_name)) == SOCKET_ERROR)
		{
			//throw "无法获得主机名.\n";
			return false;
		}			

		//从主机名数据库中得到对应的“主机”  
		struct hostent *phe = gethostbyname(host_name);
		if (NULL == phe) 
		{
			//throw "没有IP信息.";
			return false;
		}
		//本地机器IP地址		
		memcpy(&CNetWork::g_Broadcastaddr, phe->h_addr_list[0], sizeof(struct in_addr));			

		CNetWork::g_Localaddr = CNetWork::g_Broadcastaddr;
		CNetWork::g_Broadcastaddr.S_un.S_un_b.s_b4 = 255;
		
		return true;
	}

	void CNetWork::Close()
	{
		TerminateThread(m_hThread, 0);		//这里应先关闭接收线程 在关闭套接字 不然会有问题
		closesocket( m_ListenSocket);
		
	}
}