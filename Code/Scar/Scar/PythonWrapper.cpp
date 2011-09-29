/********************************************************************
	创建时间: 2011-9-29   19:32
	文件名:   PythonWrapper.cpp
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     

*********************************************************************/


#include "PythonWrapper.h"
#include "MyIrrlichtEngine.h"


//////////////////////////////////////////////////////////////////////////
//
// Class ModelManagerSlaver
// 
void ModelManagerSlaver::AddMesh( const std::string& meshID, const std::string& meshFilename, const std::string& textureFilename )
{
	ModelManager* pModelMan = MyIrrlichtEngine::GetEngine()->GetModelManager();

	pModelMan->AddMesh( meshID, meshFilename, textureFilename );

}

void ModelManagerSlaver::AddLight( const PythonSLight& light, f32 x, f32 y, f32 z )
{
	auto assign = []( video::SColorf& scolor, const PythonSColor& pcolor )
	{
		scolor.set( pcolor.alpha, pcolor.red, pcolor.green, pcolor.blue );
	};
	auto smgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();

	scene::ILightSceneNode * pLight = smgr->addLightSceneNode( 0, core::vector3df( x, y, z ) );
	video::SLight slight;
	assign( slight.AmbientColor, light.AmbientColor );
	assign( slight.DiffuseColor, light.DiffuseColor );
	assign( slight.SpecularColor, light.SpecularColor );
	pLight->getLightData() = slight;

	//auto print = []( const PythonSColor& pcolor )
	//{
	//	std::cout << pcolor.alpha << ' ' <<  pcolor.red << ' ' <<  pcolor.green << ' ' <<  pcolor.blue << std::endl;
	//};

	//print( light.AmbientColor );
	//print( light.DiffuseColor );
	//print( light.SpecularColor );
	//std::cout << x << ' ' << y << ' ' << z << std::endl;
}

PythonSceneNode ModelManagerSlaver::AddSceneNodeByMeshID( const std::string& meshID, bool bTestCollision /*= false */ )
{
	ModelManager* pModelMan = MyIrrlichtEngine::GetEngine()->GetModelManager();

	PythonSceneNode node;
	scene::ISceneNode* pNode = pModelMan->AddSceneNodeFromMesh( meshID, bTestCollision );
	node.ptr = pNode;
	return node;
}
