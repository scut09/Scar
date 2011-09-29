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

	std::map< std::string, MeshNode > m_meshMap;

public:	
	ModelManager()
	{ }

	void LoadModels();

	void AddMesh( const std::string& meshID, const std::string& meshFilename, const std::string& textureFilename );

	scene::ISceneNode* AddSceneNodeFromMesh( const std::string& meshID, bool bTestCollision = false );

	void AddSceneNode( const std::string& meshFilename, const std::string );
};

struct PythonSColor
{
	f32 alpha;
	f32 red;
	f32 green;
	f32 blue;
};

//void operator=( video::SColorf& scolor, PythonSColor& pcolor )
//{
//	scolor.set( pcolor.alpha, pcolor.red, pcolor.green, pcolor.blue );
//}

struct PythonSLight
{
	PythonSColor AmbientColor;
	PythonSColor DiffuseColor;
	PythonSColor SpecularColor;
};

//void operator=( video::SLight& slight, PythonSLight& plight )
//{
//	slight.AmbientColor = plight.AmbientColor;
//	slight.DiffuseColor = plight.DiffuseColor;
//	slight.SpecularColor = plight.SpecularColor;
//}


/*
** ���֣�ModelManagerSlaver
** ˵����Python������
**
*/
class ModelManagerSlaver
{
public:
	void AddMesh( const std::string& meshID, const std::string& meshFilename, const std::string& textureFilename );

	void AddLight( const PythonSLight& light, f32 x, f32 y, f32 z );

	void AddSceneNodeByMeshID( const std::string& meshID, bool bTestCollision = false );
};



#endif