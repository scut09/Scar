///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/12 18:39
//Describe: 选择汽车
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
	///	@brief 释放此节点
	///	@return void
	//////////////////////////////
	void	Release();

	void	DoInput();

	void	Updata();

	void	InitUI();
private:	
	ICameraSceneNode*	m_Carmera;			//摄像机节点
	int		m_rotY;
	int		m_CarmeraY;	
	std::string* m_strList;
	int		m_count;
	int		m_currentCount;

	IGUIEditBox* m_tbName;
};
#endif