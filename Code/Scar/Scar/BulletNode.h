/********************************************************************
    创建时间: 2011-10-22   19:56
    文件名:   BulletNode.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     炮弹节点

*********************************************************************/

#ifndef BulletNode_h__
#define BulletNode_h__

#include "IWeapon.h"

using namespace irr;
using namespace scene;

/*
** 名字：BulletNode
** 说明：炮弹
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
		const irr::core::vector3df& position = core::vector3df(0), 
		const irr::core::dimension2d<f32>& size = core::dimension2d<f32>(5,5),
		irr::video::SColor colorTop=video::SColor(0xFFFFFFFF),video::SColor colorBottom=video::SColor(0xFFFFFFFF))
		: IWeapon( parent, mgr, id, position )
	{
#ifdef _DEBUG
		setDebugName("CBillboardSceneNode");
#endif

		

		setSize(size);

		indices[0] = 0;
		indices[1] = 2;
		indices[2] = 1;
		indices[3] = 0;
		indices[4] = 3;
		indices[5] = 2;

		vertices[0].TCoords.set(1.0f, 1.0f);
		vertices[0].Color = colorBottom;

		vertices[1].TCoords.set(1.0f, 0.0f);
		vertices[1].Color = colorTop;

		vertices[2].TCoords.set(0.0f, 0.0f);
		vertices[2].Color = colorTop;

		vertices[3].TCoords.set(0.0f, 1.0f);
		vertices[3].Color = colorBottom;


	}

	//! pre render event
	virtual void OnRegisterSceneNode();

	//! render
	virtual void render();

	//! returns the axis aligned bounding box of this node
	virtual const core::aabbox3d<f32>& getBoundingBox() const;

	//! sets the size of the billboard
	virtual void setSize(const core::dimension2d<f32>& size);

	//! gets the size of the billboard
	virtual const core::dimension2d<f32>& getSize() const;

	virtual video::SMaterial& getMaterial(u32 i);

	//! returns amount of materials used by this scene node.
	virtual u32 getMaterialCount() const;

	//! Set the color of all vertices of the billboard
	//! \param overallColor: the color to set
	virtual void setColor(const video::SColor & overallColor);

	//! Set the color of the top and bottom vertices of the billboard
	//! \param topColor: the color to set the top vertices
	//! \param bottomColor: the color to set the bottom vertices
	virtual void setColor(const video::SColor & topColor, const video::SColor & bottomColor);

	//! Gets the color of the top and bottom vertices of the billboard
	//! \param[out] topColor: stores the color of the top vertices
	//! \param[out] bottomColor: stores the color of the bottom vertices
	virtual void getColor(video::SColor& topColor, video::SColor& bottomColor) const;

	//! Writes attributes of the scene node.
	virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;

	//! Reads attributes of the scene node.
	virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);

	//! Returns type of the scene node
	virtual ESCENE_NODE_TYPE getType() const { return ESNT_BILLBOARD; }

	//! Creates a clone of this scene node and its children.
	virtual ISceneNode* clone(ISceneNode* newParent=0, ISceneManager* newManager=0);

protected:

	core::dimension2d<f32> Size;
	core::aabbox3d<f32> BBox;
	video::SMaterial Material;

	video::S3DVertex vertices[4];
	u16 indices[6];

public:
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

		// 复制基本属性给新的BulletNode
		nb->CloneAttributeFrom( this );
		//CloneAttributeFrom( nb );
		nb->setVisible( true );


		return nb;

	}

};




#endif // BulletNode_h__