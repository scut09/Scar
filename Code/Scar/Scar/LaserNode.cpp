
#include "LaserNode.h"
#include "Toolkit.h"
#include "MyIrrlichtEngine.h"


LaserNode::LaserNode( irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr,
	s32 id, ISceneNode* target, IShip* host,
	const core::vector3df& position /*= core::vector3df( 0, 0, 0 )*/,
	const core::vector3df& rotation /*= core::vector3df( 0, 0, 0 )*/,
	const core::vector3df& scale /*= core::vector3df( 1.f, 1.f, 1.f ) */ )
	: CMeshSceneNode( mesh, parent, mgr, id, position, rotation, scale )
{
	if ( !parent )
	{
		this->setParent( mgr->getRootSceneNode() );
		drop();
	}
	Target = target;
	Host = host;
	Length = 11.6f;
	this->setScale( core::vector3df( 0.0156f, 0.0156f, 1.0f ) );
	IsLock = true;
} 

void LaserNode::build()
{
	if ( IsLock )
	{
		ICameraSceneNode* camera = MyIrrlichtEngine::GetEngine()->GetSceneManager()->getActiveCamera();
		IVideoDriver* driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
		Toolkit toolkit( MyIrrlichtEngine::GetEngine()->GetSceneManager()->getActiveCamera(), driver );
		position2df target2d;
		toolkit.To2DScreamPos( Target->getPosition(), &target2d );
		s32 width = driver->getViewPort().getWidth(), height = driver->getViewPort().getHeight();
		target2d = target2d - position2df( (f32)width * 0.5f, (f32)height * 0.5f );
		if ( target2d.getLength() < 293 )
		{
			this->setVisible( true );
			f32 targetLength = ( Target->getPosition() - Host->getPosition() ).getLength();
			vector3df currentposition = ( Target->getPosition() + Host->getPosition() ) * 0.5f;
			this->setPosition( currentposition );
			this->setScale( vector3df( 0.0625f, 0.0625f, targetLength / Length ) );
			this->setRotation( ( Target->getPosition() - Host->getPosition() ).getHorizontalAngle() );
		}
		else
			setVisible( false );
	}
	else
	{

	}
}

void LaserNode::setTarget( ISceneNode* target )
{
	Target = target;
	this->build();
}

void LaserNode::setLock( bool islock )
{
	IsLock = islock;
}

