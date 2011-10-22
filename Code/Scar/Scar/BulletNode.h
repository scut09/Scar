/********************************************************************
    创建时间: 2011-10-22   19:56
    文件名:   BulletNode.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     炮弹节点

*********************************************************************/

#ifndef BulletNode_h__
#define BulletNode_h__

#include "IWeapon.h"

/*
** 名字：BulletNode
** 说明：炮弹
**
*/
class BulletNode : public IWeapon
{
public:
	BulletNode( irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr, s32 id,
		const core::vector3df& position, const core::vector3df& rotation,
		const core::vector3df& scale )
		: IWeapon( mesh, parent, mgr, id, position, rotation, scale )
	{
	}

	irr::scene::ISceneNode* Clone( irr::scene::ISceneNode* newParent, irr::scene::ISceneManager* newManager )
	{
		if ( ! newParent ) newParent = Parent;
		if ( ! newManager ) newManager = SceneManager;


		BulletNode* nb = new BulletNode( Mesh, newParent,
			newManager, ID, RelativeTranslation, RelativeRotation, RelativeScale );

		nb->setVisible( true );

		// 复制ISceneNode基本属性
		nb->cloneMembers( this, newManager );
		nb->ReadOnlyMaterials = ReadOnlyMaterials;
		nb->Materials = Materials;

		if ( newParent )
			nb->drop();

		// 复制基本属性给新的MissileNode
		CloneAttributeTo( nb );

		return nb;
	}

};




#endif // BulletNode_h__