/*
** ���ߣ�����
** ˵����
**
*/

#include "IFly.h"

#ifndef _FLYBEHAVIOR_H_
#define _FLYBEHAVIOR_H_


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

	FlyStraightBehavior( core::vector3df& direction, f32 speed );

	void SetOwner( IFly* pFly );

	// ����
	virtual core::vector3df Fly( const core::vector3df& pos );

	virtual core::vector3df GetDirection();
};


#endif