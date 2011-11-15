#ifndef LaserNode_h__
#define LaserNode_h__


#include "CMeshSceneNode.h"
#include <string>
#include <vector>
#include <irrlicht.h>

using namespace irr;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using core::vector3df;

class LaserNode : public irr::scene::CMeshSceneNode
{
public:
	LaserNode( irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr, s32 id,
		ISceneNode* target,
		ISceneNode* host,
		const core::vector3df& position = core::vector3df( 0, 0, 0 ),
		const core::vector3df& rotation = core::vector3df( 0, 0, 0 ),
		const core::vector3df& scale = core::vector3df( 1.f, 1.f, 1.f ) );
	void setTarget( ISceneNode* target );
	void build();
	void setLock( bool islock );
private:
	bool IsLock;
	f32 Length;
	ISceneNode* Host;
	ISceneNode* Target;
};
#endif // LaserNode_h__
