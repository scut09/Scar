/********************************************************************
	����ʱ��: 2011:9:27   14:54
	�ļ���:   FlyBehavior.h
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     

*********************************************************************/

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
	// ����
	virtual void Fly( IFly* pFlyObject );
};


#endif