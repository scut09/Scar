/********************************************************************
	����ʱ��: 2011:9:27   14:55
	�ļ���:   FlyBehavior.cpp
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     

*********************************************************************/

#include "FlyBehavior.h"

using namespace irr::scene;

void FlyStraightBehavior::Fly( IFly* pFlyObject )
{
	pFlyObject->SetPostion( pFlyObject->GetPosition() + pFlyObject->GetSpeed() );
}

