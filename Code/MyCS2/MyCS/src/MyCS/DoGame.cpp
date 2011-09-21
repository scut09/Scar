#include "DoGame.h"

CDoGame*	CDoGame::g_obj = NULL;

void GameMsgCome(unsigned long SenderIP, PACKAGE& msg)
{
	switch(msg.m_cmd)
	{
	case CMD_HreoMove:		//�ƶ�
		{
			HreoMove* direction = (HreoMove*) msg.Getdata(12);
			if (direction->index != CDoGame::m_client->GetIndex())
			{
				CDoGame::g_obj->m_hreoList[direction->index]->MoveTo(direction->x, direction->y, direction->z);
			}			
			break;
		}
	case CMD_HreoTrun:		//��ת
		{
			HreoTrun* rot = (HreoTrun*) msg.Getdata(12);
			if (rot->index != CDoGame::m_client->GetIndex())
			{
				vector3df vrot(0, rot->y, 0);
				if (CDoGame::g_obj->m_hreoList[rot->index] != NULL)
				{
					CDoGame::g_obj->m_hreoList[rot->index]->Trun(vrot);
				}				
			}
			break;
		}
	case CMD_bulletAttack:		//�ӵ�
		{
			bulletAttack bullet;
			memcpy(&bullet, msg.Getdata(12), sizeof(bulletAttack));
			if (bullet.ownindex != CDoGame::m_client->GetIndex())	//��������Լ�������ӵ����� ���Լ��Ĳ�����
			{
				vector3df ps(bullet.x, bullet.y, bullet.z);
				if(bullet.killIndex > -1)		//�л��лĿ��
				{
					
					Cbullet::CreateBullet(ps,
						CDoGame::g_obj->m_hreoList[bullet.killIndex]->GetSceneNode());
					
					CDoGame::g_obj->m_hreoList[bullet.killIndex]->m_HP -=20;

					if (0 >= CDoGame::g_obj->m_hreoList[bullet.killIndex]->m_HP)
					{
						CDoGame::g_obj->m_hreoList[bullet.killIndex]->m_HP = 0;
						CDoGame::g_obj->m_hreoList[bullet.killIndex]->SetAinmState(EMAT_CROUCH_DEATH);
						std::string str;
						str = CDoGame::g_obj->m_client->GetName(bullet.ownindex);
						str += " kill ";
						str += CDoGame::g_obj->m_client->GetName(bullet.killIndex);
						CDoGame::g_obj->AddInfo(str.c_str());
						CDoGame::g_obj->m_hreoList[bullet.killIndex]->m_beKill++;
						CDoGame::g_obj->m_hreoList[bullet.ownindex]->m_killCount++;
					}

					if (bullet.killIndex == CDoGame::m_client->GetIndex())	//�Լ������� hp ����
					{
						CDoGame::g_obj->UpdataHP();
						if(0 == CDoGame::g_obj->m_hreoList[bullet.killIndex]->m_HP)
						{
							CDoGame::g_obj->m_hreo->Death();		//����							
						}
					}
				}
				else							//���г���
				{
					Cbullet::CreateBullet(ps);
				}
				ISound::MyPlaySound(ISound::SND_Shoot1, ps);	//�����ӵ�����
			}
			break;
		}
	case CMD_GameChat:		//������Ϣ
		{
			GameChat* msgstr = (GameChat*) msg.Getdata(12);
			std::string str;
			str = CDoGame::g_obj->m_client->GetName(msgstr->index);
			str += ":";
			str += msgstr->msg;
			CDoGame::g_obj->AddInfo(str.c_str());
			break;
		}
	case SCMD_CancelHost:	//�������˳�
		{
			CDoGame::g_obj->AddInfo("Host has exit!");
			Sleep(1000);
			CDoGame::g_obj->AddInfo("Exit to select UI");
			Sleep(1000);
			CDoGame::g_obj->m_client->BeExit();		//�����˳�
			break;
		}
	case CMD_Winner:		//��Ϸ����
		{
			bool* winner = (bool*) msg.Getdata(12);
			std::string str;
			for (int i = 0; i < 4; i++)
			{
				if (CDoGame::g_obj->m_client->IsSet(i))
				{
					str = CDoGame::g_obj->m_client->GetName(i);
					if (winner[i])
					{
						str += " has win";
					}
					else
					{
						str += " lost";
					}
					CDoGame::g_obj->AddInfo(str.c_str());
					
				}
			}
			Sleep(2000);
			CDoGame::g_obj->AddInfo("Exit to select UI");
			Sleep(1000);			
			CDoGame::g_obj->m_client->BeExit();		//�����˳�
			break;
		}
	case CCMD_ExitGame:		//����˳�
		{
			int index = *(int*)msg.Getdata(12);		//ת��Ϊ���� �õ��˳��ߵ�������
			std::string str = CDoGame::g_obj->m_client->GetName(index);
			str+=" has exit!";
			CDoGame::g_obj->AddInfo(str.c_str());
			if (CDoGame::g_obj->m_hreoList[index] != NULL)
			{
				delete CDoGame::g_obj->m_hreoList[index];
				CDoGame::g_obj->m_hreoList[index] = NULL;
			}
			break;
		}
	case CMD_Reset:			//��Ҹ���
		{
			int index = *(int*)msg.Getdata(12);		//ת��Ϊ����
			if (index == CDoGame::g_obj->m_client->GetIndex())	//���Լ�ʱ������
			{
				break;
			}
			CDoGame::g_obj->m_hreoList[index]->ReSet(CDoGame::g_obj->m_map->GetStartPostion(index));			
			break;
		}
	case CMD_Squat:		//����
		{
			Squat* parm = (Squat*) msg.Getdata(12);
			if (parm->index == CDoGame::g_obj->m_client->GetIndex())	//������Լ� ������
			{
				break;
			}
			CDoGame::g_obj->m_hreoList[parm->index]->SetSquat(parm->issquat);			
			break;
		}
	}
}


CDoGame::CDoGame(void)
{
	m_position[0] = vector3df(2700*2,255*2,2600*2);
	m_position[1] = vector3df(2700*2+400,255*2,2600*2+ 100);
	m_position[2] = vector3df(2700*2+800,255*2,2600*2+ 100);
	m_position[3] = vector3df(2700*2+800,255*2,2600*2+ 500);
	CDoGame::g_obj = this;
	m_changeBullet = false;
	m_menuState = false;
	m_menu = NULL;
	m_map = MyMap::CreateMap();
	ISound::Init();
}

CDoGame::~CDoGame(void)
{
}

#define MEUN_Continue		0
#define MEUN_Config			1
#define MEUN_ExitGame		2
#define MEUN_ExitProgram	3
void CDoGame::InitUI()
{
	m_currentBulletCount = 20;	//��ǰ�����ӵ���
	m_MaxCount = 20;			//���е��������
	m_totalCount = 80;			//ʣ���ӵ�����
	m_menu = NULL;

	
	
	Cbullet::g_collManager = m_smgr->getSceneCollisionManager();

	
	m_hreoEvent = new ChreoEventRecv();
	m_oldEvent = m_device->getEventReceiver();
	m_device->setEventReceiver(m_hreoEvent);	
	m_guienv->clear();	

	m_map->SetDevice(m_device);								//��ʼ����ͼ�豸ָ��

	loadMap();

	for (int i = 0 ; i < 4; i++)
	{
		if (m_client->IsSet(i))
		{
			if (i == m_client->GetIndex())
			{
				m_hreoList[i] = (IHreo*) new Chreo(i, m_map->GetStartPostion(i));
				m_hreo = (Chreo*)m_hreoList[i];
			}
			else
			{
				m_hreoList[i] = new Cenemy(i,  m_map->GetStartPostion(i));
				Cbullet::g_playerList[m_hreoList[i]->GetSceneNode()] = m_hreoList[i];
			}
		}
		else
		{
			m_hreoList[i] = NULL;
		}
	}
	m_map->SetPlayerList((void**) m_hreoList);				//������б���ӵ�map�б��ڼ���	

	ISound::SetListener(m_hreo->GetSceneNode());			//��ʼ����������

	m_rankWindow = new CRankForm((IHreo**)&m_hreoList, m_client);

	m_info = m_guienv->addStaticText(L"count:20/20 remain:80 HP:100/100",
		core::rect<s32>(750,720,1024,740), false, true, 0, -1);
	m_client->SetMsgComeEvent(GameMsgCome);		//������Ϣ������

	m_MsgBox = m_guienv->addWindow(irr::core::rect<s32>(100,768,800,800));
	m_MsgBox->setVisible(false);
	m_MsgBox->setDrawTitlebar(false);
	m_MsgBox->getCloseButton()->setVisible(false);
	m_MsgBoxState = 0;

	m_tb_msgBox = m_guienv->addEditBox(L"",irr::core::rect<s32>(5,5,690,28), true, m_MsgBox);


	m_gameinfo = m_guienv->addListBox(irr::core::rect<s32>(10,10,1024,200));
	m_gameinfo->setDrawBackground(false);
	m_gameinfo->setEnabled(false);
	
}

void CDoGame::Release()		//�ͷ���Դ
{
	for (int i = 0; i < 4; i++)
	{
		if(	m_hreoList[i] != NULL)
		{			
			m_hreoList[i]->Release();
			//delete m_hreoList[i];			����������
		}
	}
	m_rankWindow->Release();
	m_tb_msgBox->remove();
	m_MsgBox->remove();
	if (m_menu != NULL)
	{
		m_menu->remove();
	}
	m_gameinfo->remove();
	m_info->remove();
	m_map->Release();
	
	
}

void CDoGame::DoInput()
{
	MenuManage();		//�˵�����
	if (m_menuState)	//��������˵� ������IO
	{
		return;			
	}

	SendMsgManage();	//��Ϣ�Ի����ж�
	if (m_MsgBoxState == 2)		//�����������״̬ ������IO
	{		
		return;
	}

	MouseClick(); //����¼�����

	SquatManage(); //�������

	//------------------------------
	//Desc:������Ϣ
	//------------------------------
	if(m_hreoEvent->IsKeyDown(KEY_TAB))	
	{
		m_rankWindow->Show(true);
	}
	else
	{
		m_rankWindow->Show(false);
	}

	if(m_hreoEvent->IsKeyDown(KEY_KEY_R))	//������
	{
		if (m_totalCount > 0 && m_currentBulletCount < m_MaxCount)
		{
			if (!m_changeBullet)		//û���ڻ����оͿ���
			{
				ISound::MyPlaySound(ISound::SND_ChangeBullet, m_hreo->GetPosition());
				int cha = m_MaxCount - m_currentBulletCount;
				if (m_totalCount > cha)
				{
					m_totalCount -= cha;
					m_currentBulletCount = m_MaxCount;
				}
				else
				{
					m_currentBulletCount += m_totalCount;
					m_totalCount = 0;
				}
				m_changeBullet = true;
				m_hreo->m_AnimEnd = false;
				m_hreo->SetAinmState("idle");
				m_hreo->m_gun->setAnimationSpeed(60.f);
			}
		}
	}
	else		//����������ɺ� ��������
	{
		if (m_hreo->m_AnimEnd && m_changeBullet)
		{
			UpdataInfo();
			m_changeBullet = false;
		}
	}

	int x,y;

	vector3df rot = m_hreo->GetRot();
	if(m_hreoEvent->IsMouseMove(x,y))
	{		
		rot.Y += 0.03f * (x - 512 );
		rot.X += 0.03f * (y - 384 );

		if (rot.X >= 89)		//���Ƕ�89
		{
			rot.X = 89;
		}
		if (rot.X <= -89)
		{
			rot.X = -89;
		}

		if(!m_hreo->isDeath())		//Ӣ�ۻ��ž�֪ͨ������
		{
			m_package.m_cmd = CMD_HreoTrun;
			HreoTrun rotparm;
			rotparm.index = m_client->GetIndex();
			rotparm.y = rot.Y;
			m_package.Setdata((char*)&rotparm, sizeof(HreoTrun));
			m_client->SendMsg(m_package);		//֪ͨ������ ��ת
		}

		m_hreo->Trun(rot);
		m_device->getCursorControl()->setPosition(512,384);

		
	}

	DIRECTION dir = DIR_NONE;
		 
	if(m_hreoEvent->IsKeyDown(KEY_KEY_W))
	{
		if(m_hreoEvent->IsKeyDown(KEY_KEY_D))
		{
			dir = DIR_RUP;
		}
		else if (m_hreoEvent->IsKeyDown(KEY_KEY_A))
		{
			dir = DIR_LUP;
		}
		else
		{
			dir = DIR_UP;
		}		
	}
	else if(m_hreoEvent->IsKeyDown(KEY_KEY_S))
	{
		if(m_hreoEvent->IsKeyDown(KEY_KEY_D))
		{
			dir = DIR_RDOWN;
		}
		else if (m_hreoEvent->IsKeyDown(KEY_KEY_A))
		{
			dir = DIR_LDOWN;
		}
		else
		{
			dir = DIR_DOWN;
		}		
	}
	else if(m_hreoEvent->IsKeyDown(KEY_KEY_D))
	{
		dir = DIR_RIGHT;	
		
	}
	else if(m_hreoEvent->IsKeyDown(KEY_KEY_A))
	{
		dir = DIR_LEFT;	
	}
	if (DIR_NONE != dir)
	{
		m_hreo->MoveTo(dir, 0 , 0);
		
		if(!m_hreo->isDeath())		//Ӣ�ۻ��ž�֪ͨ������
		{
			m_package.m_cmd = CMD_HreoMove;
			HreoMove direction;
			direction.index = m_client->GetIndex();
			vector3df ps = m_hreo->GetPosition();
			direction.x = ps.X;
			direction.y = ps.Y;
			direction.z = ps.Z;
			m_package.Setdata((char*)&direction, sizeof(HreoMove));
			m_client->SendMsg(m_package);
		}
	}
	
}

void CDoGame::Updata()
{
	DoInput();
	if (!m_client->IsJionHost())
	{		
		m_client->ExitGame();
		this->Release();
		m_front->InitUI();		
		m_device->setEventReceiver(m_oldEvent);
		*m_CurrentUI = m_front;		
		m_device->getCursorControl()->setVisible(true);

		if (m_server != NULL)
		{
			m_server->CancelHost();
		}
	}
	if (m_hreo->isDeath())
	{
		m_hreo->m_ReSetCount++;
		if (m_hreo->m_ReSetCount > 300)
		{
			int index = m_client->GetIndex();
			m_hreo->ReSet(m_map->GetStartPostion(index));		//����
			m_package.m_cmd = CMD_Reset;

			m_package.Setdata((char*)&index, sizeof(int));
			m_client->SendMsg(m_package);

			m_currentBulletCount = m_MaxCount;
			m_totalCount = 80;
			UpdataInfo();
			UpdataHP();
		}
	}
}

void CDoGame::loadMap()
{
	std::string mapname = m_client->GetMapName();
	mapname +="\\";
	mapname += m_client->GetMapName();
	m_map->LoadMap(mapname.c_str());
}

void CDoGame::UpdataInfo()
{
	wchar_t* str = (wchar_t*)m_info->getText();
	char num[3];
	itoa(m_currentBulletCount, num, 10);
	if (m_currentBulletCount < 10)			//���õ�ǰ�ӵ���
	{
		str[6] = ' ';
		str[7] = num[0];
	}
	else
	{
		str[6] = num[0];
		str[7] = num[1];
	}
	
	itoa(m_totalCount, num, 10);
	if (m_totalCount < 10)			//�������ӵ���
	{
		str[19] = ' ';
		str[20] = num[0];
	}
	else
	{
		str[19] = num[0];
		str[20] = num[1];
	}

	m_info->setText(str);
}

void CDoGame::UpdataHP()
{
	wchar_t* str = (wchar_t*)m_info->getText();
	if(m_hreo->m_HP == m_hreo->m_maxHP)
	{
		str[25] = '1';
		str[26] = '0';
		str[27] = '0';
		m_info->setText(str);
		return;
	}
	char num[3];
	itoa(m_hreo->m_HP, num, 10);
	str[25] = ' ';
	if (m_hreo->m_HP < 10)			//���õ�ǰѪ��
	{
		str[26] = ' ';
		str[27] = num[0];
	}
	else
	{
		str[26] = num[0];
		str[27] = num[1];
	}
	m_info->setText(str);
}

void CDoGame::SendMsgManage()
{
	if (m_hreoEvent->IsKeyDown(KEY_RETURN))		//�س� ��ʾ����Ի���
	{
		if (0 == m_MsgBoxState)
		{
			m_MsgBox->setVisible(true);
			m_MsgBoxState = 1;
		}
		else if (2 == m_MsgBoxState)
		{

			if ('\0' != m_tb_msgBox->getText()[0])//������Ϣ
			{				
				GameChat msg;				
				msg.index = m_client->GetIndex();
				char * buffer = CHelper::wchar_to_char(m_tb_msgBox->getText());
				CHelper::CopyChar( msg.msg , 30, buffer);
				delete[] buffer;
				PACKAGE package;
				package.m_cmd = CMD_GameChat;
				package.Setdata((const char*)&msg, sizeof(GlobeChat));	//ǿ��ת�� �ṹ����
				m_client->SendMsg(package);
				m_tb_msgBox->setText(NULL);
				m_tb_msgBox->setEnabled(false);				

			}
			m_MsgBoxState = 3;
			//m_device->getCursorControl()->setVisible(false);
		}
	}
	else
	{
		if (1 == m_MsgBoxState) //����Ի�������
		{
			m_MsgBox->move(core::position2d<s32>(0, -5));
			if (m_MsgBox->getAbsolutePosition().UpperLeftCorner.Y <= 720)
			{
				m_MsgBoxState = 2;		// 2��ʾ������������				
				m_tb_msgBox->setEnabled(true);
				m_guienv->setFocus(m_tb_msgBox);
			}
		}
		if (3 == m_MsgBoxState) //����Ի�������
		{
			m_MsgBox->move(core::position2d<s32>(0, 5));
			if (m_MsgBox->getAbsolutePosition().UpperLeftCorner.Y >= 768)
			{
				m_MsgBoxState = 0;
				m_MsgBox->setVisible(false);
			}
		}
	}
}

void CDoGame::MouseClick()
{
	if (m_hreoEvent->IsMouseClick() && !m_hreo->isDeath())	//Ӣ�ۻ�����
	{
		if (!m_hreo->m_AnimEnd)	//�������û�в��� �������
		{
			return;
		}
		if (m_currentBulletCount > 0)		//�����ӵ�
		{
			m_currentBulletCount--;

			vector3df ps = m_hreo->GetPosition();
			int rang = 6000;

			int index = Cbullet::Attack(m_hreo->GetTagrt(), ps, rang);

			if (1 == rang)
			{
				m_package.m_cmd = CMD_bulletAttack;
				bulletAttack attack;
				attack.ownindex = m_client->GetIndex();
				attack.killIndex = index;
				if(index > -1)		//����Ŀ��
				{
					m_hreoList[index]->m_HP -=20;
					if (m_hreoList[index]->m_HP <= 0)	//ɱ���Է�
					{
						m_hreoList[index]->m_HP = 0;
						m_hreoList[index]->SetAinmState(EMAT_CROUCH_DEATH);
						std::string str;
						str = m_client->GetName(m_client->GetIndex());
						str += " kill ";
						str += m_client->GetName(index);
						AddInfo(str.c_str());
						m_hreo->m_killCount++;
						m_hreoList[index]->m_beKill++;
						bool winner[4];
						if (m_map->IsWin(winner))		//��ʤ
						{
							m_package.m_cmd = CMD_Winner;
							m_package.Setdata((char*)winner, sizeof(winner));
							m_client->SendMsg(m_package);						//��ʤ ������Ϣ֪ͨ������	
						}
					}
				}
				attack.x = ps.X;
				attack.y = ps.Y;
				attack.z = ps.Z;
				ISound::MyPlaySound(ISound::SND_Shoot1, ps);
				m_package.Setdata((char*)&attack, sizeof(bulletAttack));
				m_client->SendMsg(m_package);
			}
			else
			{
				ISound::MyPlaySound(ISound::SND_Shoot2, ps);	//û����Ŀ��ʱ������
			}
			m_hreo->m_AnimEnd = false;
			m_hreo->SetAinmState("pow");	//���Ź�������
			UpdataInfo();
		}
		else
		{
			ISound::MyPlaySound(ISound::SND_NoBullet);	//û����Ŀ��ʱ������
		}
	}
}

void CDoGame::AddInfo( const char* msg )
{
	wchar_t* str = CHelper::char_to_wchar(msg);
	m_gameinfo->addItem(str);
	delete[] str;
	if (m_gameinfo->getItemCount() > 6)
	{
		m_gameinfo->removeItem(0);
	}
}

void CDoGame::MenuManage()
{
	if( m_hreoEvent->IsKeyDown(KEY_ESCAPE)) //����Esc��
	{
		if (!m_menuState)
		{			
			m_menu = m_guienv->addContextMenu(irr::core::rect<s32>(400,320,600,500));			//�����˵�
			m_menu->addItem(L"...............Menu...............", 50);
			m_menu->addItem(L"Continue", MEUN_Continue);
			m_menu->addItem(L"Config", MEUN_Config);
			m_menu->addItem(L"Exit Game", MEUN_ExitGame);
			m_menu->addItem(L"Exit Program", MEUN_ExitProgram);
			m_menu->setItemEnabled(0,false);
			m_menuState = true;
			m_device->getCursorControl()->setVisible(true);
		}
	}
	if (m_menuState)
	{
		
		int menuid = m_hreoEvent->GetBtnDownID();
		switch(menuid)
		{
		case MEUN_Continue:
			{
				m_menuState = false;
				m_device->getCursorControl()->setVisible(false);
				break;
			}
		case MEUN_Config:
			{
				m_menuState = false;
				m_device->getCursorControl()->setVisible(false);
				break;
			}
		case MEUN_ExitGame:
			{
				if (NULL != m_server)		//��������� �˳�ʱӦ�ù㲥
				{
					m_server->CancelHost();
					m_server = NULL;
				}
				else
				{
					m_client->ExitGame();
				}
				break;
			}
		case MEUN_ExitProgram:
			{
				if (NULL != m_server)		//��������� �˳�ʱӦ�ù㲥
				{
					m_server->CancelHost();
				}
				else
				{		
					m_client->ExitGame();
				}				
				ExitProcess(0);		//�˳�����
				break;
			}
		}
		if (menuid != -1 || m_hreoEvent->IsMouseClick())
		{
			m_menu = NULL;
			m_menuState = false;
			m_device->getCursorControl()->setVisible(false);
			m_hreoEvent->IsMouseClick();		//��������Ϣ
		}		
	}
}

void CDoGame::SquatManage()
{
	if(m_hreoEvent->IsKeyDown(KEY_CONTROL))
	{
		if(!m_hreo->GetSquat())
		{
			m_hreo->SetSquat(true);
			m_package.m_cmd = CMD_Squat;			//����
			Squat parm;
			parm.index = m_client->GetIndex();
			parm.issquat = true;
			m_package.Setdata((char*)&parm, sizeof(Squat));
			m_client->SendMsg(m_package);
		}
	}
	else
	{
		if(m_hreo->GetSquat())
		{
			m_hreo->SetSquat(false);
			m_package.m_cmd = CMD_Squat;			//����
			Squat parm;
			parm.index = m_client->GetIndex();
			parm.issquat = false;
			m_package.Setdata((char*)&parm, sizeof(Squat));
			m_client->SendMsg(m_package);
		}
	}
}