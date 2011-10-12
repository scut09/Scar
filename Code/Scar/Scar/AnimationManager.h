/********************************************************************
	创建时间: 2011-9-27   14:56
	文件名:   AnimationManager.h
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     动画管理，已经过时，请不要再使用这个类。
			现在使用irrlicht引擎内部的动画来管理。

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
	typedef std::map<scene::ISceneNode*, shared_ptr<IMovable> > ModelMap;
	ModelMap m_nodeMovMap;
	
	void Run();

	void AddMovableNode( scene::ISceneNode* pNode, shared_ptr<IMovable> pMove );

	void AddFlyableNode( scene::ISceneNode* pNode, shared_ptr<IFly> pFly );

	void RemoveNode( scene::ISceneNode* pNode );

	void RemoveAll();

};

#endif