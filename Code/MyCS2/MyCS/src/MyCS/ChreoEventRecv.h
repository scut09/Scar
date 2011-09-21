///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/18 19:59
//Describe: 英雄事件处理函数
///////////////////////////////////////////////////////////////////////

#ifndef  ChreoEventRecv_h
#define  ChreoEventRecv_h
#pragma once
#include <irrlicht.h>
using namespace irr;

class ChreoEventRecv: public IEventReceiver
{
public:
	ChreoEventRecv(void);
	~ChreoEventRecv(void);
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event);	

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const;

	int		GetBtnDownID();

	bool	IsMouseClick();

	bool	IsMouseMove(int& x, int& y);

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	int		m_BtnID;
	bool m_mouseClick;

	bool m_mouseMove;
	int m_x;
	int m_y;
};
#endif