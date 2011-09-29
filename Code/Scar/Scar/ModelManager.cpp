/********************************************************************
	创建时间: 2011-9-28   0:18
	文件名:   ModelManager.cpp
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     

*********************************************************************/


#include "ModelManager.h"
#include "MyIrrlichtEngine.h"

using namespace irr;

//////////////////////////////////////////////////////////////////////////
//
// Class ModelManager
// 
void ModelManager::LoadModels()
{
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();

	auto smgr = pEngine->GetSceneManager();
	auto driver = pEngine->GetVideoDriver();

	smgr->addSkyBoxSceneNode(
		driver->getTexture("../media/irrlicht2_up.jpg"),
		driver->getTexture("../media/irrlicht2_dn.jpg"),
		driver->getTexture("../media/irrlicht2_lf.jpg"),
		driver->getTexture("../media/irrlicht2_rt.jpg"),
		driver->getTexture("../media/irrlicht2_ft.jpg"),
		driver->getTexture("../media/irrlicht2_bk.jpg"));
}

void ModelManager::AddMesh( const std::string& meshID, const std::string& meshFilename, const std::string& textureFilename )
{
	scene::ISceneManager* smgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();
	MeshNode node = { smgr->getMesh( meshFilename.c_str() ), textureFilename };

	m_meshMap[ meshID ] = node;
}

scene::ISceneNode* ModelManager::AddSceneNodeFromMesh( const std::string& meshID, bool bTestCollision )
{
	if ( m_meshMap.find( meshID ) == m_meshMap.end() )		return NULL;

	scene::ISceneManager* smgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();
	video::IVideoDriver* driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();

	MeshNode& meshNode = m_meshMap[ meshID ];

	scene::ISceneNode* node = smgr->addAnimatedMeshSceneNode( meshNode.mesh );

	if ( ! meshNode.textureFilename.empty() )
	{
		node->setMaterialFlag( video::EMF_LIGHTING, false );
		node->setMaterialTexture( 0, driver->getTexture( meshNode.textureFilename.c_str() ) );
	}

	if ( bTestCollision )
	{
		// 创建碰撞的三角形选择器以支持碰撞检测
		scene::ITriangleSelector* selector = smgr->createTriangleSelector( (scene::IAnimatedMeshSceneNode*)node );
		node->setTriangleSelector(selector);
		selector->drop();
	}

	return node;
}



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

	auto print = []( const PythonSColor& pcolor )
	{
		std::cout << pcolor.alpha << ' ' <<  pcolor.red << ' ' <<  pcolor.green << ' ' <<  pcolor.blue << std::endl;
	};

	print( light.AmbientColor );
	print( light.DiffuseColor );
	print( light.SpecularColor );
	std::cout << x << ' ' << y << ' ' << z << std::endl;
}

PythonSceneNode ModelManagerSlaver::AddSceneNodeByMeshID( const std::string& meshID, bool bTestCollision /*= false */ )
{
	ModelManager* pModelMan = MyIrrlichtEngine::GetEngine()->GetModelManager();

	PythonSceneNode node;
	scene::ISceneNode* pNode = pModelMan->AddSceneNodeFromMesh( meshID, bTestCollision );
	node.ptr = pNode;
	return node;
}
