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


/*
** ���֣�PythonSColor
** ˵����Ϊ�˼���SColor
**
*/
struct PythonSColor
{
	f32 alpha;
	f32 red;
	f32 green;
	f32 blue;
};

/*
** ���֣�PythonSLight
** ˵����Ϊ�˼���SLight
**
*/
struct PythonSLight
{
	PythonSColor AmbientColor;
	PythonSColor DiffuseColor;
	PythonSColor SpecularColor;
};

/*
** ���֣�PythonVector3df
** ˵��������vector3df
**
*/
struct PythonVector3df
{
	f32 x;
	f32 y;
	f32 z;

	PythonVector3df( f32 xx = 0, f32 yy = 0, f32 zz = 0 ) : x( xx ), y( yy ), z( zz ) {}
};

/*
** ���֣�PythonSceneNode
** ˵������װISceneNode
**
*/
struct PythonSceneNode
{
	scene::ISceneNode*	ptr;

	PythonSceneNode() : ptr( NULL )
	{}

	void SetPosition( f32 x, f32 y, f32 z )
	{
		BOOST_ASSERT( ptr );
		ptr->setPosition( core::vector3df( x, y, z ) );
	}
	
	PythonVector3df GetPosition()
	{
		BOOST_ASSERT( ptr );
		return PythonVector3df( ptr->getPosition().X, ptr->getPosition().Y, ptr->getPosition().Z );
	}

	void SetRotation( f32 x, f32 y, f32 z )
	{
		BOOST_ASSERT( ptr );
		ptr->setRotation( core::vector3df( x, y, z  ) );
	}

	PythonVector3df GetRotation()
	{
		BOOST_ASSERT( ptr );
		return PythonVector3df( ptr->getRotation().X, ptr->getRotation().Y, ptr->getRotation().Z );
	}

	void Grab()
	{
		BOOST_ASSERT( ptr );
		ptr->grab();
	}

	void Drop()
	{
		BOOST_ASSERT( ptr );
		ptr->drop();
	}

	void Remove()
	{
		BOOST_ASSERT( ptr );
		ptr->remove();
	}
};


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

	PythonSceneNode AddSceneNodeByMeshID( const std::string& meshID, bool bTestCollision = false );
};



#endif