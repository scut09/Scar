///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/12 16:56
//Describe: UI接口类
///////////////////////////////////////////////////////////////////////

#ifndef  IMyUIScene_h
#define  IMyUIScene_h

#include <irrlicht.h>
#include <string>
#include "Helper.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#include "MyEventReceiver.h"
#include "INetWork.h"

#include "IGameLogic.h"

class IMyUIScene
{
public:
	bool	m_Enable;	//表示按键是否可用
	bool	m_isVisalb;	//表示场景是否可见

	static IrrlichtDevice*		m_device;
	static IGUIEnvironment*		m_guienv;	// 设备对象
	static IVideoDriver*		m_driver ;	
	static ISceneManager*		m_smgr ;
	static CMyEventReceiver*	m_event;

	static IMyUIScene**			m_CurrentUI;

	static GameLogic::IClient*			m_client;
	static GameLogic::IServer*			m_server;

	static	std::string	m_Myname;	//玩家名字
	static	std::string	m_carPath;	//玩家选择的车子的路径

	IMyUIScene*					m_next;		//下一个
	IMyUIScene*					m_front;	//上一个

	//////////////////////////////
	///	@brief 释放此节点
	///	@return void
	//////////////////////////////
	virtual void	Release() = 0;

	virtual void	DoInput() = 0;

	virtual void	Updata() = 0;

	virtual void	InitUI() = 0;

	IGUIButton* AddBtn(int x, int y, const wchar_t* text, int id, IGUIElement* parent = 0)
	{
		IGUIButton* btn = m_guienv->addButton(rect<s32>(x,y,x + 100, y + 30), parent, id, text, 0);
		if (NULL == m_image)
		{
			m_image = m_driver->getTexture("image/btn.jpg");
		}		
		btn->setImage(m_image,rect<s32>(0,0,130,39));
		return btn;
	}

protected:

private:
	static ITexture* m_image;
};

#endif