///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/13 11:34
//Describe: ѡ����Ϸ����
///////////////////////////////////////////////////////////////////////

#ifndef  CSelectGame_h
#define  CSelectGame_h

#pragma once
#include "..\..\include\IMyUIScene.h"
#include <string>
using namespace Net;

void MsgCome(unsigned long SenderIP, PACKAGE& msg);

class CSelectGame:public IMyUIScene
{
public:
	CSelectGame(void);
	~CSelectGame(void);
public:
	//////////////////////////////
	///	@brief �ͷŴ˽ڵ�
	///	@return void
	//////////////////////////////
	void	Release();

	void	DoInput();

	void	Updata();

	void	InitUI();

	friend void MsgCome(unsigned long SenderIP, PACKAGE& msg);
private:
	std::string		m_name;		//�������
	std::string		m_carPath;	//���ѡ�������

	list<unsigned long> m_HostList;
	//map<unsigned long, int>	m_mapHostList;	//�����б�

	static CSelectGame* g_selectGame;
	
	int		m_y;

	IGUIWindow* m_windows;
	IGUIWindow* m_infoWin;
	IGUIWindow* m_winHost;
	
	IGUIWindow*		m_selectMap;
	IGUIListBox*	m_selectList;

	int		m_hostY;

	IGUIButton* m_btnJion;
	IGUIButton* m_btnCreate;
	IGUIButton* m_btnCancel;
	IGUIButton* m_btnGo;

	IGUIEditBox* m_tbSend;
	IGUIListBox* m_lbMsg;
	IGUIListBox* m_lbHostList;
	IGUIListBox* m_lbPlayerList;


	

	bool		m_addBtn;

	int			m_UIState;
	int			m_lastState;

	bool		m_isGoing;		//�ж���Ϸ�Ƿ�ʼ
	
};

#endif