/********************************************************************
    创建时间: 2011-11-9   1:05
    文件名:   AgentPlayer.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     代理玩家，也就是电脑人

*********************************************************************/

#ifndef AgentPlayer_h__
#define AgentPlayer_h__

#include "IPlayer.h"

/*
** 名字：AgentPlayer
** 说明：Computer controls this player, just like agent in a film
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