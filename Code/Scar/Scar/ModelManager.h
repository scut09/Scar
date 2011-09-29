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
** 名字：ModelManagerSlaver
** 说明：Python导出类
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