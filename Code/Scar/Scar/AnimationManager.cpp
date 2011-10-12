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
}

void AnimationManager::AddFlyableNode( scene::ISceneNode* pNode, shared_ptr<IFly> pFly )
{
	m_nodeMovMap[ pNode ] = pFly;
}

void AnimationManager::RemoveAll()
{
	m_nodeMovMap.clear();
}

void AnimationManager::RemoveNode( scene::ISceneNode* pNode )
{
	auto iter = m_nodeMovMap.find( pNode );
	if ( iter != m_nodeMovMap.end() )
	{
		m_nodeMovMap.erase( iter );
	}
}
