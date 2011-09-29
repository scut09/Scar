/********************************************************************
	创建时间: 2011:9:27   14:54
	文件名:   FlyBehavior.h
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     

*********************************************************************/

#include "IFly.h"

#ifndef _FLYBEHAVIOR_H_
#define _FLYBEHAVIOR_H_


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

	FlyStraightBehavior( core::vector3df& direction, f32 speed );

	void SetOwner( IFly* pFly );

	// 飞行
	virtual core::vector3df Fly();

	virtual core::vector3df GetDirection();
};


#endif