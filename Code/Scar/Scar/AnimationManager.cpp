#include "AnimationManager.h"


void AnimationManager::Run()
{
	std::for_each( 
		m_nodeMovMap.begin(), 
		m_nodeMovMap.end(), 
		[]( std::pair< scene::ISceneNode*, shared_ptr<IMovable> > iter ) { iter.second->Move(); });
}

void AnimationManager::AddMovableNode( scene::ISceneNode* pNode, shared_ptr<IMovable> pMove )
{
	m_nodeMovMap[ pNode ] = pMove;
	pNode->grab();
}

void AnimationManager::AddFlyableNode( scene::ISceneNode* pNode, shared_ptr<IFly> pFly )
{
	m_nodeMovMap[ pNode ] = pFly;
	pNode->grab();
}

void AnimationManager::RemoveAll()
{
	for ( auto iter = m_nodeMovMap.begin(); iter != m_nodeMovMap.end(); ++iter )
	{
		iter->first->drop();
		iter->first->remove();
	}
	m_nodeMovMap.clear();
}

void AnimationManager::RemoveNode( scene::ISceneNode* pNode )
{
	auto iter = m_nodeMovMap.find( pNode );
	if ( iter != m_nodeMovMap.end() )
	{
		m_nodeMovMap.erase( iter );
		pNode->drop();
	}
}
