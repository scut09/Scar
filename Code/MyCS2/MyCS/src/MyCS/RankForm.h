///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/21 15:26
//Describe: �����Ի���
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
	///	@brief ��ʾ�Ի���
	///	@param [in] :
	///	@return void
	//////////////////////////////
	void  Show(bool show);

	//////////////////////////////
	///	@brief 	�ж��Ƿ�����ʾ״̬
	///	@return bool
	//////////////////////////////
	bool	IsShow();

	//////////////////////////////
	///	@brief �ͷ�	
	///	@return void
	//////////////////////////////
	void  Release();
private:
	//////////////////////////////
	///	@brief ����
	///	@return ��������
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