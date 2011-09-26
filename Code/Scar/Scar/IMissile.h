/*
** 作者：华亮
** 说明：导弹和飞行
**
*/

#ifndef _IMISSILE_H_
#define _IMISSILE_H_

#include "IFly.h"
#include <iostream>
#include <map>
#include <string>

#define PRINT_POSITION(pos) std::cout << #pos << ": " << (pos).X << ' ' << (pos).Y << ' ' << (pos).Z << std::endl;

using namespace irr;


/*
** 名字：IMissile
** 说明：导弹接口
**
*/
class IMissile : public IFly
{
public:
	virtual void AddBehavior( IFlyBehavior* pBehavior ) = 0;
};


/*
** 名字：FlyStraightBehavior
** 说明：直线飞行的行为
**
*/
class FlyStraightBehavior : public IFlyBehavior
{
public:
	IFly*	m_Owner;		// 行为所有者的指针
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

	// 飞行
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
** 名字：Missile
** 说明：导弹
**
*/
class Missile : public IMissile
{
private:
	core::vector3df		m_vecPosition;		// 导弹的位置
	core::vector3df		m_vecTarget;		// 导弹的目标

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
		//m_pNode->drop();
		m_pNode->remove();
	}

	scene::ISceneNode* GetSceneNode() 
	{
		return m_pNode;
	}
};



#endif
