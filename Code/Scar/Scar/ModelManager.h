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
#include <string>
#include "def.h"

using namespace irr;

/*
** 名字：ModelManager
** 说明：模型管理
**
*/
class ModelManager
{
private:
	struct MeshNode
	{
		scene::IAnimatedMesh*	mesh;
		std::wstring				textureFilename;
	};

	std::map< std::wstring, MeshNode >	m_meshMap;
	std::list< scene::ISceneNode* >		m_ISceneNodeList;

public:	
	ModelManager()
	{ }

	const std::list< scene::ISceneNode* >& GetISceneNodeList() const
	{
		return m_ISceneNodeList;
	}

	void LoadModels();

	void AddMesh( const std::wstring& meshID, const std::wstring& meshFilename, const std::wstring& textureFilename );

	scene::ISceneNode* AddSceneNodeFromMesh( const std::wstring& meshID, bool bTestCollision = false );

	void AddSceneNode( const std::wstring& meshFilename, const std::wstring );

	void DeleteAll();
};



#endif