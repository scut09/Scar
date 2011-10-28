///********************************************************************
//    ����ʱ��: 2011-10-22   19:57
//    �ļ���:   MissileNode.h
//    ����:     ���� Cedric Porter [ Stupid ET ]	
//    ˵��:     ����
//
//*********************************************************************/
//
//
//#ifndef MissileNode_h__
//#define MissileNode_h__
//
//#include "IWeapon.h"
//
//
///*
//** ���֣�MissileNode
//** ˵��������
//**
//*/
//class MissileNode : public IWeapon
//{
//public:
//	MissileNode( irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent,
//		irr::scene::ISceneManager* mgr, s32 id = -1,
//		const core::vector3df& position = core::vector3df( 0, 0, 0 ),
//		const core::vector3df& rotation = core::vector3df( 0, 0, 0 ),
//		const core::vector3df& scale = core::vector3df( 1, 1, 1 ) )
//		: IWeapon( mesh, parent, mgr, id, position, rotation, scale )
//	{
//	}
//
//	
//
//	virtual irr::scene::ISceneNode* Clone( irr::scene::ISceneNode* newParent, irr::scene::ISceneManager* newManager )
//	{
//		if ( ! newParent ) newParent = Parent;
//		if ( ! newManager ) newManager = SceneManager;
//
//
//		MissileNode* nb = new MissileNode( Mesh, newParent,
//			newManager, ID, RelativeTranslation, RelativeRotation, RelativeScale );
//
//		nb->setVisible( true );
//
//		// ����ISceneNode��������
//		nb->cloneMembers( this, newManager );
//		nb->ReadOnlyMaterials = ReadOnlyMaterials;
//		nb->Materials = Materials;
//
//		if ( newParent )
//			nb->drop();
//
//		// ���ƻ������Ը��µ�MissileNode
//		CloneAttributeFrom( nb );
//
//		return nb;
//	}
//
//
//};
//
//
//#endif // MissileNode_h__