/*
** ���ߣ�����
** ˵���������ͷ���
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
