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
	
	void Run();

	void AddMovableNode( scene::ISceneNode* pNode, shared_ptr<IMovable> pMove );

	void AddFlyableNode( scene::ISceneNode* pNode, shared_ptr<IFly> pFly );

	void RemoveNode( scene::ISceneNode* pNode );

	void RemoveAll();

};

#endif