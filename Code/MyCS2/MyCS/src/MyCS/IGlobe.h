///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/18 16:53
//Describe: ȫ������  ���������ط�����
///////////////////////////////////////////////////////////////////////

#ifndef  IGlobe_h
#define  IGlobe_h

#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class IGlobe
{
public:	
	int			m_index;		//������
	
	static IrrlichtDevice*		g_device;
	static IGUIEnvironment*		g_guienv;		//�豸����
	static IVideoDriver*		g_driver;
	static ISceneManager*		g_smgr ;	//����������
	virtual ~IGlobe(){}
};

#endif