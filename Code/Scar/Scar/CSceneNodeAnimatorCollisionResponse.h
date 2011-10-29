/********************************************************************
    创建时间: 2011-10-22   20:03
    文件名:   CSceneNodeAnimatorCollisionResponse.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     命中响应Animator

*********************************************************************/


#ifndef CSceneNodeAnimatorCollisionResponse_h__
#define CSceneNodeAnimatorCollisionResponse_h__

#include <irrlicht.h>
#include <functional>

using namespace irr;
using namespace scene;

typedef std::function< void( ISceneNode* node, ISceneNode* target_node ) >	CollisionCallbackType;

/*
** 名字：CSceneNodeAnimatorCollisionResponse
** 说明：碰撞响应
**
*/
class CSceneNodeAnimatorMyCollisionResponse : public ISceneNodeAnimator
{
public:
	CSceneNodeAnimatorMyCollisionResponse( ISceneCollisionManager* col );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone(
		ISceneNode* node,
		ISceneManager* newManager = 0 );

	// 设置碰撞时的回调函数
	void SetCollisionCallback( CollisionCallbackType func )
	{
		Func = func;
	}

private:
	ISceneCollisionManager*		CollisionMgr;
	core::vector3df				LastPoint;			// 上次的点
	bool						FirstRun;			// 是否第一次运行
	CollisionCallbackType		Func;				// 碰撞时的回调
};




#endif // CSceneNodeAnimatorCollisionResponse_h__