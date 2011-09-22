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
	virtual void SetPostion() = 0;
	virtual void SetRotation() = 0;
	virtual core::vector3df GetPosition() = 0;
	virtual scene::ISceneNode* HitTest() = 0;
	virtual int Move() = 0;
};



/*
** ���֣�IMissile
** ˵���������ӿ�
**
*/
class IMissile : public IFly
{
public:
	virtual void AddBehavior() = 0;


};


/*
** ���֣�IFlyBehavior
** ˵�������е���Ϊ
**
*/
class IFlyBehavior
{
public:
	virtual void SetParent() = 0;
	virtual core::vector3df Fly( const core::vector3df& pos ) = 0;
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

	FlyStraightBehavior( const core::vector3df& direction, f32 speed ) 
		: m_Owner( NULL ), m_vecDirection( direction.normalize() ), m_Speed( speed )
	{}

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






public:



};