#include "FireAnimator.h"
#include "CSceneNodeAnimatorSelfDelFlyStraight.h"
#include "IShip.h"
#include "MyIrrlichtEngine.h"

void FireAnimator::animateNode( ISceneNode* node, u32 timeMs )
{
	IShip* ship = static_cast<IShip*>(node);

	if ( !Initialized )
	{
		// 初始化每种武器的上次发射时间
		for( u32 i = 0; i < ship->GetGuns().size(); i++ )
		{
			LastTimes.push_back( timeMs );
		}
		Initialized = true;
	}

	if ( IsFire )
	{
		//for( auto iter = ship->GetGuns().begin(); iter != ship->GetGuns().end(); ++iter )
		//{
		//	// 帮子弹附上动画并发射出去
		//	auto newBullet = (*iter)->Clone(0,0);
		//	newBullet->setMaterialType( EMT_TRANSPARENT_ALPHA_CHANNEL );
		//	newBullet->setMaterialFlag( EMF_LIGHTING, false );
		//	auto ani = new CSceneNodeAnimatorSelfDelFlyStraight( vector3df(0), vector3df(0,0,100), (*iter)->GetLife(), timeMs );
		//	newBullet->addAnimator( ani );
		//	auto del = MyIrrlichtEngine::GetEngine()->GetSceneManager()->createDeleteAnimator( (*iter)->GetLife() );
		//	newBullet->addAnimator( del );
		//	del->drop();
		//	ani->drop();
		//	//newBullet->drop();
		//}
		for( u32 i = 0; i < ship->GetGuns().size(); i++ )
		{
			if ( timeMs - LastTimes[i] > ship->GetGuns()[i]->GetInterval() )
			{
				// 复制子弹
				auto newBullet = ship->GetGuns()[i]->Clone( 0, 0 );
				newBullet->setMaterialType( EMT_TRANSPARENT_ALPHA_CHANNEL );
				newBullet->setMaterialFlag( EMF_LIGHTING, false );
				// 帮子弹附上动画并发射出去
				auto ani = new CSceneNodeAnimatorSelfDelFlyStraight( vector3df(0), vector3df(0,0,100), ship->GetGuns()[i]->GetLife(), timeMs );
				newBullet->addAnimator( ani );
				auto del = MyIrrlichtEngine::GetEngine()->GetSceneManager()->createDeleteAnimator( ship->GetGuns()[i]->GetLife() );
				newBullet->addAnimator( del );
				del->drop();
				ani->drop();
				LastTimes[i] = timeMs;
			}
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

FireAnimator::FireAnimator() : IsFire( false ), Initialized( false )
{

}
