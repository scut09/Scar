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
		std::string				textureFilename;
	};

	std::map< std::string, MeshNode >	m_meshMap;
	std::list< scene::ISceneNode* >		m_ISceneNodeList;

public:	
	ModelManager()
	{ }

	void LoadModels();

	void AddMesh( const std::string& meshID, const std::string& meshFilename, const std::string& textureFilename );

	scene::ISceneNode* AddSceneNodeFromMesh( const std::string& meshID, bool bTestCollision = false );

	void AddSceneNode( const std::string& meshFilename, const std::string );

	void DeleteAll()
	{
		for ( auto iter = m_ISceneNodeList.begin(); iter != m_ISceneNodeList.end(); ++iter )
		{
			(*iter)->remove();
			(*iter)->drop();
		}
		m_ISceneNodeList.clear();
	}
};



#endif