///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/17 15:30
//Describe: 游戏界面
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
	///	@brief 释放此节点
	///	@return void
	//////////////////////////////
	void	Release();

	void	DoInput();

	void	Updata();

	void	InitUI();

	friend void GameMsgCome(unsigned long SenderIP, PACKAGE& msg);

private:
	void loadMap();	//加载地图

	void UpdataInfo();	//更新子弹等信息

	void UpdataHP();	//更新血量

	void SendMsgManage(); // 管理消息发送

	void MouseClick();	//鼠标按下

	void MenuManage();		//菜单管理

	void SquatManage();		//蹲下管理

	//////////////////////////////
	///	@brief 添加消息
	///	@param [in] msg:要添加的消息
	///	@return void
	//////////////////////////////
	void AddInfo(const char* msg);	

private:
	
	static CDoGame*			g_obj;				//静态对象 供GameMsgCome函数使用
	int						m_direction;		//
	
	IHreo*					m_hreoList[4];	//游戏对象
	Chreo*					m_hreo;

	IEventReceiver*			m_oldEvent;		//以前的事件处理类
	ChreoEventRecv*			m_hreoEvent;	//事件处理类	

	PACKAGE					m_package;		//用于发包的结构

	vector3df				m_position[4];	//出生位置

	int			m_currentBulletCount;	//当前弹夹子弹数
	int			m_MaxCount;				//弹夹的最大容量
	int			m_totalCount;			//剩余子弹总数
	IMap*		m_map;

	irr::gui::IGUIWindow*	m_MsgBox;		//聊天对话框
	irr::gui::IGUIEditBox*  m_tb_msgBox;	//聊天消息编辑框
	int						m_MsgBoxState;

	irr::gui::IGUIContextMenu*	m_menu;			//弹出菜单
	bool						m_menuState;	//菜单的状态

	irr::gui::IGUIListBox*  m_gameinfo;		//游戏信息

	irr::gui::IGUIStaticText*	m_info;

	bool	m_changeBullet;		//是否换弹夹

	CRankForm*				m_rankWindow;


};
#endif