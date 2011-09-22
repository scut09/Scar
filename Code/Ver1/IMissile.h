/*
** 作者：华亮
** 说明：导弹和飞行
**
*/

#pragma once

#include <irrlicht.h>

using namespace irr;

/*
** 名字：IFly
** 说明：可飞行物体的接口
**
*/
class IFly
{
public:
	virtual void LoadSceneNode( scene::ISceneNode* pNode ) = 0;
	virtual void SetPostion( const core::vector3df& pos ) = 0;					// 设置位置
	virtual void SetRotation( const core::vector3df& rot ) = 0;					// 设置旋转角度，这个待商榷
	virtual core::vector3df GetPosition() = 0;		// 获取位置
	virtual scene::ISceneNode* TestCollision() = 0;	// 是否有碰撞
	virtual int Move() = 0;							// 移动
};

/*
** 名字：IFlyBehavior
** 说明：飞行的行为
**
*/
class IFlyBehavior
{
public:
	virtual void SetOwner( IFly* pFly ) = 0;	
	virtual core::vector3df Fly( const core::vector3df& pos ) = 0;
};

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
	Missile() {}

	void SetPostion( const core::vector3df& pos ) {}
	void SetRotation( const core::vector3df& rot ) {}
	core::vector3df GetPosition() { return m_vecPosition; }
	scene::ISceneNode* TestCollision()
	{
		return NULL;
	}

	void AddBehavior( IFlyBehavior* pBehavior )
	{
		m_flyBehavior = pBehavior;
	}

	void LoadSceneNode( scene::ISceneNode* pNode )
	{
		m_pNode = pNode;
	}

	int Move()
	{
		m_pNode->setPosition( m_flyBehavior->Fly( m_pNode->getPosition() ) );

		return 0;
	}

};