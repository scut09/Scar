/*
** ���ߣ�����
** ˵���������ͷ���
**
*/

#pragma once

#include <irrlicht.h>

using namespace irr;

/*
** ���֣�IFly
** ˵�����ɷ�������Ľӿ�
**
*/
class IFly
{
	virtual void SetPostion( const core::vector3df& pos ) = 0;					// ����λ��
	virtual void SetRotation( const core::vector3df& rot ) = 0;					// ������ת�Ƕȣ��������ȶ
	virtual core::vector3df GetPosition() = 0;		// ��ȡλ��
	virtual scene::ISceneNode* HitCollision() = 0;	// �Ƿ�����ײ
	virtual int Move() = 0;							// �ƶ�
};

/*
** ���֣�IFlyBehavior
** ˵�������е���Ϊ
**
*/
class IFlyBehavior
{
public:
	virtual void SetOwner( IFly* pFly ) = 0;	
	virtual core::vector3df Fly( const core::vector3df& pos ) = 0;
};

/*
** ���֣�IMissile
** ˵���������ӿ�
**
*/
class IMissile : public IFly
{
public:
	virtual void AddBehavior( IFlyBehavior* pBehavior ) = 0;
};





/*
** ���֣�FlyStraightBehavior
** ˵����ֱ�߷��е���Ϊ
**
*/
class FlyStraightBehavior : public IFlyBehavior
{
public:
	IFly*	m_Owner;		// ��Ϊ�����ߵ�ָ��
	f32		m_Speed;
	core::vector3df m_vecDirection;

	FlyStraightBehavior( core::vector3df& direction, f32 speed ) 
		: m_Owner( NULL ), m_vecDirection( direction.normalize() ), m_Speed( speed )
	{
	}

	void SetOwner( IFly* pFly )
	{
		m_Owner = pFly;
	}

	// ����
	virtual core::vector3df Fly( const core::vector3df& pos )
	{
		core::vector3df newPosition = pos + m_Speed * m_vecDirection;
		return newPosition;
	}
};


/*
** ���֣�Missile
** ˵��������
**
*/
class Missile : public IMissile
{
private:
	core::vector3df m_vecPosition;		// ������λ��
	core::vector3df m_vecTarget;		// ������Ŀ��

	IFlyBehavior*	m_flyBehavior;

public:
	Missile() {}

	void AddBehavior( IFlyBehavior* pBehavior )
	{
		m_flyBehavior = pBehavior;
	}





};