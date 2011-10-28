#include "Boost_Client.h"
#include "FireAnimator.h"
#include "CSceneNodeAnimatorSelfDelFlyStraight.h"
#include "IShip.h"
#include "MyIrrlichtEngine.h"
#include <iostream>

extern Network::BoostClient client;	// 测试用

void FireAnimator::animateNode( ISceneNode* node, u32 timeMs )
{
	IShip* ship = dynamic_cast<IShip*>(node);

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
		for( u32 i = 0; i < ship->GetGuns().size(); i++ )
		{
			if ( timeMs - LastTimes[i] > ship->GetGuns()[i]->GetInterval() )
			{
				CSceneNodeAnimatorSelfDelFlyStraight* ani;
				ISceneNodeAnimator* del;
				ISceneNode* newBullet;
				f32 distance = ship->GetGuns()[i]->GetVelocity() * ship->GetGuns()[i]->GetLife() / 1000.0f;  // 计算发射距离
				// 计算当前飞船姿态
				vector3df direction = ship->getRotation().rotationToDirection().normalize(); // 计算发射方向
				vector3df upVector = ship->getRotation().rotationToDirection( vector3df(0,1,0) ).normalize();
				vector3df horiVector = ship->getRotation().rotationToDirection( vector3df(1,0,0) ).normalize();
				// 左炮管偏移
				vector3df leftOffset = direction * 10 + upVector * -5 + horiVector * -5;
				// 右炮管偏移
				vector3df rightOffset = direction * 10 + upVector * -5 + horiVector * 5;
				// (左)
				vector3df startPoint = ship->getPosition() + leftOffset; // 炮弹飞行起点
				vector3df endPoint = startPoint + direction * distance; // 飞行终止点				
				// 复制子弹(左)
				newBullet = ship->GetGuns()[i]->Clone( 0, 0 );
				newBullet->setMaterialType( EMT_TRANSPARENT_ALPHA_CHANNEL );
				newBullet->setMaterialFlag( EMF_LIGHTING, false );
				// 直飞和自删除动画
				ani = new CSceneNodeAnimatorSelfDelFlyStraight( startPoint, endPoint, ship->GetGuns()[i]->GetLife(), timeMs );
				del = MyIrrlichtEngine::GetEngine()->GetSceneManager()->createDeleteAnimator( ship->GetGuns()[i]->GetLife() );

				// 帮子弹附上动画并发射出去
				newBullet->addAnimator( ani );
				newBullet->addAnimator( del );
				del->drop();
				ani->drop();
				//(右)
				startPoint = ship->getPosition() + rightOffset; // 炮弹飞行起点
				endPoint = startPoint + direction * distance; // 飞行终止点	
				// 复制子弹(右)
				newBullet = ship->GetGuns()[i]->Clone( 0, 0 );
				newBullet->setMaterialType( EMT_TRANSPARENT_ALPHA_CHANNEL );
				newBullet->setMaterialFlag( EMF_LIGHTING, false );
				// 直飞和自删除动画
				ani = new CSceneNodeAnimatorSelfDelFlyStraight( startPoint, endPoint, ship->GetGuns()[i]->GetLife(), timeMs );
				del = MyIrrlichtEngine::GetEngine()->GetSceneManager()->createDeleteAnimator( ship->GetGuns()[i]->GetLife() );

				// 帮子弹附上动画并发射出去
				newBullet->addAnimator( ani );
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
