/********************************************************************
	����ʱ��: 2011-9-28   0:18
	�ļ���:   ModelManager.cpp
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     

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
	// �����ã���������
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
		// ������ײ��������ѡ������֧����ײ���
		scene::ITriangleSelector* selector = smgr->createTriangleSelector( (scene::IAnimatedMeshSceneNode*)node );
		node->setTriangleSelector(selector);
		selector->drop();
	}

	m_ISceneNodeList.push_back( node );
	node->grab();

	return node;
}

void ModelManager::DeleteAll()
{
	for ( auto iter = m_ISceneNodeList.begin(); iter != m_ISceneNodeList.end(); ++iter )
	{
		(*iter)->remove();
		(*iter)->drop();
	}
	m_ISceneNodeList.clear();
}


