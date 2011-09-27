/********************************************************************
	创建时间: 2011:9:27   14:55
	文件名:   IFly.h
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     

*********************************************************************/

#ifndef _IFLY_H_
#define _IFLY_H_

#include "base.h"
#include "IMovable.h"

#include <irrlicht.h>

using namespace irr;

/*
** 名字：IFly
** 说明：可飞行物体的接口
**
*/
class IFly : public IMovable
{
public:

	//************************************
	// 函数名:  IFly::LoadSceneNode
	// 返回值:  void
	// 参数:    scene::ISceneNode * pNode
	// 函数修饰:
	// 描述：   为飞行物加载图形节点
	//************************************
	virtual void LoadSceneNode( scene::ISceneNode* pNode ) = 0;

	//************************************
	// 函数名:  IFly::GetSceneNode
	// 返回值:  scene::ISceneNode*
	// 函数修饰:
	// 描述：   获取飞行物中的模型节点
	//************************************
	virtual scene::ISceneNode* GetSceneNode() = 0;

	//************************************
	// 函数名:  IFly::SetPostion
	// 返回值:  void
	// 参数:    const core::vector3df & pos
	// 函数修饰:
	// 描述：   设置飞行物的相对于整个场景的位置
	//************************************
	virtual void SetPostion( const core::vector3df& pos ) = 0;		

	//************************************
	// 函数名:  IFly::SetRotation
	// 返回值:  void
	// 参数:    const core::vector3df & rot
	// 函数修饰:
	// 描述：   设置飞行物的旋转角度
	//************************************
	virtual void SetRotation( const core::vector3df& rot ) = 0;		

	//************************************
	// 函数名:  IFly::GetPosition
	// 返回值:  core::vector3df
	// 函数修饰:
	// 描述：   获取飞行物的位置
	//************************************
	virtual core::vector3df GetPosition() = 0;		// 获取位置

	//************************************
	// 函数名:  IFly::TestCollision
	// 返回值:  scene::ISceneNode*
	// 函数修饰:
	// 描述：   碰撞检测，历史遗留问题，待删除，改为回调函数处理碰撞问题
	//************************************
	virtual scene::ISceneNode* TestCollision() = 0;	// 是否有碰撞

	//************************************
	// 函数名:  IFly::Drop
	// 返回值:  void
	// 函数修饰:
	// 描述：   删除内部节点
	//************************************
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
	~IFlyBehavior() {}

	//************************************
	// 函数名:  IFlyBehavior::SetOwner
	// 返回值:  void
	// 参数:    IFly * pFly
	// 函数修饰:
	// 描述：   
	//************************************
	virtual void SetOwner( IFly* pFly ) = 0;	

	//************************************
	// 函数名:  IFlyBehavior::Fly
	// 返回值:  core::vector3df
	// 参数:    const core::vector3df & pos
	// 函数修饰:
	// 描述：   
	//************************************
	virtual core::vector3df Fly( const core::vector3df& pos ) = 0;

	//************************************
	// 函数名:  IFlyBehavior::GetDirection
	// 返回值:  core::vector3df
	// 函数修饰:
	// 描述：   
	//************************************
	virtual core::vector3df GetDirection() = 0;
};


#endif
