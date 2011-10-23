/********************************************************************
    创建时间: 2011-10-23  
    文件名:   Cruiseship.h
    作者:     谢骏飞
    说明:	  继承IShip基类,巡航舰,特点主要在于敏捷

*********************************************************************/
#ifndef Cruiseship_h__
#define Cruiseship_h__


#include "iship.h"
class CCruiseship :
	public IShip



{
public:
	CCruiseship(irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr,	s32 id,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f)):
	IShip( mesh,  parent,mgr,	id,position ,rotation ,scale )
	{
		initShip(L"巡航舰");
		MoveImmediate =1;
		MoveImmediateRefreshTime = 3000;
	}
	~CCruiseship(void);

	//发动技能
	virtual bool PerformMoveImmediate(const vector3df&pos);
	
	//重置技能
	virtual void ReSetMoveImmediate( const u32& time);
	
	//获取和修改技能刷新时间
	virtual void SetMoveImmediateRefreshTime( const u32& time){  MoveImmediateRefreshTime = time; }
	virtual u32 GetMoveImmediateRefreshTime() { return MoveImmediateRefreshTime; }

	//启动和关闭技能
	virtual void EnableMoveImmediate(){ MoveImmediate = true; }
	virtual void DisableMoveImmediate() { MoveImmediate = false;}

	//刷新属性
	virtual void RefreshAttrbutes( const u32& time){
		ReSetMoveImmediate(time);
		IShip::RefreshAttrbutes(time);
	};

private:
	u32  RecordMoveImmediateRefreshTime;     //记录过去的时间
	
protected:
	bool MoveImmediate;                      //瞬间移动
	u32  MoveImmediateRefreshTime;           //瞬间移动刷新时间
	
};

#endif // Cruiseship_h__