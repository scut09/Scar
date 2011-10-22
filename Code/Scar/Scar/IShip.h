/********************************************************************
    创建时间: 2011-10-22   11:44
    文件名:   IShip.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:		舰船接口，派生于CMeshSceneNode，已经拥有绘图基本功能，
			只需要为其添加Mesh即可。
				所以我们现在只需要关注与舰船的基本属性，而不需要把注意力放在绘图上

*********************************************************************/


#ifndef IShip_h__
#define IShip_h__

#include "CMeshSceneNode.h"

using namespace irr;

/*
** 名字：IShip
** 说明：舰船接口类，提供舰船的基本接口
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
	f32		MaxSpeed;			// 最大速度
	f32		Acceleration;		// 加速度
	f32		Sensitivity;		// 灵敏度

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