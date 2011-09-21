///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/11 9:49
//Describe: 事件处理类
///////////////////////////////////////////////////////////////////////

#ifndef  CMyEventReceiver_h
#define  CMyEventReceiver_h
#pragma once

#include <irrlicht.h>
using namespace irr;

class CMyEventReceiver: public IEventReceiver
{
public:
	CMyEventReceiver(void);	
	~CMyEventReceiver(void);
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event);	

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const;
	int		GetBtnDownID();

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	int		m_BtnID;
};
#endif