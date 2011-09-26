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
#include "FlyBehavior.h"


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

	void SetPostion( const core::vector3df& pos );
	void SetRotation( const core::vector3df& rot ) {}
	core::vector3df GetPosition() { return m_vecPosition; }
	scene::ISceneNode* TestCollision();

	void AddBehavior( IFlyBehavior* pBehavior );

	void LoadSceneNode( scene::ISceneNode* pNode );

	int Move();

	void Drop();

	scene::ISceneNode* GetSceneNode();
};



#endif
