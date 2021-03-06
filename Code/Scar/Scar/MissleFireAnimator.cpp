#include "Boost_Client.h"
#include "Boost_Client.h"
#include "CSceneNodeAnimatorSelfDelFlyStraight.h"
#include "MissleFireAnimator.h"
#include "IShip.h"
#include "GeneralCallBack.h"
#include "SceneNodeShader.h"
#include "MissleFlame.h"
#include "MyIrrlichtEngine.h"
#include <iostream>
#include "CSceneNodeAutoTrackAnimator.h"
#include "MySceneNodeAnimatorCollisionResponse.h"
#include "MultiplayerScene.h"

MissleFireAnimator::MissleFireAnimator( boost::shared_ptr<Network::IClient> client ) 
	: IsFire( false ), Initialized( false ), Client( client )
{
}

void MissleFireAnimator::animateNode( ISceneNode* node, u32 timeMs )
{
	IShip* Ship = static_cast<IShip*>( node );
	//ICameraSceneNode* ship = static_cast<ICameraSceneNode*>( node );

	if ( !Initialized )
	{
		// 初始化每种武器的上次发射时间
		for( u32 i = 0; i < Ship->GetMissles().size(); i++ )
		{
			LastTimes.push_back( timeMs );
		}
		Initialized = true;
	}

	if ( IsFire )
	{
		for( u32 i = 0; i < Ship->GetMissles().size(); i++ )
		{
			if ( timeMs - LastTimes[i] > Ship->GetMissles()[i]->GetInterval() )
			{
				AddMissleToScene( static_cast< MissleNode* >( Ship->GetMissles()[ i ] ) );
				IsFire = false;
				LastTimes[i] = timeMs;
			}
		}
	}
}

ISceneNodeAnimator* MissleFireAnimator::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	throw std::exception("The method or operation is not implemented.");
}

bool MissleFireAnimator::OnEvent( const SEvent& event )
{
	switch(event.EventType)
	{

	case EET_MOUSE_INPUT_EVENT:
		if (event.MouseInput.Event == EMIE_RMOUSE_PRESSED_DOWN)
		{
			IsFire = true;
			return true;
		}
		break;

	default:
		break;

	}

	return false;
}



void MissleFireAnimator::AddMissleToScene( MissleNode* missle )
{

	boost::shared_ptr<IPlayer> player = MyIrrlichtEngine::GetEngine()->GetCurrentPlayer();
	
	if ( player->GetLockedShip() )
	{
		//目标船的ID存在startpoint的第一位中
		Client->SendBullet( Client->GetID(), 1, vector3df( (f32)player->GetLockedShip()->getID() , 0.0f, 0.0f), vector3df( 0.0f ), missle->GetLife() );

		// clone missle
		ISceneNode* newMissle = missle->Clone( 0, 0 );
		static_cast< MissleNode* >( newMissle )->setScale( vector3df( 8.f, 8.f, 8.f ) );

		// Flame
		MissleFlame mfe;
		mfe.AddFlameToScene( newMissle, MyIrrlichtEngine::GetEngine()->GetSceneManager() );

		// Lock
		static_cast< MissleNode* >( newMissle )->setTarget( player->GetLockedShip() );
		newMissle->setPosition( player->GetShip()->getPosition() );
		// Track
		auto missleAni = new CSceneNodeAnimatorAutoTrack( static_cast< MissleNode* >( newMissle )->getTarget() );
		newMissle->addAnimator( missleAni );
		missleAni->drop();

		ITriangleSelector* triSelector 
			= static_cast<MultiplayerScene*>(MyIrrlichtEngine::GetEngine()->GetGameSceneManager()->GetCurrentGameScene())->m_mapSelector;

		auto ColAni = new MySceneNodeAnimatorCollisionResponse( 
			MyIrrlichtEngine::GetEngine()->GetCollisionManager(), triSelector );

		//CSceneNodeAnimatorMyCollisionResponse* coll = 
		//	new CSceneNodeAnimatorMyCollisionResponse( MyIrrlichtEngine::GetEngine()->GetCollisionManager() );

		//// 添加碰撞响应函数
		//coll->SetCollisionCallback( [this, newMissle]( ISceneNode* node, ISceneNode* target_node )	
		//{
		//	//std::cout << "Ship hitted!\n";
		//	IWeapon* weapon = dynamic_cast<IWeapon*>( node );

		//	// 打中的是飞船
		//	IShip *ship = dynamic_cast<IShip *>( target_node );
		//	if (NULL != ship)
		//	{
		//		std::cout << "Missile Hit!\n";
		//		Client->SendBulletHit( Client->GetID(), ship->getID(), 1 );
		//		newMissle->setVisible( false );
		//	}
		//} );

		CSceneNodeAnimatorMyCollisionResponse* coll = 
			new CSceneNodeAnimatorMyCollisionResponse( MyIrrlichtEngine::GetEngine()->GetCollisionManager() );
		coll->SetCollisionCallback( [ this, newMissle ]( ISceneNode* node, ISceneNode* target_node ) 
		{
			IWeapon* weapon = dynamic_cast< IWeapon* >( node );
			IShip* ship = dynamic_cast< IShip* >( target_node );
			if ( NULL != ship )
			{
				int damage = 100;
				if ( ship->GetShield() > 0.0 )
					ship->SetShield( ship->GetShield() - damage );
				else if ( ship->GetArmor() > 0.0 )
					ship->SetArmor( ship->GetArmor() - damage );
				if ( ship->GetShield() < 0.0 )
					ship->SetShield( 0.0f );
				if ( ship->GetArmor() < 0.0 )
					ship->SetArmor( 0.0f );
				Client->SendBulletHit( Client->GetID(), ship->getID(), 1, ship );

				newMissle->setVisible( false );
			}
		});

		newMissle->addAnimator( coll );
		coll->drop();

	}
	/*CSceneNodeAnimatorMyCollisionResponse* coll = 
		new CSceneNodeAnimatorMyCollisionResponse( MyIrrlichtEngine::GetEngine()->GetCollisionManager() );

	// 测试发送炮弹数据
	Client->SendBullet( Client->GetID(), 0, startPoint, endPoint, bullet->GetLife() );

	// 添加碰撞响应函数
	coll->SetCollisionCallback( [this]( ISceneNode* node, ISceneNode* target_node )	
	{
		//std::cout << "Ship hitted!\n";
		IWeapon* weapon = dynamic_cast<IWeapon*>( node );

		// 打中的是飞船
		IShip *ship = dynamic_cast<IShip *>( target_node );
		if (NULL != ship)
		{
			std::cout << "fuck Ship hitted!\n";
			Client->SendBulletHit( Client->GetID(), ship->getID(), 0 );
		}
	} );

	newBullet->addAnimator( coll );
	coll->drop();*/
}
