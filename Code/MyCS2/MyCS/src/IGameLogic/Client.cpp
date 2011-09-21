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
		if (NULL == client->m_OnMsgCome)		//�����Ϣ����ΪNULL ���˳�
		{
			return;
		}

		if(client->IsJionHost())		//������������ 
		{
#ifndef Home
			if (SenderIP == client->m_HostIP)	//ֻ������������Ϣ
			{
#endif
				switch(msg.GetCMD())
				{
				case SCMD_HostMember:				//������Ա
					{					
						HostMember meb;
						memcpy((char*)&meb, msg.Getdata(12), sizeof(HostMember));
						memcpy(client->m_playerName[meb.index], meb.name, MyNameLength);
						client->m_OnMsgCome(SenderIP, msg);								//����UI����
						client->m_isNull[meb.index] = true;	//��ʾ����
						break;
					}
				case CCMD_ExitGame:				//����˳�
				case CCMD_ExitHost:				
					{					
						int index = *(int*)msg.Getdata(12);						
						client->m_OnMsgCome(SenderIP, msg);					//����UI����
						client->m_isNull[index] = false;					//��ʾû��
						break;
					}				
				default:
					{					
						client->m_OnMsgCome(SenderIP, msg);	//����UI����
						break;
					}

				}
#ifndef Home
			}
			else	//�����ܷ�������Ϣ
			{
				return;
			}
#endif
		}
		else
		{
			switch(msg.GetCMD())
			{
			case SCMD_ERRORRequestJion:			//��������ʧ��
				{
					client->m_isJionOK = 0;
					break;
				}
			case SCMD_OKRequestJion:			//���������ɹ�
				{
					client->m_isJionOK = 1;
					client->m_myIndex = *((int*)msg.Getdata(12));
					memcpy(client->m_mapName,msg.Getdata(16),30);
					break;
				}		
			default:
				{					
					client->m_OnMsgCome(SenderIP, msg);	//����UI����
					break;
				}

			}
		}
	}

	CClient::CClient(void)
	{
		m_isJionOK = -1;
		m_network = Net::CreateNetWork();
		m_network->Run(OnCMsgCome);			//����		

	}

	CClient::~CClient(void)
	{
		if (m_network != NULL)			//�ͷ���Դ
		{
			m_network->Close();
			delete m_network;
		}
	}

	bool CClient::JionHost( unsigned long serverIP, const char* name)
	{
		for(int i = 0; i < 4; i++)
		{
			m_isNull[i] = false;				//��ʾû��
		}
		m_HostIP = serverIP;
		
		m_package.m_cmd = CCMD_RequestJion;
		m_package.Setdata(name,sizeof(RequestJion));

		Net::SendMessage(m_package, 3251, serverIP);	//��������

		int count = 0;

		//��������߳� �ȴ���������Ӧ��Ϣ
		//�������ɹ� OnCMsgCome �߳̽��޸�m_isJionOK��ֵ
		while (-1 == m_isJionOK)
		{
			count++;
			if (count > 20)	//��ֹ����������� 4��
			{
				return false;
			}
			Sleep(200);
		}
		return m_isJionOK;
	}

	void CClient::SendMsg( PACKAGE& msg )		//�������������Ϣ
	{
		Net::SendMessage(msg, 3251, m_HostIP);	//��������
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
		Net::SendMessage(m_package, 3251, m_HostIP);	//��������
	}

	void CClient::ExitGame()
	{
		m_isJionOK = -1;
		m_HostIP = 0;

		m_package.m_cmd = CCMD_ExitGame;
		m_package.Setdata((char*)&m_myIndex, sizeof(int));
		Net::SendMessage(m_package, 3251, m_HostIP);	//��������
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
		Net::SendMessage(m_package, 3251);	//��������
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