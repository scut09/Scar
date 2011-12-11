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
		TimePoint = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
	}

	virtual void Update()
	{
		f32 PassedTime = (f32)(MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime() - TimePoint);

		if (PassedTime >= 2000)
		{
			TimePoint =  MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
			if (PlayerShip->GetShield() < 1000.f)
			{
				PlayerShip->SetShield( PlayerShip->GetShield() + 10 );
			}

			if (PlayerShip->GetShield() > 1000.f)
			{
				PlayerShip->SetShield( 1000.f );
			}

		}
	}
private:
	u32 TimePoint;

};

#endif // HumanPlayer_h__