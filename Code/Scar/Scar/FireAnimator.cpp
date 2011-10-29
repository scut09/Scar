#include "Boost_Client.h"
#include "FireAnimator.h"
#include "CSceneNodeAnimatorSelfDelFlyStraight.h"
#include "CSceneNodeAnimatorCollisionResponse.h"
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
				//CSceneNodeAnimatorSelfDelFlyStraight* ani;
				//ISceneNodeAnimator* del;
				//ISceneNode* newBullet;
				f32 distance = ship->GetGuns()[i]->GetVelocity() * ship->GetGuns()[i]->GetLife() / 1000.0f;  // 计算发射距离
				// 计算当前飞船姿态
				vector3df direction = ( Camera->getTarget() - Camera->getPosition() ).normalize(); // 计算发射方向
				vector3df upVector = Camera->getUpVector();
				upVector.normalize();
				vector3df horiVector = ( upVector.crossProduct( direction ) ).normalize();
				// 左炮管偏移
				vector3df leftOffset = direction * 10 + upVector * -5 + horiVector * -5;
				// 右炮管偏移
				vector3df rightOffset = direction * 10 + upVector * -5 + horiVector * 5;
				// (左)
				vector3df startPoint = ship->getPosition() + leftOffset; // 炮弹飞行起点
				vector3df endPoint = startPoint + direction * distance; // 飞行终止点		

				// 复制子弹(左)
				AddBulletToScene( ship->GetGuns()[i], startPoint, endPoint, timeMs );				

				//(右)
				startPoint = ship->getPosition() + rightOffset; // 炮弹飞行起点
				endPoint = startPoint + direction * distance; // 飞行终止点	

				// 复制子弹(右)
				AddBulletToScene( ship->GetGuns()[i], startPoint, endPoint, timeMs );				

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

FireAnimator::FireAnimator( ICameraSceneNode* camera ) : IsFire( false ), Initialized( false ), Camera( camera )
{

}

void FireAnimator::AddBulletToScene( IWeapon* bullet, const vector3df& startPoint, const vector3df& endPoint, u32 timeMs )
{
	// 复制子弹(左)
	ISceneNode* newBullet = bullet->Clone( 0, 0 );
	newBullet->setMaterialType( EMT_TRANSPARENT_ALPHA_CHANNEL );
	newBullet->setMaterialFlag( EMF_LIGHTING, false );
	// 直飞和自删除动画
	auto ani = new CSceneNodeAnimatorSelfDelFlyStraight( startPoint, endPoint, bullet->GetLife(), timeMs );
	auto del = MyIrrlichtEngine::GetEngine()->GetSceneManager()->createDeleteAnimator( bullet->GetLife() );

	// 测试发送炮弹数据
	client.SendBullet( 0, 0, startPoint, endPoint, bullet->GetLife() );

	// 帮子弹附上动画并发射出去
	newBullet->addAnimator( ani );
	newBullet->addAnimator( del );
	del->drop();
	ani->drop();

	CSceneNodeAnimatorMyCollisionResponse* coll = 
		new CSceneNodeAnimatorMyCollisionResponse( MyIrrlichtEngine::GetEngine()->GetCollisionManager() );

	
	// 添加碰撞响应函数
	coll->SetCollisionCallback( []( ISceneNode* node, ISceneNode* target_node )	
	{
		std::cout << "Ship hitted!\n";
		IWeapon* weapon = dynamic_cast<IWeapon*>( node );

		// 打中的是飞船
		IShip *ship = dynamic_cast<IShip *>( target_node );
		if (NULL != ship)
		{
			std::cout << "fuck Ship hitted!\n";
		}
	} );

	newBullet->addAnimator( coll );
	coll->drop();
}
