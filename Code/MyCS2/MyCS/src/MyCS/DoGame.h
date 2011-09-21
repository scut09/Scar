///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/17 15:30
//Describe: ��Ϸ����
///////////////////////////////////////////////////////////////////////
#ifndef  CDoGame_h
#define  CDoGame_h

#pragma once

#include "..\..\include\IMyUIScene.h"
#include "..\..\include\ISound.h"
#include "..\..\include\IMap.h"
using namespace MyMap;

#include "ChreoEventRecv.h"
#include "Chreo.h"
#include "Cenemy.h"
#include "Cbullet.h"
#include "RankForm.h"

#include <list>
using namespace Net;

void GameMsgCome(unsigned long SenderIP, PACKAGE& msg);

class CDoGame:public IMyUIScene
{
public:
	CDoGame(void);
	~CDoGame(void);
public:
	//////////////////////////////
	///	@brief �ͷŴ˽ڵ�
	///	@return void
	//////////////////////////////
	void	Release();

	void	DoInput();

	void	Updata();

	void	InitUI();

	friend void GameMsgCome(unsigned long SenderIP, PACKAGE& msg);

private:
	void loadMap();	//���ص�ͼ

	void UpdataInfo();	//�����ӵ�����Ϣ

	void UpdataHP();	//����Ѫ��

	void SendMsgManage(); // ������Ϣ����

	void MouseClick();	//��갴��

	void MenuManage();		//�˵�����

	void SquatManage();		//���¹���

	//////////////////////////////
	///	@brief �����Ϣ
	///	@param [in] msg:Ҫ��ӵ���Ϣ
	///	@return void
	//////////////////////////////
	void AddInfo(const char* msg);	

private:
	
	static CDoGame*			g_obj;				//��̬���� ��GameMsgCome����ʹ��
	int						m_direction;		//
	
	IHreo*					m_hreoList[4];	//��Ϸ����
	Chreo*					m_hreo;

	IEventReceiver*			m_oldEvent;		//��ǰ���¼�������
	ChreoEventRecv*			m_hreoEvent;	//�¼�������	

	PACKAGE					m_package;		//���ڷ����Ľṹ

	vector3df				m_position[4];	//����λ��

	int			m_currentBulletCount;	//��ǰ�����ӵ���
	int			m_MaxCount;				//���е��������
	int			m_totalCount;			//ʣ���ӵ�����
	IMap*		m_map;

	irr::gui::IGUIWindow*	m_MsgBox;		//����Ի���
	irr::gui::IGUIEditBox*  m_tb_msgBox;	//������Ϣ�༭��
	int						m_MsgBoxState;

	irr::gui::IGUIContextMenu*	m_menu;			//�����˵�
	bool						m_menuState;	//�˵���״̬

	irr::gui::IGUIListBox*  m_gameinfo;		//��Ϸ��Ϣ

	irr::gui::IGUIStaticText*	m_info;

	bool	m_changeBullet;		//�Ƿ񻻵���

	CRankForm*				m_rankWindow;


};
#endif