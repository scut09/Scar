/********************************************************************
    ����ʱ��: 2011-11-9   1:02
    �ļ���:   HumanPlayer.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     �������

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