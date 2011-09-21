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
		if(server->m_gameing)					//游戏开始时的消息处理
		{
			switch(msg.GetCMD())
			{
			case CCMD_ExitGame:			//退出游戏
				{
					int index = *(int*)msg.Getdata(12);		//转换为整型 得到退出者的索引号

					if(server->m_playerIP[index] == SenderIP)		//判断是否合法信息
					{
						server->m_playerIP[index] = 0;				//删除玩家
					}
					else
					{
						break;			//非法信息 不处理
					}
					server->SendToMember(msg);				//通知其他玩家有玩家退出
					break;
				}
			case CMD_Winner:			//有人获胜
				{					
					server->SendToMember(msg);				//通知其他玩家游戏结束
					break;
				}

			default:		//无须处理的包 直接转发
				{
					server->SendToMember(msg);
					break;
				}
			}
		}
		else									//未开始
		{
			switch(msg.GetCMD())
			{
			case CCMD_RequestJion:		//请求加入主机
				{
					if (server->m_playCount == 4)	//服务器人满	不能加入
					{
						PACKAGE tempmsg;
						tempmsg.m_cmd = SCMD_ERRORRequestJion;
						Net::SendMessage(tempmsg, 3250, SenderIP);
						break;
					}

					//否则 可以加入
					int index = -1;
					for(int i = 0; i < 4; i++) //查看是否还有空位
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

					tempmsg.Setdata((char*)&parm, sizeof(OKRequestJion));	//发送索引和地图信息

					Net::SendMessage(tempmsg, 3250, SenderIP);

					tempmsg.m_cmd = SCMD_HostMember;
					HostMember member;
					for (int i = 0; i < 4; i++)				//发送已经在此host中的人的信息给新进的成员
					{
						if (0 != server->m_playerIP[i])		//如果此位置有人 则通知
						{
							member.index = i;
							memcpy( member.name, server->m_player[i], MyNameLength);
							tempmsg.Setdata((char*)&member, sizeof(HostMember));
							Net::SendMessage(tempmsg, 3250, SenderIP);
						}
					}

					server->m_playerIP[index] = SenderIP;		//将新进的成员信息加入到主机列表中
					memcpy( server->m_player[index], msg.Getdata(12), MyNameLength);

					//通知所有成员 新进成员的信息
					member.index = index;
					memcpy( member.name, server->m_player[index], MyNameLength);
					tempmsg.Setdata((char*)&member, sizeof(HostMember));
					server->SendToMember(tempmsg);

					server->m_playCount++;

					tempmsg.m_cmd = SCMD_HostCurrentNum;				//广播当前人数
					tempmsg.Setdata((char*) &server->m_playCount, sizeof(int));
					Net::SendMessage(tempmsg, 3250);

					break;
				}
			case CCMD_QueryHost:		//查询主机
				{
					PACKAGE tempmsg;
					tempmsg.m_cmd = SCMD_RQueryHost;
					tempmsg.Setdata((char*)&server->m_hostInfo, sizeof(CreateHostStruct));
					Net::SendMessage(tempmsg, 3250, SenderIP);			//回复主机查询

					tempmsg.m_cmd = SCMD_HostCurrentNum;				//回复当前人数
					tempmsg.Setdata((char*) &server->m_playCount, sizeof(int));
					Net::SendMessage(tempmsg, 3250, SenderIP);			//当前人数
					
					break;

				}
			case CCMD_ExitHost:			//退出主机
				{
					int index = *(int*)msg.Getdata(12);		//转换为整型 得到退出者的索引号

					if(server->m_playerIP[index] == SenderIP)		//判断是否合法信息
					{
						server->m_playerIP[index] = 0;				//删除玩家
						server->m_playCount--;
					}
					else
					{
						break;			//非法信息 不处理
					}

					server->SendToMember(msg);				//通知其他玩家有玩家退出

					PACKAGE tempmsg;
					tempmsg.m_cmd = SCMD_HostCurrentNum;		//广播当前人数
					tempmsg.Setdata((char*) &server->m_playCount, sizeof(int));
					Net::SendMessage(tempmsg, 3250);			//当前人数

					break;
				}			
			default:		//无须处理的包 直接转发
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
		if (NULL != m_network)		//释放资源
		{		
			m_network->Close();
			delete m_network;
			m_network = NULL;
		}
	}

	void CServer::CreateHost(const char * name, const char* mapName)	//创建主机
	{		
		memcpy(m_hostInfo.name, name, 20);
		memcpy(m_hostInfo.mapName, mapName, 30);

		m_network = Net::CreateNetWork();
		m_network->Run(OnMsgCome, 3251);		//服务器监听端口
		PACKAGE pack;
		pack.m_cmd = SCMD_CreatHost;
		//CreateHost parm;
		
		pack.Setdata((char*)&m_hostInfo, sizeof(CreateHostStruct));

		Net::SendMessage(pack);					//通知所有客户端

		g_Server = this;
	}
	void CServer::CancelHost()					//取消主机
	{
		m_network->Close();
		delete m_network;
		m_network = NULL;
		m_playCount = 0;

		PACKAGE pack;
		pack.m_cmd = SCMD_CancelHost;
		
		if (m_gameing)								//如果已经开始游戏
		{
			SendToMember(pack);						//仅通知所有玩家 主机退出
		}
		else
		{
			Net::SendMessage(pack);					//通知所有客户端
		}
		
	}

	bool CServer::BeignGame()
	{
		/*if (m_playCount < 2)	//如果玩家只有一个 不能开始有戏
		{
			return false;
		}*/
		m_gameing = true;
		PACKAGE pack;
		pack.m_cmd = SCMD_BeignGame;
		Net::SendMessage(pack);		//通知所有客户 游戏开始
									//这里广播是为了通知所有客户端更新主机列表

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
			if (0 != m_playerIP[i])				//如果此位置有人 则发送消息
			{
				Net::SendMessage(msg, 3250, m_playerIP[i]);
			}
		}
	}
}