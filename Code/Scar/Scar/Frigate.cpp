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
