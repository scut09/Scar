/********************************************************************
	����ʱ��: 2011-9-27   14:56
	�ļ���:   AnimationManager.h
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     ��������

*********************************************************************/


#ifndef _ANIMATIONMAMAGER_H_
#define _ANIMATIONMAMAGER_H_

#include "base.h"
#include "IFly.h"
#include <list>
#include <map>
#include <algorithm>
#include <irrlicht.h>

using namespace irr;

/*
** ���֣�AnimationManager
** ˵������������
**
*/
class AnimationManager
{
public:
	typedef std::map<scene::ISceneNode*, shared_ptr<IMovable> > ModelMap;
	ModelMap m_nodeMovMap;
	
	void Run()
	{
		std::for_each( 
			m_nodeMovMap.begin(), 
			m_nodeMovMap.end(), 
			[]( std::pair< scene::ISceneNode*, shared_ptr<IMovable> > iter ) { iter.second->Move(); });
	}

	void AddMovableNode( scene::ISceneNode* pNode, shared_ptr<IMovable> pMove )
	{
		m_nodeMovMap[ pNode ] = pMove;
	}

	void AddFlyableNode( scene::ISceneNode* pNode, shared_ptr<IFly> pFly )
	{
		m_nodeMovMap[ pNode ] = pFly;
	}

	void RemoveNode( scene::ISceneNode* pNode )
	{
		auto iter = m_nodeMovMap.find( pNode );
		if ( iter != m_nodeMovMap.end() )
		{
			m_nodeMovMap.erase( iter );
		}
	}


};

#endif