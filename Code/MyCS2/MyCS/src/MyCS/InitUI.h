///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/12 18:39
//Describe: ѡ������
///////////////////////////////////////////////////////////////////////

#ifndef  CSelectCar_h
#define  CSelectCar_h

#pragma once
#include "..\..\include\IMyUIScene.h"

#include <string>

class CInitUI:public IMyUIScene
{
public:
	CInitUI(void);
	~CInitUI(void);

public:
	//////////////////////////////
	///	@brief �ͷŴ˽ڵ�
	///	@return void
	//////////////////////////////
	void	Release();

	void	DoInput();

	void	Updata();

	void	InitUI();
private:	
	ICameraSceneNode*	m_Carmera;			//������ڵ�
	int		m_rotY;
	int		m_CarmeraY;	
	std::string* m_strList;
	int		m_count;
	int		m_currentCount;

	IGUIEditBox* m_tbName;
};
#endif