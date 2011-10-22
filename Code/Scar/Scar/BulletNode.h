/********************************************************************
    ����ʱ��: 2011-10-22   19:56
    �ļ���:   BulletNode.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     �ڵ��ڵ�

*********************************************************************/

#ifndef BulletNode_h__
#define BulletNode_h__

#include "IWeapon.h"

/*
** ���֣�BulletNode
** ˵�����ڵ�
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

		// ����ISceneNode��������
		nb->cloneMembers( this, newManager );
		nb->ReadOnlyMaterials = ReadOnlyMaterials;
		nb->Materials = Materials;

		if ( newParent )
			nb->drop();

		// ���ƻ������Ը��µ�MissileNode
		CloneAttributeTo( nb );

		return nb;
	}

};




#endif // BulletNode_h__