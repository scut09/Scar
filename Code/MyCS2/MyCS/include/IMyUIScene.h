///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/12 16:56
//Describe: UI�ӿ���
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
	bool	m_Enable;	//��ʾ�����Ƿ����
	bool	m_isVisalb;	//��ʾ�����Ƿ�ɼ�

	static IrrlichtDevice*		m_device;
	static IGUIEnvironment*		m_guienv;	// �豸����
	static IVideoDriver*		m_driver ;	
	static ISceneManager*		m_smgr ;
	static CMyEventReceiver*	m_event;

	static IMyUIScene**			m_CurrentUI;

	static GameLogic::IClient*			m_client;
	static GameLogic::IServer*			m_server;

	static	std::string	m_Myname;	//�������
	static	std::string	m_carPath;	//���ѡ��ĳ��ӵ�·��

	IMyUIScene*					m_next;		//��һ��
	IMyUIScene*					m_front;	//��һ��

	//////////////////////////////
	///	@brief �ͷŴ˽ڵ�
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