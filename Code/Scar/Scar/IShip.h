/********************************************************************
    创建时间: 2011-10-22   11:44
    文件名:   IShip.h
    作者:     谢骏飞
    说明:		舰船接口，派生于CMeshSceneNode，已经拥有绘图基本功能，
			只需要为其添加Mesh即可。
				所以我们现在只需要关注与舰船的基本属性，而不需要把注意力放在绘图上

*********************************************************************/


#ifndef IShip_h__
#define IShip_h__

#include "CMeshSceneNode.h"
#include <string>
#include "IWeapon.h"
#include <vector>
#include <irrlicht.h>

using namespace irr;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using core::vector3df;
using core::aabbox3df;
using core::dimension2df;

// 创建完后自动加载到场景树中，并且将引用计数设置为1

/*
** 名字：IShip
** 说明：舰船接口类，提供舰船的基本接口
**
*/
class IShip : public irr::scene::CMeshSceneNode
{
public:
	
	IShip( irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr,	s32 id,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f) );

protected:
	vector3df          Speed;                  // 速度 
	vector3df		   Acceleration;		   // 加速度
	f32                MaxAcceleration;        // 最大加速度 
	f32		           Sensitivity;	           // 灵敏度
	
	f32                LifeAddPerGrade;        // 每等级增加生命
	f32                Defence;                // 防御
	std::wstring       Name;                   // 船的类型名字
	u32                Shield;                 // 护盾类型
    u32                CurrentGrade;           // 等级
	u32                NextGrade;              // 下一等级
	u32                MaxGrade;               // 最大等级
	f32                Inertance;              // 惯性
    f32                RecoverLife;            // 恢复生命 
	f32                Experience;             // 经验值
	f32                ExperienceToGrade;      // 加等级的经验值
	   
	
	/************************************************************************/
	/* 下面才是真正用到的属性                                               */
	/************************************************************************/
	f32					MaxSpeed;				// 最大速度
	f32					Velocity;				// 速率
	u32					GunEquitCount;			// 最大主炮装备数量
	u32					MissileEquitCount;		// 最大飞弹种类装备数量
	std::vector< IWeapon* >		Guns;			// 主炮
	std::vector< IWeapon* >		Missiles;		// 飞弹
	f32					MaxShield;				// 最大护盾值
	f32					CurrentShield;          // 当前护盾值
	f32					MaxArmor;				// 最大护甲值
	f32					CurrentArmor;			// 当前护甲值
	u32					Energy;                 // 当前能量值
	u32					MaxEnergy;				// 最大能量值
	s32					Team;					// 队伍编号 一般情况下，0代表不加入任何队伍
	u32                 Money;                  // 金钱 
	u32					MaxMoney;				// 金钱上限

	/************************************************************************/
	/* 提供控制模型的辅助信息                                               */
	/************************************************************************/
	core::vector3df Target;
	core::vector3df UpVector;

public:
	virtual void setTarget(const core::vector3df& pos)
	{
		Target = pos;
	}

	virtual const core::vector3df& getTarget() const
	{
		return Target;
	}

	virtual void setUpVector(const core::vector3df& pos)
	{
		UpVector = pos;
	}

	virtual const core::vector3df& getUpVector() const
	{
		return UpVector;
	}

	bool OnEvent(const SEvent& event)
	{
		// send events to event receiving animators
		ISceneNodeAnimatorList::Iterator ait = Animators.begin();

		for (; ait != Animators.end(); ++ait)
			if ((*ait)->isEventReceiverEnabled() && (*ait)->OnEvent(event))
				return true;

		// if nobody processed the event, return false
		return false;
	}

public:
	
	virtual ~IShip();

	//初始化飞船的属性参数
	virtual void initShip(const std::wstring& name,const f32& maxspeed=10, const vector3df& speed=vector3df(0,1,0), 
		const vector3df& acceleration=vector3df(0,0,0), const f32& maxaccleration=1, const f32& sensitivity=1, 
		const f32& maxlife=1000, const f32& currentlife=1000, const f32& lifeaddpergrade=1000, const f32& defence=2, 
		const u32& shield=1, const u32& currentgrade=0, const u32& nextgrade=1, const u32&maxgrade=10, const f32& inertance=1,
		const f32& recoverLife=10, const f32& experience=0, const f32& experiencetograde=100 );

	//获取和设置飞船的队伍
	s32 GetTeam() const;
	void SetTeam( s32 team );

	//获取和修改飞船的金钱
	void SetMoney( u32 money);
	u32  GetMoney() const;
	u32 GetMaxMoney() const;
	void SetMaxMoney( u32 money );

	//获取和设置飞船的能量 
	void SetEnergy( u32 en );
	const u32 GetEnergy() const;
	void SetMaxEnergy( u32 en );
	const u32 GetMaxEnergy() const;

	//获取和设置飞船的主炮
	const std::vector< IWeapon* >& GetGuns() const;
	void AddGun( IWeapon* gun );
	void RemoveGun( IWeapon* gun );
	void RemoveGuns();

	//获取和设置飞船的飞弹
	const std::vector< IWeapon* >& GetMissles() const;
	void AddMissles( IWeapon* missile );
	void RemoveMissle( IWeapon* missile );
	void RemoveMissles();

	//获取和修改飞船速率
	virtual f32 GetVelocity() const { return Velocity; }
	virtual void SetVelocity( f32 velocity ) { Velocity = velocity; }

	//获取和修改飞船的护盾
	void SetShield(const f32 shield);
	const f32  GetShield()const;
	void SetMaxShield(const f32& maxShield);
	const f32  GetMaxShield()const;

	//获取和设置飞船的护甲
	const f32 GetMaxArmor() const;
	void SetMaxArmor( f32 maxArmor );
	const f32 GetArmor() const;
	void SetArmor( f32 armor );

	//////////////////////////////////////////////////////////////////////////////////////////

	//获取和修改飞船的速度
	virtual vector3df GetSpeed()const { return Speed; }
	virtual void SetSpeed( const vector3df& speed ) { Speed = speed; }

	//获取和修改飞船的最大速率
	virtual f32 GetMaxSpeed()const{return MaxSpeed;}
	virtual void SetMaxSpeed( const f32& maxspeed ){MaxSpeed = maxspeed;}

	//获取和修改飞船的经验值
	virtual void SetExperience( const f32&experience ){ Experience = experience; }
	virtual f32  GetExperience() const { return Experience;}

	//获取和修改飞船的每升一个等级需要的经验
	virtual void SetExperienceToGrade(const f32& experience){ ExperienceToGrade = experience;}
	virtual f32  GetExperienceToGrade()const{ return ExperienceToGrade;}

	//获取和修改飞船的当前等级
	virtual void SetCurrentGrade(const u32& grade){ CurrentGrade = grade;}
	virtual u32 GetCurrentGrade()const{ return CurrentGrade; }

	//获取和修改飞船的最高等级
	virtual void SetMaxGrade( const u32& grade ){ MaxGrade = grade; }
	virtual u32  GetMaxGrade() const { return MaxGrade; }
	
	//获取和修改飞船的升一个等级增加的生命上限
	virtual void SetAddLifePerGrade(const f32& addlife){LifeAddPerGrade = addlife;}
	virtual f32  GetAddLifePerGrade()const { return LifeAddPerGrade;}

	//获取和修改飞船的惯性
	virtual void SetInertance(const f32& inertance ){ Inertance = inertance;}
	virtual f32  GetInertance()const { return Inertance;}

	//获取和修改飞船的每秒恢复的生命值
	virtual void SetRecoverLife(const f32& recoverlife){ RecoverLife = RecoverLife; }
	virtual f32  GetRecoverLife()const{ return RecoverLife;}

	//获取和修改飞船的加速度
	virtual void SetAccleration(const vector3df& accl){Acceleration = accl;}
	virtual vector3df GetAccleration()const{return Acceleration;}

	//获取和修改飞船的最大加速度速率
	virtual void SetMaxAccleration( const f32& accl ){ MaxAcceleration = accl; }
	virtual f32 GetMaxAccleration() const { return MaxAcceleration; }

	

	//获取和修改飞船的防御力
	virtual void SetDefence( const f32 defence){ Defence = defence; }
	virtual f32  GetDefence()const { return Defence; }

	//获取和修改飞船的护盾类型
	virtual void SetShieldType(const u32& shield){ Shield = shield; }
	virtual u32  GetShieldType()const{return Shield; }

	//获取和修改飞船的名字
	virtual void SetName( const std::wstring& name ){ Name = name; }
	virtual std::wstring  GetName()const {return Name;}

	//获取和修改飞船的灵敏度
	virtual void SetSensitivity(const f32& sensitivity){ Sensitivity = sensitivity ;}
	virtual f32  GetSensitivity()const { return Sensitivity;};
	
	//每秒恢复生命值
	//virtual void RecoverLifePerSecond(const u32& pass);

	//一次性恢复生命值
	//virtual void RecoverLifeOneTime(const u32&addlife );
	
	//每升一级增加生命上限
	//virtual void MaxLifeUpByGrade();

	//等级随着经验值的增加而增加
	virtual void GradeUpByExperience();

	//受到攻击，当前生命值损失
	//virtual void LifeDissolveByAttack(const u32&attack){CurrentShield-=(attack - Defence);}
	
	//飞船移动
	//virtual void Move(u32 time);

	//刷新属性
	virtual void RefreshAttrbutes( const u32& time);
	
	



};




#endif // IShip_h__