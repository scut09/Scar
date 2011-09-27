/********************************************************************
����ʱ��: 2011-9-27   14:56
�ļ���:   ModelManager.h
����:     ���� Cedric Porter [ Stupid ET ]	
˵��:     ģ�͹���

*********************************************************************/

#ifndef _MODELMANAGER_H_
#define _MODELMANAGER_H_

#include <irrlicht.h>
#include <map>
#include <list>

using namespace irr;

/*
** ���֣�ModelManager
** ˵����ģ�͹���
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