#include "Cruiseship.h"




CCruiseship::~CCruiseship(void)
{
}

bool CCruiseship::PerformMoveImmediate( const vector3df&pos )
{
	if (MoveImmediate)
	{
		MoveImmediate = 0;
		Energy--;
		setPosition(pos);
		return true;
	}
	else return false;
}

void CCruiseship::ReSetMoveImmediate( const u32& time )
{
	if (MoveImmediateRefreshTime<=RecordMoveImmediateRefreshTime)
	{
		MoveImmediate = 1;
		RecordMoveImmediateRefreshTime = 0;
	}
	else RecordMoveImmediateRefreshTime += time;
}
