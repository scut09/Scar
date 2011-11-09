/********************************************************************
    创建时间: 2011-11-9   1:02
    文件名:   HumanPlayer.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     人类玩家

*********************************************************************/

#ifndef HumanPlayer_h__
#define HumanPlayer_h__

#include "IPlayer.h"

class HumanPlayer : public IPlayer
{
public:
	HumanPlayer( IShip* ship ) : IPlayer( ship )
	{

	}

	virtual void Update()
	{
		// Do nothing, because human player will control the ship
	}


};

#endif // HumanPlayer_h__