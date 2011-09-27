/********************************************************************
	创建时间: 2011-9-27   14:56
	文件名:   AnimationManager.h
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     动画管理

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
** 名字：AnimationManager
** 说明：动画管理
**
*/
class AnimationManager
{
public:
	typedef std::map<scene::ISceneNode*, IMovable*> ModelMap;
	ModelMap m_nodeMovMap;
	
	void Run()
	{
		//std::for_each( m_nodeMovMap.begin(), m_nodeMovMap.end(), []( ModelMap::iterator& iter ) { iter->second->Move(); });
	}

	void AddMovableNode( scene::ISceneNode* pNode, IMovable* pMove )
	{
		m_nodeMovMap[ pNode ] = pMove;
	}

	void AddFlyableNode( scene::ISceneNode* pNode, IFly* pFly )
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