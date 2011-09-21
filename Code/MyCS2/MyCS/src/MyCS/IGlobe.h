///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/18 16:53
//Describe: 全局引用  方便其他地方引用
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
	int			m_index;		//索引号
	
	static IrrlichtDevice*		g_device;
	static IGUIEnvironment*		g_guienv;		//设备对象
	static IVideoDriver*		g_driver;
	static ISceneManager*		g_smgr ;	//场景管理器
	virtual ~IGlobe(){}
};

#endif