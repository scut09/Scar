//
///********************************************************************
//    创建时间: 2011-10-22   11:44
//    文件名:   Battleship.h
//    作者:     谢骏飞
//    说明:	  继承IShip基类,战列舰,特点主要在于攻击
//
//*********************************************************************/
//#ifndef Battleship_h__
//#define Battleship_h__
//
//
//
//#pragma once
//#include "iship.h"
//
//
//class CBattleship :
//	public IShip
//{
//public:
//	CBattleship(irr::scene::IAnimatedMesh* mesh, irr::scene::ISceneNode* parent,
//		irr::scene::ISceneManager* mgr,	s32 id,
//		const core::vector3df& position = core::vector3df(0,0,0),
//		const core::vector3df& rotation = core::vector3df(0,0,0),
//		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f)):
//	IShip( mesh,  parent,mgr,	id,position ,rotation ,scale )
//	{
//		initShip(L"战列舰");
//		HitDizzy = HitAdd = 1;
//		HitAddRefreshTime = HitDizzyRefreshTime = 1000;
//		RecordHitAddRefreshTime = RecordHitDizzyRefreshTime = 0;
//	}
//	~CBattleship(void);
//
//	//发动技能
//	virtual bool PerformHitDizzy();
//	virtual bool PerformHitAdd();
//
//	//重置技能 
//    virtual void ReSetHitAdd(const u32& time);
//	virtual void ReSetHitDizzy( const u32& time);
//
//	//修改和获取技能刷新时间
//	virtual void SetHitDizzyRefreshTime( const u32& time){ HitDizzyRefreshTime = time; }
//	virtual void SetHitAddRefreshTime ( const u32& time ) { HitAddRefreshTime = time; }
//	virtual u32  GetHitAddrefreshTime( ) const { return HitAddRefreshTime; }
//	virtual u32  GetHitDizzyRefreshTime()const { return HitDizzyRefreshTime; }
//
//	//启动和关闭技能
//	virtual void EnableHitDizzy(){ HitDizzy = true; }
//	virtual void DisableHitDizzy(){ HitDizzy = false;}
//	virtual void EnableHitAdd(){ HitAdd = true; }
//	virtual void DisableHitAdd(){ HitAdd = false; }
//
//	//刷新属性
//	virtual void RefreshAttrbutes( const u32& time){
//		ReSetHitAdd(time);
//		ReSetHitDizzy(time);
//		IShip::RefreshAttrbutes(time);
//	};
//
//private:
//	u32  RecordHitDizzyRefreshTime;          //记录过去的时间
//	u32  RecordHitAddRefreshTime;            //记录过去的时间
//protected:
//	bool HitDizzy;                           //击晕
//	u32  HitDizzyRefreshTime;                //击晕刷新时间
//	u32  HitAddRefreshTime;                  //加强伤害刷新时间
//	bool HitAdd;                             //加强伤害
//
//};
//
//#endif // Battleship_h__