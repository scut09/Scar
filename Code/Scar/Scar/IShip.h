/********************************************************************
    ����ʱ��: 2011-10-22   11:44
    �ļ���:   IShip.h
    ����:     л����
    ˵��:		�����ӿڣ�������CMeshSceneNode���Ѿ�ӵ�л�ͼ�������ܣ�
			ֻ��ҪΪ�����Mesh���ɡ�
				������������ֻ��Ҫ��ע�뽢���Ļ������ԣ�������Ҫ��ע�������ڻ�ͼ��

*********************************************************************/


#ifndef IShip_h__
#define IShip_h__

#include "CMeshSceneNode.h"
#include <string>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/*
** ���֣�IShip
** ˵���������ӿ��࣬�ṩ�����Ļ����ӿ�
**
*/
class IShip : public irr::scene::CMeshSceneNode
{
public:
	
	IShip( irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr,	s32 id,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f) )
		:
	CMeshSceneNode( mesh, parent, mgr, id, position, rotation, scale )
	{
		Money =0;
		Energy =1000;
	}

protected:
	
	f32		           MaxSpeed;			   // ����ٶ�
	vector3df          Speed;                  // �ٶ� 
	f32				   Velocity;			   // ����
	vector3df		   Acceleration;		   // ���ٶ�
	f32                MaxAcceleration;        // �����ٶ� 
	f32		           Sensitivity;	           // ������
	f32                MaxLife;                // �������ֵ
	f32                CurrentLife;            // ��ǰ����ֵ
	f32                LifeAddPerGrade;        // ÿ�ȼ���������
	f32                Defence;                // ����
	std::wstring       Name;                   // ������������
	u32                Shield;                 // ��������
    u32                CurrentGrade;           // �ȼ�
	u32                NextGrade;              // ��һ�ȼ�
	u32                MaxGrade;               // ���ȼ�
    f32                Inertance;              // ����
    f32                RecoverLife;            // �ָ����� 
	f32                Experience;             // ����ֵ
	f32                ExperienceToGrade;      // �ӵȼ��ľ���ֵ
	u32                Money;                  // ��Ǯ    
	u32                Energy;                 // ����

public:
	
	virtual ~IShip(void){};

	//��ʼ���ɴ������Բ���
	virtual void initShip(const std::wstring& name,const f32& maxspeed=10, const vector3df& speed=vector3df(0,1,0), 
		const vector3df& acceleration=vector3df(0,0,0), const f32& maxaccleration=1, const f32& sensitivity=1, 
		const f32& maxlife=1000, const f32& currentlife=1000, const f32& lifeaddpergrade=1000, const f32& defence=2, 
		const u32& shield=1, const u32& currentgrade=0, const u32& nextgrade=1, const u32&maxgrade=10, const f32& inertance=1,
		const f32& recoverLife=10, const f32& experience=0, const f32& experiencetograde=100 );
	
	//��ȡ���޸ķɴ�����
	virtual f32 GetVelocity() const { return Velocity; }
	virtual void SetVelocity( f32 velocity ) { Velocity = velocity; }

	//��ȡ���޸ķɴ������� 
	virtual void SetEnergy( const u32& en ){ Energy = en; }
	virtual u32   GetEnergy() const { return Energy;}

	//��ȡ���޸ķɴ��Ľ�Ǯ
	virtual void SetMoney( const u32& money) { Money  = money; }
	virtual u32  GetMoney() const { return Money; }
	//��ȡ���޸ķɴ����ٶ�
	virtual vector3df GetSpeed()const { return Speed; }
	virtual void SetSpeed( const vector3df& speed ) { Speed = speed; }

	//��ȡ���޸ķɴ����������
	virtual f32 GetMaxSpeed()const{return MaxSpeed;}
	virtual void SetMaxSpeed( const f32& maxspeed ){MaxSpeed = maxspeed;}

	//��ȡ���޸ķɴ��ľ���ֵ
	virtual void SetExperience( const f32&experience ){ Experience = experience; }
	virtual f32  GetExperience() const { return Experience;}

	//��ȡ���޸ķɴ���ÿ��һ���ȼ���Ҫ�ľ���
	virtual void SetExperienceToGrade(const f32& experience){ ExperienceToGrade = experience;}
	virtual f32  GetExperienceToGrade()const{ return ExperienceToGrade;}

	//��ȡ���޸ķɴ��ĵ�ǰ�ȼ�
	virtual void SetCurrentGrade(const u32& grade){ CurrentGrade = grade;}
	virtual u32 GetCurrentGrade()const{ return CurrentGrade; }

	//��ȡ���޸ķɴ�����ߵȼ�
	virtual void SetMaxGrade( const u32& grade ){ MaxGrade = grade; }
	virtual u32  GetMaxGrade() const { return MaxGrade; }
	
	//��ȡ���޸ķɴ�����һ���ȼ����ӵ���������
	virtual void SetAddLifePerGrade(const f32& addlife){LifeAddPerGrade = addlife;}
	virtual f32  GetAddLifePerGrade()const { return LifeAddPerGrade;}

	//��ȡ���޸ķɴ��Ĺ���
	virtual void SetInertance(const f32& inertance ){ Inertance = inertance;}
	virtual f32  GetInertance()const { return Inertance;}

	//��ȡ���޸ķɴ���ÿ��ָ�������ֵ
	virtual void SetRecoverLife(const f32& recoverlife){ RecoverLife = RecoverLife; }
	virtual f32  GetRecoverLife()const{ return RecoverLife;}

	//��ȡ���޸ķɴ��ļ��ٶ�
	virtual void SetAccleration(const vector3df& accl){Acceleration = accl;}
	virtual vector3df GetAccleration()const{return Acceleration;}

	//��ȡ���޸ķɴ��������ٶ�����
	virtual void SetMaxAccleration( const f32& accl ){ MaxAcceleration = accl; }
	virtual f32 GetMaxAccleration() const { return MaxAcceleration; }

	//��ȡ���޸ķɴ��ĵ�ǰ����ֵ
	virtual void SetCurrentLife(const f32 life){CurrentLife = life;}
	virtual f32  GetCurrentLife()const{return CurrentLife;}

	//��ȡ���޸ķɴ�����������
	virtual void SetMaxLife(const f32& maxlife){ MaxLife = maxlife; }
	virtual f32  GetMaxLife()const { return MaxLife; }

	//��ȡ���޸ķɴ��ķ�����
	virtual void SetDefence( const f32 defence){ Defence = defence; }
	virtual f32  GetDefence()const { return Defence; }

	//��ȡ���޸ķɴ��Ļ�������
	virtual void SetShield(const u32& shield){ Shield = shield; }
	virtual u32  GetShield()const{return Shield; }

	//��ȡ���޸ķɴ�������
	virtual void SetName( const std::wstring& name ){ Name = name; }
	virtual std::wstring  GetName()const {return Name;}

	//��ȡ���޸ķɴ���������
	virtual void SetSensitivity(const f32& sensitivity){ Sensitivity = sensitivity ;}
	virtual f32  GetSensitivity()const { return Sensitivity;};
	
	//ÿ��ָ�����ֵ
	virtual void RecoverLifePerSecond(const u32& pass);

	//һ���Իָ�����ֵ
	virtual void RecoverLifeOneTime(const u32&addlife );
	
	//ÿ��һ��������������
	virtual void MaxLifeUpByGrade();

	//�ȼ����ž���ֵ�����Ӷ�����
	virtual void GradeUpByExperience();

	//�ܵ���������ǰ����ֵ��ʧ
	virtual void LifeDissolveByAttack(const u32&attack){CurrentLife-=(attack - Defence);}
	
	//�ɴ��ƶ�
	virtual void Move(u32 time);

	//ˢ������
	virtual void RefreshAttrbutes( const u32& time);
	
	



};




#endif // IShip_h__