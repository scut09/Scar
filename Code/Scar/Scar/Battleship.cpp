//#include "Battleship.h"
//
//
//
//
//CBattleship::~CBattleship(void)
//{
//}
//
//bool CBattleship::PerformHitDizzy()
//{
//	if (HitDizzy)
//	{
//		Energy --;
//		HitDizzy = 0;
//		return true;
//	}
//	else return false;
//}
//
//bool CBattleship::PerformHitAdd()
//{
//	if (HitAdd)
//	{
//		HitAdd = 0;
//		Energy--;
//		return true;
//	}
//	else return false;
//}
//
//void CBattleship::ReSetHitDizzy( const u32& time )
//{
//	if (HitDizzyRefreshTime<=RecordHitDizzyRefreshTime)
//	{
//		HitDizzyRefreshTime = 1;
//		RecordHitDizzyRefreshTime = 0;
//	}
//	else RecordHitDizzyRefreshTime += time;
//}
//
//void CBattleship::ReSetHitAdd( const u32& time )
//{
//	if (HitAddRefreshTime<=RecordHitAddRefreshTime)
//	{
//		HitAddRefreshTime=1;
//		RecordHitAddRefreshTime  =0;
//	}
//	else RecordHitAddRefreshTime += time;
//}
//
