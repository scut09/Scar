/*
** 作者：华亮
** 说明：
**
*/

#include "base.h"

#include <irrlicht.h>

#ifndef _IFLY_H_
#define _IFLY_H_

using namespace irr;


/*
** 名字：IFly
** 说明：可飞行物体的接口
**
*/
class IFly : public IMovable
{
public:
	virtual void LoadSceneNode( scene::ISceneNode* pNode ) = 0;
	virtual scene::ISceneNode* GetSceneNode() = 0;
	virtual void SetPostion( const core::vector3df& pos ) = 0;					// 设置位置
	virtual void SetRotation( const core::vector3df& rot ) = 0;					// 设置旋转角度，这个待商榷
	virtual core::vector3df GetPosition() = 0;		// 获取位置
	virtual scene::ISceneNode* TestCollision() = 0;	// 是否有碰撞
	virtual void Drop() = 0;
};


/*
** 名字：IFlyBehavior
** 说明：飞行的行为
**
*/
class IFlyBehavior
{
public:
	virtual void SetOwner( IFly* pFly ) = 0;	
	virtual core::vector3df Fly( const core::vector3df& pos ) = 0;
	virtual core::vector3df GetDirection() = 0;
};


#endif
