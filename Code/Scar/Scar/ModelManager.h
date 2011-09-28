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
#include "def.h"

using namespace irr;

/*
** 名字：ModelManager
** 说明：模型管理
**
*/
class ModelManager
{
public:	
	ModelManager()
	{ }

	void LoadModels();

};


/*
** 名字：ModelManagerSlaver
** 说明：Python导出类
**
*/
class ModelManagerSlaver
{
public:

};

#endif