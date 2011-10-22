/********************************************************************
    创建时间: 2011-10-22   11:50
    文件名:   IShip.cpp
    作者:     
    说明:     

*********************************************************************/

#include "IShip.h"



void IShip::Move(u32 time) 
{
	if (Speed.getLength()>MaxSpeed)
	{
		Speed = Speed.normalize()*MaxSpeed;
	}

	if (Acceleration.getLength()>MaxAcceleration)
	{
		Acceleration = Acceleration.normalize()*MaxAcceleration;
	}

	vector3df pos = getPosition();
	pos+=(f32)time * Speed+Acceleration*((f32)0.5*(f32)time * (f32)time);
		setPosition(pos);
}

void IShip::RecoverLifePerSecond( const u32& pass )
{
	static u32 time = 0;
	time +=pass;
	if (time>=1000)
	{
		CurrentLife+= RecoverLife;
		time = 0;
	}
	if (CurrentLife>MaxLife)
	{
		CurrentLife = MaxLife;
	}
}

void IShip::RecoverLifeOneTime( const u32&addlife )
{
	CurrentLife += addlife;
	if (CurrentLife>MaxLife)
	{
		CurrentLife = MaxLife;
	}
}

void IShip::MaxLifeUpByGrade()
{
	if (CurrentGrade == NextGrade)
	{MaxLife+=LifeAddPerGrade;
	NextGrade = CurrentGrade+1;
	}
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

void IShip::RefreshAttrbutes()
{
	GradeUpByExperience();
	MaxLifeUpByGrade();
}

void IShip::initShip( const std::wstring& name,const f32& maxspeed/*=10*/, const vector3df& speed/*=vector3df(0,1,0)*/, const vector3df& acceleration/*=vector3df(0,0,0)*/, const f32& maxaccleration/*=1*/, const f32& sensitivity/*=1*/, const f32& maxlife/*=1000*/, const f32& currentlife/*=1000*/, const f32& lifeaddpergrade/*=1000*/, const f32& defence/*=2*/, const u32& shield/*=1*/, const u32& currentgrade/*=0*/, const u32& nextgrade/*=1*/, const u32&maxgrade/*=10*/, const f32& inertance/*=1*/, const f32& recoverLife/*=10*/, const f32& experience/*=0*/, const f32& experiencetograde/*=100 */ )
{
	MaxSpeed = maxspeed;
	Speed    = speed;
	Acceleration = acceleration;
	MaxAcceleration = maxaccleration;
	Sensitivity = sensitivity;
	MaxLife = maxlife;
	CurrentLife = currentlife;
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
