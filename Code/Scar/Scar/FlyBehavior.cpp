/********************************************************************
	创建时间: 2011:9:27   14:55
	文件名:   FlyBehavior.cpp
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     

*********************************************************************/

#include "FlyBehavior.h"

using namespace irr::scene;

void FlyStraightBehavior::Fly( IFly* pFlyObject )
{
	pFlyObject->SetPostion( pFlyObject->GetPosition() + pFlyObject->GetSpeed() );
}

