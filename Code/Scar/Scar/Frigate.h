/********************************************************************
    创建时间: 2011-10-23  
    文件名:   Frigate.h
    作者:     谢骏飞
    说明:	  继承IShip基类,护卫舰,特点主要在于防守

*********************************************************************/
#pragma once
#include "iship.h"
class CFrigate :
	public IShip
{
public:
	CFrigate(irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr,	s32 id,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f)):
	IShip( mesh,  parent,mgr,	id,position ,rotation ,scale )
	{
		initShip(L"护卫舰");
		BuildWall = BuildAir =true;
		BuildWallRefreshTime = BuildAirRefreshTime =2000;
		RecordBuildWallRefreshTime = RecordBuildAirRefreshTime =0;
	}
	~CFrigate(void);

	//关闭和启动技能
	virtual void EnableBuildWall() { BuildWall = true ;}
	virtual void DisableBuildWall() { BuildWall = false; }
	virtual void EnableBuildAir() { BuildAir = true; }
	virtual void DisableBuildAir() { BuildAir = false; }

	//获取和修改技能刷新时间
	virtual void SetBuildWallRefreshTime( const u32& time){ BuildWallRefreshTime = time; }
	virtual u32 GetBuildWallRefreshTime() const { return BuildWallRefreshTime ;}
	virtual void SetBuildAirRefreshTime( const u32& time){ BuildAirRefreshTime = time; }
	virtual u32  GetBuildAirRefreshTime()const { return BuildAirRefreshTime; }

	//重置防御气体技能
	virtual void ResetBuildWall(const u32& time);

	//重置防御墙技能
	virtual void ResetBuildAir(const u32& time);

	//发动技能 
	virtual bool PerformBuildAir();
	virtual bool PerformBuildWall(){ Energy --;return BuildWall; }

	//更新属性
	virtual void RefreshAttrbutes(const u32& time);
private:
	u32 RecordBuildWallRefreshTime;
	u32 RecordBuildAirRefreshTime;
protected:
	bool BuildWall;                      //防御墙技能
	u32  BuildWallRefreshTime;           //防御墙技能刷新时间
	u32  BuildAirRefreshTime;           //防御气体技能刷新时间
	bool BuildAir;                      //防御气体技能
};

