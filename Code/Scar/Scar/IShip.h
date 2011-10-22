/********************************************************************
    ����ʱ��: 2011-10-22   11:44
    �ļ���:   IShip.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:		�����ӿڣ�������CMeshSceneNode���Ѿ�ӵ�л�ͼ�������ܣ�
			ֻ��ҪΪ�����Mesh���ɡ�
				������������ֻ��Ҫ��ע�뽢���Ļ������ԣ�������Ҫ��ע�������ڻ�ͼ��

*********************************************************************/


#ifndef IShip_h__
#define IShip_h__

#include "CMeshSceneNode.h"

using namespace irr;

/*
** ���֣�IShip
** ˵���������ӿ��࣬�ṩ�����Ļ����ӿ�
**
*/
class IShip : public irr::scene::CMeshSceneNode
{
public:
	// IMeshSceneNode* node = new CMeshSceneNode(mesh, parent, this, id, position, rotation, scale);
	// 
	IShip( irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr,	s32 id,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f) )
		:
	CMeshSceneNode( mesh, parent, mgr, id, position, rotation, scale )
	{

	}

protected:
	f32		MaxSpeed;			// ����ٶ�
	f32		Acceleration;		// ���ٶ�
	f32		Sensitivity;		// ������

	// Armor

	// Shield

	//! Creates a clone of this scene node and its children.
	//ISceneNode* clone(ISceneNode* newParent, irr::scene::ISceneManager* newManager)
	//{
	//	if (!newParent) newParent = Parent;
	//	if (!newManager) newManager = SceneManager;

	//	CMeshSceneNode* nb = new CMeshSceneNode(Mesh, newParent,
	//		newManager, ID, RelativeTranslation, RelativeRotation, RelativeScale);

	//	nb->cloneMembers(this, newManager);
	//	nb->ReadOnlyMaterials = ReadOnlyMaterials;
	//	nb->Materials = Materials;

	//	if ( newParent )
	//		nb->drop();
	//	return nb;
	//}


};


#endif // IShip_h__