#include "FireAnimator.h"
#include "CSceneNodeAnimatorSelfDelFlyStraight.h"
#include "IShip.h"
#include "MyIrrlichtEngine.h"

void FireAnimator::animateNode( ISceneNode* node, u32 timeMs )
{
	if ( IsFire )
	{
		IShip* ship = static_cast<IShip*>(node);
		for( auto iter = ship->GetGuns().begin(); iter != ship->GetGuns().end(); ++iter )
		{
			irr::u32 time = 5000;

			// 帮子弹附上动画并发射出去
			auto ani = new CSceneNodeAnimatorSelfDelFlyStraight( vector3df(0), vector3df(0,0,100), time, timeMs );
			auto newBullet = (*iter)->Clone(0,0);
			newBullet->addAnimator( ani );
			auto del = MyIrrlichtEngine::GetEngine()->GetSceneManager()->createDeleteAnimator( time );
			newBullet->addAnimator( del );
			del->drop();
			ani->drop();
			//newBullet->drop();
		}
	}
}

ISceneNodeAnimator* FireAnimator::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	throw std::exception("The method or operation is not implemented.");
}

bool FireAnimator::OnEvent( const SEvent& event )
{
	switch(event.EventType)
	{

	case EET_MOUSE_INPUT_EVENT:
		if (event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
		{
			IsFire = true;
			return true;
		}
		if (event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP)
		{
			IsFire = false;
			return true;
		}
		break;

	default:
		break;

	}

	return false;
}
