///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/21 15:26
//Describe: 排名对话框
///////////////////////////////////////////////////////////////////////

#ifndef  CRankForm_h
#define  CRankForm_h
#pragma once
#include "Ihreo.h"
#include "../../include/IGameLogic.h"
#include "Helper.h"

class CRankForm:public IGlobe
{
public:
	CRankForm(IHreo** playerlist, GameLogic::IClient* client);
	~CRankForm(void);
public:
	//////////////////////////////
	///	@brief 显示对话框
	///	@param [in] :
	///	@return void
	//////////////////////////////
	void  Show(bool show);

	//////////////////////////////
	///	@brief 	判断是否处于显示状态
	///	@return bool
	//////////////////////////////
	bool	IsShow();

	//////////////////////////////
	///	@brief 释放	
	///	@return void
	//////////////////////////////
	void  Release();
private:
	//////////////////////////////
	///	@brief 排序
	///	@return 返回人数
	//////////////////////////////
	int	Sort();

private:
	IHreo**					m_playerlist;
	GameLogic::IClient*		m_client;
	bool					m_isShow;
	IHreo*					m_sort[4];
	irr::gui::IGUIListBox*	m_listBox;
	irr::gui::IGUIWindow*	m_window;


};
#endif