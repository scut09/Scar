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
		ISceneNode* newMissle = missle->Clone( 0, 0 );
		static_cast< MissleNode* >( newMissle )->setScale( vector3df( 8.f, 8.f, 8.f ) );
		MissleFlame mfe;
		mfe.AddFlameToScene( newMissle, MyIrrlichtEngine::GetEngine()->GetSceneManager() );
		static_cast< MissleNode* >( newMissle )->setTarget( player->GetLockedShip() );
		newMissle->setPosition( player->GetShip()->getPosition() );
		auto missleAni = new CSceneNodeAnimatorAutoTrack( static_cast< MissleNode* >( newMissle )->getTarget() );
		newMissle->addAnimator( missleAni );
		missleAni->drop();
		auto autodelete = MyIrrlichtEngine::GetEngine()->GetMySceneManager()->createDeleteAnimator( 5000 );
		newMissle->addAnimator( autodelete );
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
