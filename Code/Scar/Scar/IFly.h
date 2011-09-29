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
#include "def.h"
#include <irrlicht.h>

using namespace irr;
using boost::shared_ptr;

class IFlyBehavior;

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
	// 函数名:  IFly::Drop
	// 返回值:  void
	// 函数修饰:
	// 描述：   删除内部节点
	//************************************
	virtual void Drop() = 0;

	//************************************
	// 函数名:  IFly::SetSpeed
	// 返回值:  void
	// 参数:    const core::vector3df & speed
	// 函数修饰:
	// 描述：   设置速度，一个方向向量
	//************************************
	virtual void SetSpeed( const core::vector3df& speed ) = 0;

	//************************************
	// 函数名:  IFly::GetSpeed
	// 返回值:  core::vector3df
	// 函数修饰:
	// 描述：   获取速度，一个方向向量
	//************************************
	virtual core::vector3df GetSpeed() = 0;

	//************************************
	// 函数名:  IFly::AddFlyBehavior
	// 返回值:  void
	// 参数:    shared_ptr<IFlyBehavior> pBehavior
	// 函数修饰:
	// 描述：   添加一个飞行的行为。飞行物在每次飞行时
	//			会使用所有添加进来的飞行行为来完成一个瞬间的飞行动作
	//************************************
	virtual void AddFlyBehavior( shared_ptr<IFlyBehavior> pBehavior ) = 0;

	//************************************
	// 函数名:  IFly::RemoveFlyBehavior
	// 返回值:  void
	// 参数:    shared_ptr<IFlyBehavior> pBehavior
	// 函数修饰:
	// 描述：   从飞行行为列表中删除一个飞行行为.
	//************************************
	virtual void RemoveFlyBehavior( shared_ptr<IFlyBehavior> pBehavior ) = 0;
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
	// 函数名:  IFlyBehavior::Fly
	// 返回值:  core::vector3df
	// 参数:    const core::vector3df & pos
	// 函数修饰:
	// 描述：   
	//************************************
	virtual void Fly( IFly* pFlyObject ) = 0;


};


#endif
