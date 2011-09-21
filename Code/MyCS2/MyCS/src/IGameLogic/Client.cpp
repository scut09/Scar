#include "Client.h"
#define Home
namespace GameLogic
{
	CClient*	CClient::g_Client = NULL;
	int			CClient::m_isJionOK = -1;
	extern "C" IGAMELOGIC_API IClient* CreateLanClient(OnMsgComeEvent OnMsgCome)
	{
		CClient* Client = new CClient();
		CClient::g_Client = Client;
		Client->m_OnMsgCome = OnMsgCome;
		return Client;
	}


	void OnCMsgCome(unsigned long SenderIP, PACKAGE& msg)
	{		
		CClient* client = CClient::g_Client;
		if (NULL == client->m_OnMsgCome)		//如果消息函数为NULL 则退出
		{
			return;
		}

		if(client->IsJionHost())		//当加入主机后 
		{
#ifndef Home
			if (SenderIP == client->m_HostIP)	//只接受主机的消息
			{
#endif
				switch(msg.GetCMD())
				{
				case SCMD_HostMember:				//主机成员
					{					
						HostMember meb;
						memcpy((char*)&meb, msg.Getdata(12), sizeof(HostMember));
						memcpy(client->m_playerName[meb.index], meb.name, MyNameLength);
						client->m_OnMsgCome(SenderIP, msg);								//交给UI处理
						client->m_isNull[meb.index] = true;	//表示有人
						break;
					}
				case CCMD_ExitGame:				//玩家退出
				case CCMD_ExitHost:				
					{					
						int index = *(int*)msg.Getdata(12);						
						client->m_OnMsgCome(SenderIP, msg);					//交给UI处理
						client->m_isNull[index] = false;					//表示没人
						break;
					}				
				default:
					{					
						client->m_OnMsgCome(SenderIP, msg);	//交给UI处理
						break;
					}

				}
#ifndef Home
			}
			else	//不接受非主机消息
			{
				return;
			}
#endif
		}
		else
		{
			switch(msg.GetCMD())
			{
			case SCMD_ERRORRequestJion:			//加入主机失败
				{
					client->m_isJionOK = 0;
					break;
				}
			case SCMD_OKRequestJion:			//加入主机成功
				{
					client->m_isJionOK = 1;
					client->m_myIndex = *((int*)msg.Getdata(12));
					memcpy(client->m_mapName,msg.Getdata(16),30);
					break;
				}		
			default:
				{					
					client->m_OnMsgCome(SenderIP, msg);	//交给UI处理
					break;
				}

			}
		}
	}

	CClient::CClient(void)
	{
		m_isJionOK = -1;
		m_network = Net::CreateNetWork();
		m_network->Run(OnCMsgCome);			//监听		

	}

	CClient::~CClient(void)
	{
		if (m_network != NULL)			//释放资源
		{
			m_network->Close();
			delete m_network;
		}
	}

	bool CClient::JionHost( unsigned long serverIP, const char* name)
	{
		for(int i = 0; i < 4; i++)
		{
			m_isNull[i] = false;				//表示没人
		}
		m_HostIP = serverIP;
		
		m_package.m_cmd = CCMD_RequestJion;
		m_package.Setdata(name,sizeof(RequestJion));

		Net::SendMessage(m_package, 3251, serverIP);	//发送请求

		int count = 0;

		//这里挂起线程 等待服务器响应消息
		//如果加入成功 OnCMsgCome 线程将修改m_isJionOK的值
		while (-1 == m_isJionOK)
		{
			count++;
			if (count > 20)	//防止丢包后的死锁 4秒
			{
				return false;
			}
			Sleep(200);
		}
		return m_isJionOK;
	}

	void CClient::SendMsg( PACKAGE& msg )		//向服务器发送消息
	{
		Net::SendMessage(msg, 3251, m_HostIP);	//发送请求
	}

	void CClient::SetMsgComeEvent( OnMsgComeEvent OnMsgCome )
	{
		m_OnMsgCome = OnMsgCome;
	}

	bool CClient::IsJionHost()
	{
		if (m_isJionOK != 1)
		{
			return false;
		}
		return true;
	}

	void CClient::ExitHost()
	{
		m_isJionOK = -1;
		m_HostIP = 0;
		m_package.m_cmd = CCMD_ExitHost;
		m_package.Setdata((char*)&m_myIndex, sizeof(int));
		Net::SendMessage(m_package, 3251, m_HostIP);	//发送请求
	}

	void CClient::ExitGame()
	{
		m_isJionOK = -1;
		m_HostIP = 0;

		m_package.m_cmd = CCMD_ExitGame;
		m_package.Setdata((char*)&m_myIndex, sizeof(int));
		Net::SendMessage(m_package, 3251, m_HostIP);	//发送请求
	}

	int CClient::GetIndex()
	{
		return m_myIndex;
	}

	const char* CClient::GetName( int index )
	{
		return m_playerName[index];
	}

	void CClient::ReSet()
	{
		m_isJionOK = -1;
		m_HostIP = 0;
	}

	void CClient::QueryHost()
	{		
		m_package.m_cmd = CCMD_QueryHost;
		Net::SendMessage(m_package, 3251);	//发送请求
	}

	bool CClient::IsSet( int index )
	{
		return m_isNull[index];
	}

	void CClient::BeExit()
	{
		m_isJionOK = -1;
		m_HostIP = 0;
	}

	const char* CClient::GetMapName()
	{
		return m_mapName;
	}
}