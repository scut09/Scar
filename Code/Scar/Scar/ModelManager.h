/********************************************************************
创建时间: 2011-9-27   14:56
文件名:   ModelManager.h
作者:     华亮 Cedric Porter [ Stupid ET ]	
说明:     模型管理

*********************************************************************/

#ifndef _MODELMANAGER_H_
#define _MODELMANAGER_H_

#include <irrlicht.h>
#include <map>
#include <list>

using namespace irr;

/*
** 名字：ModelManager
** 说明：模型管理
**
*/
class ModelManager
{
	scene::ISceneManager*	m_smgr;

public:	
	ModelManager()
	{ }

	void LoadModels( scene::ISceneManager* smgr, video::IVideoDriver* driver )
	{
		m_smgr = smgr;

		smgr->addSkyBoxSceneNode(
			driver->getTexture("../media/irrlicht2_up.jpg"),
			driver->getTexture("../media/irrlicht2_dn.jpg"),
			driver->getTexture("../media/irrlicht2_lf.jpg"),
			driver->getTexture("../media/irrlicht2_rt.jpg"),
			driver->getTexture("../media/irrlicht2_ft.jpg"),
			driver->getTexture("../media/irrlicht2_bk.jpg"));
	}

};

#endif