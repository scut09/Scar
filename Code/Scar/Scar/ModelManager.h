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
#include <string>
#include "def.h"

using namespace irr;

/*
** ���֣�ModelManager
** ˵����ģ�͹���
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