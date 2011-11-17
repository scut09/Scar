/********************************************************************
    创建时间: 2011-10-22   11:50
    文件名:   IShip.cpp
    作者:     
    说明:     

*********************************************************************/

#include "IShip.h"
#include <algorithm>


//void IShip::Move(u32 time) 
//{
//	if (Speed.getLength()>MaxSpeed)
//	{
//		Speed = Speed.normalize()*MaxSpeed;
//	}
//
//	if (Acceleration.getLength()>MaxAcceleration)
//	{
//		Acceleration = Acceleration.normalize()*MaxAcceleration;
//	}
//
//	vector3df pos = getPosition();
//	pos+=(f32)time * Speed+Acceleration*((f32)0.5*(f32)time * (f32)time);
//		setPosition(pos);
//}

//void IShip::RecoverLifePerSecond( const u32& pass )
//{
//	static u32 time = 0;
//	time +=pass;
//	if (time>=1000)
//	{
//		CurrentShield+= RecoverLife;
//		time = 0;
//	}
//	if (CurrentShield>MaxShield)
//	{
//		CurrentShield = MaxShield;
//	}
//}

//void IShip::RecoverLifeOneTime( const u32&addlife )
//{
//	CurrentShield += addlife;
//	if (CurrentShield>MaxShield)
//	{
//		CurrentShield = MaxShield;
//	}
//}

//void IShip::MaxLifeUpByGrade()
//{
//	if (CurrentGrade == NextGrade)
//	{MaxShield+=LifeAddPerGrade;
//	NextGrade = CurrentGrade+1;
//	}
//}


IShip::IShip( irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr,
	s32 id, const core::vector3df& position /*= core::vector3df(0,0,0)*/,
	const core::vector3df& rotation /*= core::vector3df(0,0,0)*/,
	const core::vector3df& scale /*= core::vector3df(1.0f, 1.0f, 1.0f) */ ) 
	: CMeshSceneNode( mesh, parent, mgr, id, position, rotation, scale )
	, UpVector( core::vector3df( 0.f, 1.f, 0.f ) )
	, Target( core::vector3df( 0.f, 0.f, 100.f ) )
{
	if ( !parent )
	{
		this->setParent( mgr->getRootSceneNode() );
		drop();											// 已经加入场景树，自己的引用计数器减一
	}
	Money = 0;
	// 创建碰撞的三角形选择器以支持碰撞检测	[ 华亮 2011-10-29 ]
	scene::ITriangleSelector* selector = mgr->createTriangleSelector( mesh, (ISceneNode*)this );
	this->setTriangleSelector(selector);
	selector->drop();
}


void IShip::GradeUpByExperience()
{
	if (Experience>=ExperienceToGrade)
	{
		CurrentGrade ++;
		if (CurrentGrade>MaxGrade)
		{
			Experience = ExperienceToGrade;
			CurrentGrade=MaxGrade;
		}
		else Experience = Experience - ExperienceToGrade;

	}
}

void IShip::RefreshAttrbutes( const u32& time )
{
	GradeUpByExperience();
	//MaxLifeUpByGrade();
}

void IShip::initShip( const std::wstring& name,const f32& maxspeed/*=10*/, const vector3df& speed/*=vector3df(0,1,0)*/,
	const vector3df& acceleration/*=vector3df(0,0,0)*/, const f32& maxaccleration/*=1*/,
	const f32& sensitivity/*=1*/, const f32& maxlife/*=1000*/, const f32& currentlife/*=1000*/, 
	const f32& lifeaddpergrade/*=1000*/, const f32& defence/*=2*/, const u32& shield/*=1*/, 
	const u32& currentgrade/*=0*/, const u32& nextgrade/*=1*/, const u32&maxgrade/*=10*/, const f32& inertance/*=1*/, 
	const f32& recoverLife/*=10*/, const f32& experience/*=0*/, const f32& experiencetograde/*=100 */ )
{
	MaxSpeed = maxspeed;
	Velocity = 0;
	MaxShield = 1000;
	CurrentShield = MaxShield;

	Speed    = speed;
	Acceleration = acceleration;
	MaxAcceleration = maxaccleration;
	Sensitivity = sensitivity;
	CurrentShield = currentlife;
	LifeAddPerGrade = lifeaddpergrade;
	Defence = defence;
	Name = name;
	Shield = shield;
	CurrentGrade = currentgrade;
	NextGrade = nextgrade;
	MaxGrade = maxgrade;
	Inertance = inertance;
	RecoverLife = recoverLife;
	Experience = experience;
	ExperienceToGrade = experiencetograde;
}

void IShip::AddGun( IWeapon* gun )
{
	if ( !gun ) return;
	if ( Guns.size() >= GunEquitCount )
		return;
	gun->grab();
	Guns.push_back( gun );
}

void IShip::RemoveGun( IWeapon* gun )
{
	auto itr = std::find( Guns.begin(), Guns.end(), gun );
	int diff = itr - Guns.begin();
	Guns.erase( Guns.begin() + diff );
	gun->drop();
}

void IShip::RemoveGuns()
{
	for ( auto iter = Guns.begin(); iter != Guns.end(); ++iter )
	{
		(*iter)->drop();
	}
	Guns.clear();
}

const std::vector< IWeapon* >& IShip::GetGuns() const
{
	return Guns;
}

const std::vector< IWeapon* >& IShip::GetMissles() const
{
	return Missiles;
}

void IShip::AddMissles( IWeapon* missile )
{
	if ( !missile ) return;
	if ( Missiles.size() >= MissileEquitCount )
		return;
	missile->grab();
	Missiles.push_back( missile );
}

void IShip::RemoveMissle( IWeapon* missile )
{
	auto itr = std::find( Missiles.begin(), Missiles.end(), missile );
	int diff = itr - Missiles.begin();
	Missiles.erase( Missiles.begin() + diff );
	missile->drop();
}

void IShip::RemoveMissles()
{
	for ( auto iter = Missiles.begin(); iter != Missiles.end(); ++iter )
	{
		(*iter)->drop();
	}
	Missiles.clear();
}


void IShip::SetShield( const f32 shield )
{
	CurrentShield = shield;
	if ( CurrentShield < 0 )
		CurrentShield = 0;
}

const f32 IShip::GetShield() const
{
	return CurrentShield;
}

void IShip::SetMaxShield( const f32& maxShield )
{
	MaxShield = maxShield;
}

const f32 IShip::GetMaxShield() const
{
	return MaxShield;
}

const f32 IShip::GetMaxArmor() const
{
	return MaxArmor;
}

void IShip::SetMaxArmor( f32 maxArmor )
{
	MaxArmor = maxArmor;
}

const f32 IShip::GetArmor() const
{
	return CurrentArmor;
}

void IShip::SetArmor( f32 armor )
{
	CurrentArmor = armor;
}

void IShip::SetEnergy( u32 en )
{
	Energy = en;
}

const u32 IShip::GetEnergy() const
{
	return Energy;
}

IShip::~IShip()
{
	RemoveGuns();
}

void IShip::SetMaxEnergy( u32 en )
{
	MaxEnergy = en;
}

const u32 IShip::GetMaxEnergy() const
{
	return MaxEnergy;
}

void IShip::SetMoney( u32 money )
{
	Money  = money;
}

irr::u32 IShip::GetMoney() const
{
	return Money;
}

irr::u32 IShip::GetMaxMoney() const
{
	return MaxMoney;
}

void IShip::SetMaxMoney( u32 money )
{
	MaxMoney = money;
}

irr::s32 IShip::GetTeam() const
{
	return Team;
}

void IShip::SetTeam( s32 team )
{
	Team = team;
}
