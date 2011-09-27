/********************************************************************
	创建时间: 2011:9:27   14:55
	文件名:   FlyBehavior.cpp
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     

*********************************************************************/

#include "FlyBehavior.h"


FlyStraightBehavior::FlyStraightBehavior( core::vector3df& direction, f32 speed ) : m_Owner( NULL ), m_vecDirection( direction.normalize() ), m_Speed( speed )
{

}

void FlyStraightBehavior::SetOwner( IFly* pFly )
{
	m_Owner = pFly;
}

core::vector3df FlyStraightBehavior::Fly( const core::vector3df& pos )
{
	core::vector3df newPosition = pos + m_Speed * m_vecDirection;
	return newPosition;
}

core::vector3df FlyStraightBehavior::GetDirection()
{
	return m_vecDirection;
}
