#include "Server.h"

namespace  GameLogic
{

	CServer* CServer::g_Server = NULL;

	extern "C" IGAMELOGIC_API IServer* CreateLanServer()
	{
		return new CServer();
	}

	void OnMsgCome(unsigned long SenderIP, PACKAGE& msg)
	{
		CServer* server = CServer::g_Server;
		if(server->m_gameing)					//��Ϸ��ʼʱ����Ϣ����
		{
			switch(msg.GetCMD())
			{
			case CCMD_ExitGame:			//�˳���Ϸ
				{
					int index = *(int*)msg.Getdata(12);		//ת��Ϊ���� �õ��˳��ߵ�������

					if(server->m_playerIP[index] == SenderIP)		//�ж��Ƿ�Ϸ���Ϣ
					{
						server->m_playerIP[index] = 0;				//ɾ�����
					}
					else
					{
						break;			//�Ƿ���Ϣ ������
					}
					server->SendToMember(msg);				//֪ͨ�������������˳�
					break;
				}
			case CMD_Winner:			//���˻�ʤ
				{					
					server->SendToMember(msg);				//֪ͨ���������Ϸ����
					break;
				}

			default:		//���봦��İ� ֱ��ת��
				{
					server->SendToMember(msg);
					break;
				}
			}
		}
		else									//δ��ʼ
		{
			switch(msg.GetCMD())
			{
			case CCMD_RequestJion:		//�����������
				{
					if (server->m_playCount == 4)	//����������	���ܼ���
					{
						PACKAGE tempmsg;
						tempmsg.m_cmd = SCMD_ERRORRequestJion;
						Net::SendMessage(tempmsg, 3250, SenderIP);
						break;
					}

					//���� ���Լ���
					int index = -1;
					for(int i = 0; i < 4; i++) //�鿴�Ƿ��п�λ
					{
						if (0 == server->m_playerIP[i])
						{
							index = i;
							break;
						}
					}
				
					PACKAGE tempmsg;
					tempmsg.m_cmd = SCMD_OKRequestJion;
					OKRequestJion parm;
					parm.index = index;
					memcpy(parm.mapName, server->m_hostInfo.mapName, 30);

					tempmsg.Setdata((char*)&parm, sizeof(OKRequestJion));	//���������͵�ͼ��Ϣ

					Net::SendMessage(tempmsg, 3250, SenderIP);

					tempmsg.m_cmd = SCMD_HostMember;
					HostMember member;
					for (int i = 0; i < 4; i++)				//�����Ѿ��ڴ�host�е��˵���Ϣ���½��ĳ�Ա
					{
						if (0 != server->m_playerIP[i])		//�����λ������ ��֪ͨ
						{
							member.index = i;
							memcpy( member.name, server->m_player[i], MyNameLength);
							tempmsg.Setdata((char*)&member, sizeof(HostMember));
							Net::SendMessage(tempmsg, 3250, SenderIP);
						}
					}

					server->m_playerIP[index] = SenderIP;		//���½��ĳ�Ա��Ϣ���뵽�����б���
					memcpy( server->m_player[index], msg.Getdata(12), MyNameLength);

					//֪ͨ���г�Ա �½���Ա����Ϣ
					member.index = index;
					memcpy( member.name, server->m_player[index], MyNameLength);
					tempmsg.Setdata((char*)&member, sizeof(HostMember));
					server->SendToMember(tempmsg);

					server->m_playCount++;

					tempmsg.m_cmd = SCMD_HostCurrentNum;				//�㲥��ǰ����
					tempmsg.Setdata((char*) &server->m_playCount, sizeof(int));
					Net::SendMessage(tempmsg, 3250);

					break;
				}
			case CCMD_QueryHost:		//��ѯ����
				{
					PACKAGE tempmsg;
					tempmsg.m_cmd = SCMD_RQueryHost;
					tempmsg.Setdata((char*)&server->m_hostInfo, sizeof(CreateHostStruct));
					Net::SendMessage(tempmsg, 3250, SenderIP);			//�ظ�������ѯ

					tempmsg.m_cmd = SCMD_HostCurrentNum;				//�ظ���ǰ����
					tempmsg.Setdata((char*) &server->m_playCount, sizeof(int));
					Net::SendMessage(tempmsg, 3250, SenderIP);			//��ǰ����
					
					break;

				}
			case CCMD_ExitHost:			//�˳�����
				{
					int index = *(int*)msg.Getdata(12);		//ת��Ϊ���� �õ��˳��ߵ�������

					if(server->m_playerIP[index] == SenderIP)		//�ж��Ƿ�Ϸ���Ϣ
					{
						server->m_playerIP[index] = 0;				//ɾ�����
						server->m_playCount--;
					}
					else
					{
						break;			//�Ƿ���Ϣ ������
					}

					server->SendToMember(msg);				//֪ͨ�������������˳�

					PACKAGE tempmsg;
					tempmsg.m_cmd = SCMD_HostCurrentNum;		//�㲥��ǰ����
					tempmsg.Setdata((char*) &server->m_playCount, sizeof(int));
					Net::SendMessage(tempmsg, 3250);			//��ǰ����

					break;
				}			
			default:		//���봦��İ� ֱ��ת��
				{
					server->SendToMember(msg);
					break;
				}
			}
		}
	}

	CServer::CServer(void)
	{
		for (int i = 0; i < 4; i++)
		{
			m_playerIP[i] = 0;
		}
		m_gameing = false;
		m_playCount = 0;
	}

	CServer::~CServer(void)
	{
		if (NULL != m_network)		//�ͷ���Դ
		{		
			m_network->Close();
			delete m_network;
			m_network = NULL;
		}
	}

	void CServer::CreateHost(const char * name, const char* mapName)	//��������
	{		
		memcpy(m_hostInfo.name, name, 20);
		memcpy(m_hostInfo.mapName, mapName, 30);

		m_network = Net::CreateNetWork();
		m_network->Run(OnMsgCome, 3251);		//�����������˿�
		PACKAGE pack;
		pack.m_cmd = SCMD_CreatHost;
		//CreateHost parm;
		
		pack.Setdata((char*)&m_hostInfo, sizeof(CreateHostStruct));

		Net::SendMessage(pack);					//֪ͨ���пͻ���

		g_Server = this;
	}
	void CServer::CancelHost()					//ȡ������
	{
		m_network->Close();
		delete m_network;
		m_network = NULL;
		m_playCount = 0;

		PACKAGE pack;
		pack.m_cmd = SCMD_CancelHost;
		
		if (m_gameing)								//����Ѿ���ʼ��Ϸ
		{
			SendToMember(pack);						//��֪ͨ������� �����˳�
		}
		else
		{
			Net::SendMessage(pack);					//֪ͨ���пͻ���
		}
		
	}

	bool CServer::BeignGame()
	{
		/*if (m_playCount < 2)	//������ֻ��һ�� ���ܿ�ʼ��Ϸ
		{
			return false;
		}*/
		m_gameing = true;
		PACKAGE pack;
		pack.m_cmd = SCMD_BeignGame;
		Net::SendMessage(pack);		//֪ͨ���пͻ� ��Ϸ��ʼ
									//����㲥��Ϊ��֪ͨ���пͻ��˸��������б�

		return true;
	}

	int CServer::GetHostState()
	{
		return 0;
	}

	void CServer::SendToMember( PACKAGE& msg )
	{
		for(int i = 0; i < 4; i++)
		{
			if (0 != m_playerIP[i])				//�����λ������ ������Ϣ
			{
				Net::SendMessage(msg, 3250, m_playerIP[i]);
			}
		}
	}
}