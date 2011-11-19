/********************************************************************
    创建时间: 2011-10-22   19:19
    文件名:   IWeapon.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     武器

*********************************************************************/


#ifndef IWeapon_h__
#define IWeapon_h__

#include <typeinfo>
#include <irrlicht.h>

using namespace irr;



/*
** 名字：ICollisionCallback
** 说明：碰撞回调
**
*/
class IWeaponCollisionCallback
{
public:
	virtual void OnCollision( scene::ISceneNode* target ) = 0;
};


using namespace irr;
using irr::scene::ISceneManager;
using irr::scene::ISceneNode;


/*
** 名字：IWeapon
** 说明：武器基类
**
*/
class IWeapon : public irr::scene::ISceneNode, public IWeaponCollisionCallback
{
protected:
	u32 Interval;			// 发射间隔 ms
	f32 Velocity;			// 飞行速率 pixel / s
	u32 Life;				// 最大飞行时间 ms
	s32	Damage;				// 杀伤力
	s32 Remain;				// 弹药余量

public:

	IWeapon(ISceneNode* parent, ISceneManager* mgr, s32 id=-1,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f));


	virtual void OnCollision( scene::ISceneNode* target );

	// 设置和获取弹药余量
	const s32 GetRemain() const;
	void SetRemain( s32 num );

	// 设置和获取武器杀伤力
	const s32 GetDamage() const;
	void SetDamage( s32 damage );
	
	// 设置和获取发射间隔
	const u32 GetInterval() const;
	void SetInterval( u32 interval );

	// 设置和获取飞行速率
	const f32 GetVelocity() const;
	void SetVelocity( f32 velocity );

	// 设置和获取最大飞行时间
	const u32 GetLife() const;
	void SetLife( u32 life );
	
	//! 克隆一个自己，主要在发射导弹/炮弹的时候的可以复制一份武器出来
	virtual irr::scene::ISceneNode* Clone( irr::scene::ISceneNode* newParent, irr::scene::ISceneManager* newManager ) = 0;

protected:
	//! 复制IWeapon的属性给w，提供给派生类拷贝IWeapon的属性
	virtual void CloneAttributeFrom( IWeapon* w );

private:
	//! 禁止使用CMeshSceneNode的clone函数
	virtual ISceneNode* clone( irr::scene::ISceneNode* newParent=0, irr::scene::ISceneManager* newManager=0 )
	{
		return NULL;
	}

};




#endif // IWeapon_h__