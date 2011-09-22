/*
** ���ߣ�����
** ˵���������ͷ���
**
*/

#pragma once

#include <irrlicht.h>
#include <iostream>
#include <map>
#include <string>

using namespace irr;

/*
** ���֣�IFly
** ˵�����ɷ�������Ľӿ�
**
*/
class IFly
{
public:
	virtual void LoadSceneNode( scene::ISceneNode* pNode ) = 0;
	virtual void SetPostion( const core::vector3df& pos ) = 0;					// ����λ��
	virtual void SetRotation( const core::vector3df& rot ) = 0;					// ������ת�Ƕȣ��������ȶ
	virtual core::vector3df GetPosition() = 0;		// ��ȡλ��
	virtual scene::ISceneNode* TestCollision() = 0;	// �Ƿ�����ײ
	virtual int Move() = 0;							// �ƶ�
	virtual void Drop() = 0;
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
	virtual core::vector3df GetDirection() = 0;
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

	virtual core::vector3df GetDirection()
	{
		return m_vecDirection;
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
	core::vector3df		m_vecPosition;		// ������λ��
	core::vector3df		m_vecTarget;		// ������Ŀ��

	IFlyBehavior*		m_flyBehavior;

	scene::ISceneNode*	m_pNode;

public:
	static scene::ISceneCollisionManager*		m_pColMan;
	static std::map<scene::ISceneNode*, std::string>*	m_pModels;

public:
	Missile() {}

	void SetPostion( const core::vector3df& pos ) 
	{
		m_vecPosition = pos;
	}
	void SetRotation( const core::vector3df& rot ) {}
	core::vector3df GetPosition() { return m_vecPosition; }
	scene::ISceneNode* TestCollision();

	void AddBehavior( IFlyBehavior* pBehavior )
	{
		m_flyBehavior = pBehavior;
	}

	void LoadSceneNode( scene::ISceneNode* pNode )
	{
		if ( pNode )
		{
			m_pNode = pNode;
			m_pNode->setPosition( m_vecPosition );
		}
	}

	int Move()
	{
		m_pNode->setPosition( m_flyBehavior->Fly( m_pNode->getPosition() ) );

		return 0;
	}

	void Drop()
	{
		m_pNode->drop();
		m_pNode->remove();

	}
};