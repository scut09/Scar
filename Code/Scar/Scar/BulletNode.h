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
	//BulletNode( irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent,
	//	irr::scene::ISceneManager* mgr, s32 id,
	//	const core::vector3df& position, const core::vector3df& rotation,
	//	const core::vector3df& scale )
	//	: IWeapon( mesh, parent, mgr, id, position, rotation, scale )
	//{
	//}

	BulletNode( irr::scene::ISceneManager* mgr, 
		irr::scene::ISceneNode* parent = 0, s32 id = 1,	
		const irr::core::vector3df& position = vector3df(0), 
		const irr::core::dimension2d<f32>& size = core::dimension2d<f32>(5,5),
		irr::video::SColor colorTop=video::SColor(0xFFFFFFFF),video::SColor colorBottom=video::SColor(0xFFFFFFFF))
		: IWeapon( mgr, parent, id, position, size, colorTop, colorBottom )
	{

	}


	irr::scene::ISceneNode* Clone( irr::scene::ISceneNode* newParent, irr::scene::ISceneManager* newManager )
	{
		if (!newParent)
			newParent = Parent;
		if (!newManager)
			newManager = SceneManager;

		BulletNode* nb = new BulletNode(newManager,
			newParent, ID, RelativeTranslation, Size);

		nb->cloneMembers(this, newManager);
		nb->Material = Material;

		if ( newParent )
			nb->drop();

		// ���ƻ������Ը��µ�BulletNode
		nb->CloneAttributeFrom( this );
		//CloneAttributeFrom( nb );
		nb->setVisible( true );


		return nb;

	}

};




#endif // BulletNode_h__