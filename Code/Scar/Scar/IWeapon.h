/********************************************************************
    创建时间: 2011-10-22   19:19
    文件名:   IWeapon.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     武器

*********************************************************************/


#ifndef IWeapon_h__
#define IWeapon_h__

#include <typeinfo>
#include "CMeshSceneNode.h"

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




/*
** 名字：IWeapon
** 说明：武器基类
**
*/
class IWeapon : public irr::scene::CMeshSceneNode, public IWeaponCollisionCallback
{
public:
	IWeapon( irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr, s32 id,
		const core::vector3df& position, const core::vector3df& rotation,
		const core::vector3df& scale );


	virtual void OnCollision( scene::ISceneNode* target );

	
	//! 克隆一个自己，主要在发射导弹/炮弹的时候的可以复制一份武器出来
	virtual irr::scene::ISceneNode* Clone( irr::scene::ISceneNode* newParent, irr::scene::ISceneManager* newManager ) = 0;

protected:
	//! 复制IWeapon的属性给w，提供给派生类拷贝IWeapon的属性
	virtual void CloneAttributeTo( IWeapon* w )
	{
		Amount = w->Amount;
		Damage = w->Damage;
	}

private:
	//! 禁止使用CMeshSceneNode的clone函数
	virtual ISceneNode* clone( irr::scene::ISceneNode* newParent=0, irr::scene::ISceneManager* newManager=0 )
	{
		return NULL;
	}

protected:

	s32		Amount;			// 武器余量
	s32		Damage;			// 杀伤力

};




#endif // IWeapon_h__