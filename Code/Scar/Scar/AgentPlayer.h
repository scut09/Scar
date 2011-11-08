/********************************************************************
    ����ʱ��: 2011-11-9   1:05
    �ļ���:   AgentPlayer.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     ������ң�Ҳ���ǵ�����

*********************************************************************/

#ifndef AgentPlayer_h__
#define AgentPlayer_h__

#include "IPlayer.h"

/*
** ���֣�AgentPlayer
** ˵����Computer controls this player, just like agent in a film
**
*/
class AgentPlayer : public IPlayer
{
public:
	virtual bool IsRobot()
	{
		return true;
	}

	virtual void Update()
	{
		// Do some control here
	}
};


#endif // AgentPlayer_h__