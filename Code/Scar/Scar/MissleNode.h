#ifndef MissileNode_h__
#define MissileNode_h__


#include "CMeshSceneNode.h"
#include <string>
#include <vector>
#include <irrlicht.h>
#include "IShip.h"
#include "IWeapon.h"

using namespace irr;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using core::vector3df;

class MissleNode : public IWeapon
{
public:
	MissleNode( irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr, s32 id,
		const core::vector3df& position = core::vector3df( 0, 0, 0 ),
		const core::vector3df& rotation = core::vector3df( 0, 0, 0 ),
		const core::vector3df& scale = core::vector3df( 1.f, 1.f, 1.f ) );

	void setTarget( ISceneNode* target );

	ISceneNode* getTarget();
	
	//! frame
	virtual void OnRegisterSceneNode();

	//! renders the node.
	virtual void render();

	//! returns the axis aligned bounding box of this node
	virtual const core::aabbox3d<f32>& getBoundingBox() const;

	//! returns the material based on the zero based index i. To get the amount
	//! of materials used by this scene node, use getMaterialCount().
	//! This function is needed for inserting the node into the scene hirachy on a
	//! optimal position for minimizing renderstate changes, but can also be used
	//! to directly modify the material of a scene node.
	virtual video::SMaterial& getMaterial(u32 i);

	//! returns amount of materials used by this scene node.
	virtual u32 getMaterialCount() const;

	//! Writes attributes of the scene node.
	virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;

	//! Reads attributes of the scene node.
	virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);

	//! Returns type of the scene node
	virtual ESCENE_NODE_TYPE getType() const { return ESNT_MESH; }

	//! Sets a new mesh
	virtual void setMesh(IMesh* mesh);

	//! Returns the current mesh
	virtual IMesh* getMesh(void) { return Mesh; }

	//! Sets if the scene node should not copy the materials of the mesh but use them in a read only style.
	/* In this way it is possible to change the materials a mesh causing all mesh scene nodes 
	referencing this mesh to change too. */
	virtual void setReadOnlyMaterials(bool readonly);

	//! Returns if the scene node should not copy the materials of the mesh but use them in a read only style
	virtual bool isReadOnlyMaterials() const;

	//! Creates a clone of this scene node and its children.
	virtual ISceneNode* clone(ISceneNode* newParent=0, ISceneManager* newManager=0);

	//protected:

	void copyMaterials();

	core::array<video::SMaterial>	Materials;
	core::aabbox3d<f32>				Box;
	video::SMaterial				tmpReadOnlyMaterial;

	IMesh* Mesh;

	s32 PassCount;
	bool ReadOnlyMaterials;

private:
	f32 Length;
	ISceneNode* Target;

public:
	irr::scene::ISceneNode* Clone( irr::scene::ISceneNode* newParent, irr::scene::ISceneManager* newManager )
	{
		if (!newParent)
			newParent = Parent;
		if (!newManager)
			newManager = SceneManager;

		MissleNode* nb = new MissleNode( Mesh, Parent, newManager, ID );

		nb->cloneMembers(this, newManager);

		if ( newParent )
			nb->drop();

		// 复制基本属性给新的BulletNode
		nb->CloneAttributeFrom( this );
		//CloneAttributeFrom( nb );
		nb->setVisible( true );
		return nb;

	}

};
#endif // MissileNode_h__
