#include "SelectGame.h"

CSelectGame* CSelectGame::g_selectGame = NULL;

#define BTN_CREAT	0
#define BTN_JION	1
#define BTN_CANCEL	2
#define BTN_OK		3
#define BTN_SEND	4

void MsgCome(unsigned long SenderIP, PACKAGE& msg)
{
	switch(msg.m_cmd)
	{
	case CMD_GameChat:		//聊天消息
			{
				GameChat chatmsg;
				CHelper::CopyChar((char*)&chatmsg, sizeof(GameChat), msg.Getdata(12));
				std::string str = CSelectGame::m_client->GetName(chatmsg.index);
				str +=" : ";
				str += chatmsg.msg;

				wchar_t* buffer = CHelper::char_to_wchar(str.c_str());
				CSelectGame::g_selectGame->m_lbMsg->addItem(buffer, 4);
				delete[] buffer;
				if(CSelectGame::g_selectGame->m_lbMsg->getItemCount() > 40)	//超过一定数据是删除
				{
					CSelectGame::g_selectGame->m_lbMsg->removeItem(0);
				}
				CSelectGame::g_selectGame->m_lbMsg->setSelected(
					CSelectGame::g_selectGame->m_lbMsg->getItemCount());
				break;
			}
	case CMD_GlobeChat:		//全局聊天消息
		{
			GlobeChat chatmsg;
			CHelper::CopyChar((char*)&chatmsg, sizeof(GlobeChat), msg.Getdata(12));
			std::string str = chatmsg.name;
			str +=" : ";
			str += chatmsg.msg;

			wchar_t* buffer = CHelper::char_to_wchar(str.c_str());
			CSelectGame::g_selectGame->m_lbMsg->addItem(buffer, 3);
			delete[] buffer;
			if(CSelectGame::g_selectGame->m_lbMsg->getItemCount() > 40)	//超过一定数据是删除
			{
				CSelectGame::g_selectGame->m_lbMsg->removeItem(0);
			}
			CSelectGame::g_selectGame->m_lbMsg->setSelected(
				CSelectGame::g_selectGame->m_lbMsg->getItemCount());
			break;
		}
	case SCMD_CreatHost:		//有host 被创建
		{
			if (SenderIP == Net::GetIP_long())		//如果是自己建立的主机 不添加到列表
			{
				break;
			}
			std::string name = "(1/4)   ";
			CreateHostStruct* parm = (CreateHostStruct*)msg.Getdata(12);
			name += parm->name;
			name += "    map: ";
			name += parm->mapName;
			wchar_t* buffer = CHelper::char_to_wchar(name.c_str());

			CSelectGame::g_selectGame->m_HostList.push_back(SenderIP);

			CSelectGame::g_selectGame->m_lbHostList->addItem(buffer);
			delete[] buffer;
			break;
		}
	case SCMD_RQueryHost:		//查询到有host创建
		{
			if (SenderIP == Net::GetIP_long())		//如果是自己建立的主机 不添加到列表
			{
				break;
			}
			std::string name = "(1/4)   ";
			CreateHostStruct* parm = (CreateHostStruct*)msg.Getdata(12);
			name += parm->name;
			name += "    map: ";
			name += parm->mapName;
			wchar_t* buffer = CHelper::char_to_wchar(name.c_str());

			CSelectGame::g_selectGame->m_HostList.push_back(SenderIP);

			CSelectGame::g_selectGame->m_lbHostList->addItem(buffer);
			delete[] buffer;
			break;
		}
	case SCMD_BeignGame:		//游戏开始
		{
			if (CSelectGame::g_selectGame->m_client->IsJionHost())		//如果有加入主机 则准备开始游戏 否则删除主机列表
			{			
				CSelectGame::g_selectGame->m_isGoing = true;		//这里是线程 不能进行资源加载 不然会出错
				//所以资源加载放到主线程中去
				break;
			}
		}
	case SCMD_CancelHost:		//取消host
		{
			if( CSelectGame::g_selectGame->m_HostList.empty())
			{
				break;	//如果空 则退出
			}
			if (SenderIP == Net::GetIP_long())
			{
				break;	//如果是自己的主机取消 不处理
			}
			if (CSelectGame::g_selectGame->m_client->IsJionHost())
			{
				CSelectGame::g_selectGame->m_lbPlayerList->setItem(0, L"Open", 3);
				CSelectGame::g_selectGame->m_lbPlayerList->setItem(1, L"Open", 3);
				CSelectGame::g_selectGame->m_lbPlayerList->setItem(2, L"Open", 3);
				CSelectGame::g_selectGame->m_lbPlayerList->setItem(3, L"Open", 3);
				CSelectGame::g_selectGame->m_client->BeExit();
				CSelectGame::g_selectGame->m_client->QueryHost();
				CSelectGame::g_selectGame->m_UIState = 2;
			}

			int	index = 0;		//获得索引
			list<unsigned long>::Iterator it = CSelectGame::g_selectGame->m_HostList.begin();
			while (true)
			{				
				if ((unsigned long)(*it) == SenderIP)
				{
					break;
				}
				else
				{
					index++;
					it++;
					if (it == CSelectGame::g_selectGame->m_HostList.end())		//未找到列表
					{
						return;
					}					
				}
			}
			CSelectGame::g_selectGame->m_HostList.erase(it);			//删除映射
			CSelectGame::g_selectGame->m_lbHostList->removeItem(index);
			
			break;
		}
	case SCMD_HostMember:		//主机成员
		{
			HostMember meb;
			CHelper::CopyChar((char*)&meb, sizeof(HostMember), msg.Getdata(12));
			wchar_t* name = CHelper::char_to_wchar(meb.name);
			CSelectGame::g_selectGame->m_lbPlayerList->setItem(meb.index, name, 3);		//将成员添加到列表中
			delete[]  name;
			break;
		}
	case CCMD_ExitHost:			//成员退出
		{
			int index = * (int*) msg.Getdata(12);		
			CSelectGame::g_selectGame->m_lbPlayerList->setItem(index, L"Open", 3);		//将成员添加到列表中			
			break;
		}
	case SCMD_HostCurrentNum:	//主机玩家数目
		{
			if( CSelectGame::g_selectGame->m_HostList.empty())
			{
				break;	//如果空 则退出
			}
			if (CSelectGame::g_selectGame->m_client->IsJionHost())
			{
				break;
			}

			int	index = 0;			//获得索引
			list<unsigned long>::Iterator it = CSelectGame::g_selectGame->m_HostList.begin();
			while (true)
			{
				if ((unsigned long)(*it) == SenderIP)
				{
					break;
				}
				else
				{		
					index++;
					it++;
					if (it == CSelectGame::g_selectGame->m_HostList.end())
					{
						return;
					}
					
				}
			}
			wchar_t* str = (wchar_t*) CSelectGame::g_selectGame->m_lbHostList->getListItem(index);
			char num[2];
			int count = *(int*)msg.Getdata(12);
			itoa(count, num, 10);
			str[1] = num[0];			//人数修改
			break;
		}	

	}
}

CSelectGame::CSelectGame(void)
{
	CSelectGame::g_selectGame = this;	
}

CSelectGame::~CSelectGame(void)
{
	Release();
}

void CSelectGame::InitUI()
{
	
	m_isGoing = false;
	CSelectGame::g_selectGame = this;

	m_guienv->addImage(m_driver->getTexture("image\\box.jpg"), core::position2d<s32>(0,0) );
	
	m_y = -460;
	m_windows = m_guienv->addWindow(core::rect<s32>(10, m_y, 600,100), false, L"Host List");
	m_windows->getCloseButton()->setVisible(false);	
	m_windows->setDraggable(false);


	m_selectMap = m_guienv->addWindow(core::rect<s32>(10, -560, 600,0), false, L"Select Map");
	m_selectMap->getCloseButton()->setVisible(false);	
	m_selectMap->setDraggable(false);
	m_selectList = m_guienv->addListBox(core::rect<s32>(10, 25, 580,550), m_selectMap);
	m_selectList->setDrawBackground(true);
	m_selectList->addItem(L"Icworld");
	m_selectList->addItem(L"Icworld2");
	m_selectList->addItem(L"Round");


	m_hostY = -560;
	m_winHost = m_guienv->addWindow(core::rect<s32>(10, m_hostY, 600, 0), false, L"Player List");
	m_winHost->getCloseButton()->setVisible(false);
	m_winHost->setDraggable(false);

	m_infoWin = m_guienv->addWindow(core::rect<s32>(620, m_y, 950,100), false, L"Message Box");	
	m_infoWin->getCloseButton()->setVisible(false);	
	m_infoWin->setDraggable(false);

	m_btnCreate = AddBtn(250, 650, L"Crate", BTN_CREAT);
	m_btnJion = AddBtn(450, 650, L"Jion", BTN_JION);
	m_btnCancel = AddBtn(850, 650, L"Cancel", BTN_CANCEL);
	m_btnGo	= AddBtn(450, 650, L"OK", BTN_OK);
	

	m_tbSend = m_guienv->addEditBox(NULL,core::rect<s32>(10, 520, 320,550), true, m_infoWin);
	m_tbSend->setMax(30);

	m_lbMsg = m_guienv->addListBox(core::rect<s32>(10, 25, 320,510), m_infoWin);
	m_lbMsg->addItem(L"Welcome to the Game.");
	m_lbMsg->setDrawBackground(true);

	m_lbHostList = m_guienv->addListBox(core::rect<s32>(10, 25, 580,550), m_windows);
	m_lbHostList->setDrawBackground(true);

	m_lbPlayerList = m_guienv->addListBox(core::rect<s32>(10, 25, 580,550), m_winHost);
	m_lbPlayerList->setDrawBackground(true);
	m_lbPlayerList->addItem(L"Open", 3);
	m_lbPlayerList->addItem(L"Open", 3);
	m_lbPlayerList->addItem(L"Open", 3);
	m_lbPlayerList->addItem(L"Open", 3);

	m_lbPlayerList->setItemHeight(50);


	m_btnCreate->setVisible(false);
	m_btnJion->setVisible(false);
	m_btnCancel->setVisible(false);
	m_btnGo->setVisible(false);

	m_addBtn = false;
	m_UIState = 0;

	if(NULL == m_client)		//如果客户端为NULL 则new一个
	{
		m_client = GameLogic::CreateLanClient(MsgCome);
	}
	else						//否则修改客户端的消息函数地址
	{
		m_client->SetMsgComeEvent(MsgCome);
	}	
	m_client->QueryHost();		//查询主机
	
}

void CSelectGame::Release()
{
	m_guienv->clear();
}

void CSelectGame::DoInput()
{
	int id = m_event->GetBtnDownID();
	if (id != -1)
	{
		switch(id)
		{
		case BTN_CREAT:
			{
				if (1 != m_lastState)	//创建
				{
					m_UIState = 1;
					m_lbMsg->clear();				

					m_btnJion->setVisible(false);
					m_btnCreate->setVisible(false);
					
				}
				break;
			}
		case BTN_JION:
			{				
				m_UIState = 6;
				m_lbMsg->clear();
				m_btnJion->setVisible(false);
				m_btnCreate->setVisible(false);
				break;
				int hostindex = m_lbHostList->getSelected();
				if (hostindex >= 0)
				{					
					unsigned long hostIP;
					list<unsigned long>::Iterator it = m_HostList.begin();
					for (int i = 0; i < hostindex; i++)
					{
						it++;
					}
					hostIP = (unsigned long)*it;
					
					if (m_client->JionHost(hostIP, m_Myname.c_str()))
					{		//加入游戏成功
						m_UIState = 6;
						m_lbMsg->clear();
						m_btnJion->setVisible(false);
						m_btnCreate->setVisible(false);
						
						m_lbHostList->clear();				//清除主机列表
					}
					else
					{
						m_lbMsg->addItem(L"----fail to jion the game----", 4);
					}
				}
				else
				{
					m_lbMsg->addItem(L"Please select a host first!", 4);
				}
				break;
			}
		case BTN_CANCEL:
			{	
				if (4 == m_lastState ||  6 == m_lastState)	//取消创建主机 或 取消选择的主机
				{
					if (NULL == m_server)	//取消选择的主机
					{
						m_client->ExitHost();
					}
					else					//取消创建主机
					{
						m_lbPlayerList->setItem(0, L"Open", 3);
						m_lbPlayerList->setItem(1, L"Open", 3);
						m_lbPlayerList->setItem(2, L"Open", 3);
						m_lbPlayerList->setItem(3, L"Open", 3);
						m_server->CancelHost();
						m_client->BeExit();
						delete m_server;
						m_server = NULL;
					}
					m_lbMsg->clear();
					m_lbHostList->clear();
					m_client->QueryHost();
					m_btnGo->setVisible(false);
					m_UIState = 5;

				}
				else if(1 == m_lastState)	
				{
					m_UIState = 2;
				}
				else	//退到选车的界面
				{
					m_UIState = 3;
					m_btnJion->setVisible(false);
					m_btnCreate->setVisible(false);	
					m_btnCancel->setVisible(false);
				}
				break;
			}
		case BTN_OK:
			{
				if (m_lastState == 1)		//选择地图
				{
					int index = m_selectList->getSelected();
					if (index >= 0)
					{	
						m_UIState = 4;
						if( m_server != NULL)
						{
							delete m_server;
						}
						char* buffer = CHelper::wchar_to_char(m_selectList->getListItem(index));
						m_server = GameLogic::CreateLanServer();
						m_server->CreateHost(m_Myname.c_str(), buffer);
						delete[] buffer;

						m_client->JionHost(Net::GetIP_long(), m_Myname.c_str());
						m_btnGo->setVisible(false);
					}
					else
					{
						m_lbMsg->addItem(L"Please select a Map first!", 4);
					}
				}
				else		//开始游戏
				{
					if (!m_server->BeignGame())
					{
						m_lbMsg->addItem(L"至少要2个玩家!");
						break;
					}
				}

			}		
		}
	}
	if( m_event->IsKeyDown(irr::KEY_RETURN))		//发送消息
	{
		if ('\0' != m_tbSend->getText()[0])
		{				
			if (!m_client->IsJionHost())		//如果是未加入主机 广播消息
			{
				GlobeChat msg;
				CHelper::CopyChar( msg.name ,20, IMyUIScene::m_Myname.c_str());	

				char * buffer = CHelper::wchar_to_char(m_tbSend->getText());
				CHelper::CopyChar( msg.msg , 30, buffer);
				delete[] buffer;

				PACKAGE package;

				package.m_cmd = CMD_GlobeChat;

				package.Setdata((const char*)&msg, sizeof(GlobeChat));	//强行转换 结构数据
				Net::SendMessage(package);
			}
			else							//如果是已经加入主机 则把消息发送到主机
			{
				GameChat msg;				
				msg.index = m_client->GetIndex();
				char * buffer = CHelper::wchar_to_char(m_tbSend->getText());
				CHelper::CopyChar( msg.msg , sizeof(GameChat) - sizeof(int), buffer);
				delete[] buffer;
				PACKAGE package;
				package.m_cmd = CMD_GameChat;
				package.Setdata((const char*)&msg, sizeof(GameChat));	//强行转换 结构数据
				m_client->SendMsg(package);
			}
			m_tbSend->setText(NULL);
		}
	}
}

void CSelectGame::Updata()
{
	if (m_isGoing)
	{
		CSelectGame::g_selectGame->m_next->InitUI();
		*CSelectGame::g_selectGame->m_CurrentUI = CSelectGame::g_selectGame->m_next;
		CSelectGame::g_selectGame = NULL;
		return;
	}

	DoInput();
	switch(m_UIState)
	{
	case 0:
		{
			if (m_y < 40)
			{
				m_y+=20;
				m_windows->move(core::position2d<s32>(0, 20));
				m_infoWin->move(core::position2d<s32>(0, 20));
			}
			else if(!m_addBtn)
			{
				m_btnCreate->setVisible(true);
				m_btnJion->setVisible(true);
				m_btnCancel->setVisible(true);
				m_addBtn = true;
			}
			else
			{
				m_lastState = m_UIState;
				m_hostY = 40;
				m_y = -560;
				m_UIState = 10;
				
			}
			break;
		}
	case 1:
		{
			if (m_hostY > -560)
			{
				m_hostY-=20;
				m_windows->move(core::position2d<s32>(0, -20));
				
			}		
			else if (m_y < 40)
			{
				m_y+=20;
				m_selectMap->move(core::position2d<s32>(0, 20));
			}
			else
			{
				m_lastState = m_UIState;
				m_hostY = 40;
				m_y = -560;
				m_UIState = 10;
				m_btnGo->setVisible(true);
			}
			break;
		}
	case 2:
		{			
			if (m_hostY > -560)
			{
				m_hostY-=20;
				m_selectMap->move(core::position2d<s32>(0, -20));
			}
			else if (m_y < 40)
			{
				m_y+=20;
				m_windows->move(core::position2d<s32>(0, 20));
				m_btnJion->setVisible(true);
				m_btnCreate->setVisible(true);
				m_btnGo->setVisible(false);
			}
			else
			{
				m_lastState = m_UIState;
				m_hostY = 40;
				m_y = -560;
				m_UIState = 10;
			}
			break;
		}
	case 3:		//退到选车的界面
		{
			if (m_hostY > -660)
			{
				m_hostY-=20;
				m_infoWin->move(core::position2d<s32>(0, -20));
				m_windows->move(core::position2d<s32>(0, -20));
				
			}
			else
			{
				m_lastState = m_UIState;
				m_hostY = 40;
				m_y = -560;
				m_UIState = 10;
				g_selectGame = NULL;
				this->Release();
				m_front->InitUI();
				*m_CurrentUI = m_front;
			}
			break;
		}
	case 4:
		{
			if (m_hostY > -560)
			{
				m_hostY-=20;
				m_selectMap->move(core::position2d<s32>(0, -20));
			}
			else if (m_y < 40)
			{
				m_y+=20;
				m_winHost->move(core::position2d<s32>(0, 20));
			}
			else
			{
				m_lastState = m_UIState;
				m_hostY = 40;
				m_y = -560;
				m_UIState = 10;
				m_btnGo->setVisible(true);
			}
			break;
		}
	case 5:
		{
			if (m_hostY > -560)
			{
				m_hostY-=20;
				m_winHost->move(core::position2d<s32>(0, -20));
			}
			else if (m_y < 40)
			{
				m_y+=20;
				m_windows->move(core::position2d<s32>(0, 20));
				
			}			
			else
			{
				m_lastState = m_UIState;
				m_hostY = 40;
				m_y = -560;
				m_UIState = 10;
				m_btnJion->setVisible(true);
				m_btnCreate->setVisible(true);
				m_btnGo->setVisible(false);
			}
			break;
		}
	case 6:
		{
			if (m_hostY > -560)
			{
				m_hostY-=20;
				m_windows->move(core::position2d<s32>(0, -20));
			}
			else if (m_y < 40)
			{
				m_y+=20;
				m_winHost->move(core::position2d<s32>(0, 20));
			}
			else
			{
				m_lastState = m_UIState;
				m_hostY = 40;
				m_y = -560;
				m_UIState = 10;
				m_btnGo->setVisible(true);
			}
		}
	}

}