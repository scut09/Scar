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
	// 飞行
	virtual void Fly( IFly* pFlyObject );
};


#endif