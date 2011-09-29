/********************************************************************
	����ʱ��: 2011:9:27   14:55
	�ļ���:   FlyBehavior.cpp
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     

*********************************************************************/

#include "FlyBehavior.h"

using namespace irr::scene;

FlyStraightBehavior::FlyStraightBehavior( core::vector3df& direction, f32 speed ) 
	: m_Owner( NULL ), 
	m_vecDirection( direction.normalize() ),
	m_Speed( speed )
{

}

void FlyStraightBehavior::SetOwner( IFly* pFly )
{
	m_Owner = pFly;
}

core::vector3df FlyStraightBehavior::Fly()
{
	ISceneNode* node = m_Owner->GetSceneNode();

	core::vector3df newPosition = pos + m_Speed * m_vecDirection;
	return newPosition;
}

core::vector3df FlyStraightBehavior::GetDirection()
{
	return m_vecDirection;
}
