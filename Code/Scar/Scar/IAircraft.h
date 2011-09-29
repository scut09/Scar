/********************************************************************
	����ʱ��: 2011-9-27   15:50
	�ļ���:   IAircraft.h
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     

*********************************************************************/


#ifndef IAircraft_h__
#define IAircraft_h__

#include "IFly.h"


/*
** ���֣�IAircraft
** ˵�����������ӿ�
**
*/
class IAircraft : public IFly
{
public:
	virtual void SetHP( u32 hp ) = 0;
	virtual u32 GetHP() = 0;

};


#endif // IAircraft_h__