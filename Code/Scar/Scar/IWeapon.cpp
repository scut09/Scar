#include "IWeapon.h"
#include "IShip.h"
#include <iostream>
#include "irrlicht.h"

//IWeapon::IWeapon( irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, s32 id, const core::vector3df& position, const core::vector3df& rotation, const core::vector3df& scale ) : CMeshSceneNode( mesh, parent, mgr, id, position, rotation, scale )
//{
//	setParent( mgr->getRootSceneNode() );
//	setVisible( false );
//}


IWeapon::IWeapon( irr::scene::ISceneManager* mgr, 
	irr::scene::ISceneNode* parent,
	s32 id, const irr::core::vector3df& position, 
	const irr::core::dimension2d<f32>& size, 
	irr::video::SColor colorTop/*=video::SColor(0xFFFFFFFF)*/,
	video::SColor colorBottom/*=video::SColor(0xFFFFFFFF)*/ )
	: CBillboardSceneNode( parent, mgr, id, position, size, colorTop, colorBottom )
{
		setParent( mgr->getRootSceneNode() );
		setVisible( false );

		Interval = 250;
		Velocity = 20;
		Life = 2000;
}

void IWeapon::OnCollision( scene::ISceneNode* target )
{
	if ( typeid( *target ) == typeid( IShip ) )
	{
		IShip* ship = dynamic_cast<IShip*>( target );
		ship->LifeDissolveByAttack( 10 );
	}

	std::cout << "Hit\n";
}

const u32 IWeapon::GetInterval() const
{
	return Interval;
}

void IWeapon::SetInterval( u32 interval )
{
	Interval = interval;
}

const f32 IWeapon::GetVelocity() const
{
	return Velocity;
}

void IWeapon::SetVelocity( f32 velocity )
{
	Velocity = velocity;
}

const u32 IWeapon::GetLife() const
{
	return Life;
}

void IWeapon::SetLife( u32 life )
{
	Life = life;
}

const s32 IWeapon::GetRemain() const
{
	return Remain;
}

void IWeapon::SetRemain( s32 num )
{
	Remain = num;
}

const s32 IWeapon::GetDamage() const
{
	return Damage;
}

void IWeapon::SetDamage( s32 damage )
{
	Damage = damage;
}
