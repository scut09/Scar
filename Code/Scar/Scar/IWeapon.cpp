#include "IWeapon.h"
#include "IShip.h"


IWeapon::IWeapon( irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, s32 id, const core::vector3df& position, const core::vector3df& rotation, const core::vector3df& scale ) : CMeshSceneNode( mesh, parent, mgr, id, position, rotation, scale )
{
	setVisible( false );
}

void IWeapon::OnCollision( scene::ISceneNode* target )
{
	if ( typeid( *target ) == typeid( IShip ) )
	{
		IShip* ship = dynamic_cast<IShip*>( target );

	}
}
