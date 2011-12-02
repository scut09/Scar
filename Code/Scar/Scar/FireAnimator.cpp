#include "Boost_Client.h"
#include "Boost_Client.h"
#include "CSceneNodeAnimatorSelfDelFlyStraight.h"
#include "FireAnimator.h"
#include "IShip.h"
#include "MyIrrlichtEngine.h"
#include "MultiplayerScene.h"
#include <iostream>

ShipFireAnimator::ShipFireAnimator( boost::shared_ptr<Network::IClient> client ) 
	: IsFire( false ), Initialized( false ), Client( client )
{
}

void ShipFireAnimator::animateNode( ISceneNode* node, u32 timeMs )
{
	IShip* Ship = static_cast<IShip*>( node );
	//ICameraSceneNode* ship = static_cast<ICameraSceneNode*>( node );

	if ( !Initialized )
	{
		// 初始化每种武器的上次发射时间
		for( u32 i = 0; i < Ship->GetGuns().size(); i++ )
		{
			LastTimes.push_back( timeMs );
		}
		Initialized = true;
	}

	if ( IsFire )
	{
		for( u32 i = 0; i < Ship->GetGuns().size(); i++ )
		{
			if ( timeMs - LastTimes[i] > Ship->GetGuns()[i]->GetInterval() )
			{
				//CSceneNodeAnimatorSelfDelFlyStraight* ani;
				//ISceneNodeAnimator* del;
				//ISceneNode* newBullet;
				f32 distance = Ship->GetGuns()[i]->GetVelocity() * Ship->GetGuns()[i]->GetLife() / 1000.0f;  // 计算发射距离
				// 计算当前飞船姿态
				vector3df direction = ( Ship->getTarget() - Ship->getPosition() ).normalize(); // 计算发射方向
				vector3df upVector = Ship->getUpVector();
				upVector.normalize();
				vector3df horiVector = ( upVector.crossProduct( direction ) ).normalize();
				// 左炮管偏移
				vector3df leftOffset = direction * 10 + upVector * -5 + horiVector * -5;
				// 右炮管偏移
				vector3df rightOffset = direction * 10 + upVector * -5 + horiVector * 5;
				// (左)
				vector3df startPoint = Ship->getPosition() + leftOffset; // 炮弹飞行起点
				vector3df endPoint = startPoint + direction * distance; // 飞行终止点		

				// 复制子弹(左)
				AddBulletToScene( Ship->GetGuns()[i], startPoint, endPoint, timeMs );				

				//(右)
				startPoint = Ship->getPosition() + rightOffset; // 炮弹飞行起点
				endPoint = startPoint + direction * distance; // 飞行终止点	

				// 复制子弹(右)
				AddBulletToScene( Ship->GetGuns()[i], startPoint, endPoint, timeMs );	

				// 开火音效
				/*MultiplayerScene* mulScene = static_cast<MultiplayerScene*>(MyIrrlichtEngine::GetEngine()->GetGameSceneManager()->GetCurrentGameScene());
				mulScene->m_pSoundEngine->play3D( "../sound/gunfire.wav", Ship->getPosition() );*/
				//mulScene->m_pSoundEngine->play2D( "../sound/gunfire.wav" );

				LastTimes[i] = timeMs;
			}
		}
	}
}

ISceneNodeAnimator* ShipFireAnimator::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	throw std::exception("The method or operation is not implemented.");
}

bool ShipFireAnimator::OnEvent( const SEvent& event )
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



void ShipFireAnimator::AddBulletToScene( IWeapon* bullet, const vector3df& startPoint, const vector3df& endPoint, u32 timeMs )
{
	// 复制子弹(左)
	ISceneNode* newBullet = bullet->Clone( 0, 0 );
	newBullet->setMaterialType( EMT_TRANSPARENT_ALPHA_CHANNEL );
	newBullet->setMaterialFlag( EMF_LIGHTING, false );
	// 直飞和自删除动画
	auto ani = new CSceneNodeAnimatorSelfDelFlyStraight( startPoint, endPoint, bullet->GetLife(), timeMs );
	auto del = MyIrrlichtEngine::GetEngine()->GetSceneManager()->createDeleteAnimator( bullet->GetLife() );

	// 帮子弹附上动画并发射出去
	newBullet->addAnimator( ani );
	newBullet->addAnimator( del );
	del->drop();
	ani->drop();

	CSceneNodeAnimatorMyCollisionResponse* coll = 
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
	coll->drop();
}
