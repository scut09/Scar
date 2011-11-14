#include "Frigate.h"





CFrigate::~CFrigate(void)
{
}

bool CFrigate::PerformBuildAir()
{
	Energy--;return BuildAir;
}

void CFrigate::ResetBuildWall( const u32& time )
{
	if (RecordBuildWallRefreshTime>=BuildWallRefreshTime)
	{
		BuildWall = true;
		RecordBuildWallRefreshTime = 0;
	}
	else RecordBuildWallRefreshTime+=time;
}

void CFrigate::ResetBuildAir( const u32& time )
{
	if (RecordBuildAirRefreshTime>=BuildAirRefreshTime)
	{
		RecordBuildAirRefreshTime = 0;
		BuildAir = true;
	}
	else RecordBuildAirRefreshTime += time;
}

void CFrigate::RefreshAttrbutes( const u32& time )
{
	ResetBuildAir(time);
	ResetBuildWall(time);
	IShip::RefreshAttrbutes(time);
}

CFrigate::CFrigate( irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, s32 id, const core::vector3df& position /*= core::vector3df(0,0,0)*/, const core::vector3df& rotation /*= core::vector3df(0,0,0)*/, const core::vector3df& scale /*= core::vector3df(1.0f, 1.0f, 1.0f)*/ ) :
IShip( mesh,  parent,mgr,	id,position ,rotation ,scale )
{
	initShip(L"ª§Œ¿Ω¢");
	BuildWall = BuildAir =true;
	BuildWallRefreshTime = BuildAirRefreshTime =2000;
	RecordBuildWallRefreshTime = RecordBuildAirRefreshTime =0;

	MaxEnergy = Energy = 1000;
}
