#include "Boost_Client.h"
#include "Boost_Client.h"
#include "CSceneNodeAnimatorSelfDelFlyStraight.h"
#include "FireAnimator.h"
#include "IShip.h"
#include "MyIrrlichtEngine.h"
#include "MultiplayerScene.h"
#include <iostream>
#include "MySceneNodeAnimatorCollisionResponse.h"
#include "SpriteControlAnimatorl.h"

ShipFireAnimator::ShipFireAnimator( boost::shared_ptr<Network::IClient> client, int type ) 
	: IsFire( false ), Initialized( false ), Client( client ), m_type( type )
{
	BulletHit = MyIrrlichtEngine::GetEngine()->GetMySceneManager()->addBillboardSceneNode();
	BulletHit->setMaterialTexture( 0, MyIrrlichtEngine::GetEngine()->GetVideoDriver()->getTexture("../media/Weapon/bullethit2.png") );
	BulletHit->setVisible( false );
}

void ShipFireAnimator::animateNode( ISceneNode* node, u32 timeMs )
{
	IShip* Ship = static_cast<IShip*>( node );
	//ICameraSceneNode* ship = static_cast<ICameraSceneNode*>( node );

	if ( !Initialized )
	{
		// ��ʼ��ÿ���������ϴη���ʱ��
		for( u32 i = 0; i < Ship->GetGuns().size(); i++ )
		{
			LastTimes.push_back( timeMs );
		}
		Initialized = true;
	}

	if ( Ship->GetEnergy() < Ship->GetMaxEnergy() )
		Ship->SetEnergy( Ship->GetEnergy() + 2 );

	if ( IsFire )
	{
		for( u32 i = 0; i < Ship->GetGuns().size(); i++ )
		{
			if ( timeMs - LastTimes[i] > Ship->GetGuns()[i]->GetInterval() && Ship->GetEnergy() > 20)
			{
				Ship->SetEnergy( Ship->GetEnergy() - 20 );
				if( Ship->GetEnergy() < 0 )
					Ship->SetEnergy( 0 );
				//CSceneNodeAnimatorSelfDelFlyStraight* ani;
				//ISceneNodeAnimator* del;
				//ISceneNode* newBullet;
				f32 distance = Ship->GetGuns()[i]->GetVelocity() * Ship->GetGuns()[i]->GetLife() / 1000.0f;  // ���㷢�����
				// ���㵱ǰ�ɴ���̬
				vector3df direction = ( Ship->getTarget() - Ship->getPosition() ).normalize(); // ���㷢�䷽��
				vector3df upVector = Ship->getUpVector();
				upVector.normalize();
				vector3df horiVector = ( upVector.crossProduct( direction ) ).normalize();
				// ���ڹ�ƫ��
				vector3df leftOffset = direction * 10 + upVector * -5 + horiVector * -5;
				// ���ڹ�ƫ��
				vector3df rightOffset = direction * 10 + upVector * -5 + horiVector * 5;
				// (��)
				vector3df startPoint = Ship->getPosition() + leftOffset; // �ڵ��������
				vector3df endPoint = startPoint + direction * distance; // ������ֹ��		

				// �����ӵ�(��)
				AddBulletToScene( Ship->GetGuns()[i], startPoint, endPoint, timeMs );				

				//(��)
				startPoint = Ship->getPosition() + rightOffset; // �ڵ��������
				endPoint = startPoint + direction * distance; // ������ֹ��	

				// �����ӵ�(��)
				AddBulletToScene( Ship->GetGuns()[i], startPoint, endPoint, timeMs );	

				// ������Ч
				if ( Ship == MyIrrlichtEngine::GetEngine()->GetCurrentPlayer()->GetShip() )
				{
					MultiplayerScene* mulScene = static_cast<MultiplayerScene*>(MyIrrlichtEngine::GetEngine()->GetGameSceneManager()->GetCurrentGameScene());
					mulScene->m_pSoundEngine->play2D( "../sound/gunfire.wav" );
				}

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
	if ( m_type == 2 || m_type == 4 )
	{
		// ���Է����ڵ�����
		Client->SendBullet( Client->GetID(), 0, startPoint, endPoint, bullet->GetLife() );
	}

	if ( m_type == 2 )
	{
		return;
	}

	// �����ӵ�
	ISceneNode* newBullet = bullet->Clone( 0, 0 );
	newBullet->setMaterialType( EMT_TRANSPARENT_ALPHA_CHANNEL );
	newBullet->setMaterialFlag( EMF_LIGHTING, false );
	// ֱ�ɺ���ɾ������
	auto ani = new CSceneNodeAnimatorSelfDelFlyStraight( startPoint, endPoint, bullet->GetLife(), timeMs );
	auto del = MyIrrlichtEngine::GetEngine()->GetSceneManager()->createDeleteAnimator( bullet->GetLife() );

	// ���ӵ����϶����������ȥ
	newBullet->addAnimator( ani );
	newBullet->addAnimator( del );
	del->drop();
	ani->drop();
	
	ITriangleSelector* triSelector = static_cast<MultiplayerScene*>(MyIrrlichtEngine::GetEngine()->GetGameSceneManager()->GetCurrentGameScene())->m_mapSelector;
	auto ColAni = new MySceneNodeAnimatorCollisionResponse( 
		MyIrrlichtEngine::GetEngine()->GetCollisionManager(), triSelector );

	ColAni->SetCollisionCallback( [this, newBullet](ISceneNode* node, const ISceneNode* ColNode, vector3df ColPos)
	{
		IWeapon* weapon = dynamic_cast<IWeapon*>( node );

		//// ���е��Ƿɴ�
		//IShip *ship = dynamic_cast<IShip*>(const_cast<ISceneNode*>( ColNode ));
		//if (NULL != ship)
		//{
		//	std::cout << "fuck Ship hitted!\n";
		//	Client->SendBulletHit( Client->GetID(), ship->getID(), 0 );
		//}
		newBullet->setVisible( false );
		// �ӵ����л�⶯��
		ISceneNode* HitSprite = BulletHit->clone();
		HitSprite->setVisible( true );
		HitSprite->setMaterialFlag( EMF_ZBUFFER, false );
		HitSprite->setPosition( ColPos );
		auto ani = new SpriteControlAnimatorl( 8, 2, 0, "Shader/BulletHit.frag" );
		HitSprite->addAnimator( ani );
		ani->drop();
	} );

	newBullet->addAnimator( ColAni );
	ColAni->drop();

	CSceneNodeAnimatorMyCollisionResponse* coll = 
		new CSceneNodeAnimatorMyCollisionResponse( MyIrrlichtEngine::GetEngine()->GetCollisionManager() );

	// �����ײ��Ӧ����
	coll->SetCollisionCallback( [this, newBullet]( ISceneNode* node, ISceneNode* target_node )	
	{
		//std::cout << "Ship hitted!\n";
		IWeapon* weapon = dynamic_cast<IWeapon*>( node );

		// ���е��Ƿɴ�
		IShip *ship = dynamic_cast<IShip *>( target_node );
		if (NULL != ship)
		{
			//std::cout << "fuck Ship hitted!\n";
			int damage = 10;
			IShip *ship = dynamic_cast<IShip *>( target_node );
			if (NULL != ship)
			{
				if (ship->GetShield() > 0.0 )
				{
					// ���㻤��
					ship->SetShield( ship->GetShield() - damage );
					std::cout << "ship SetShield\n";
				}
				else if(ship->GetArmor() > 0.0 )
				{
					// ���㻤��
					ship->SetArmor( ship->GetArmor() - damage );
					std::cout << "ship SetArmor\n";
				}

				if ( ship->GetShield() < 0.0 )
				{
					ship->SetShield(0.0f);
				}

				if ( ship->GetArmor() < 0.0 )
				{
					ship->SetArmor(0.0f);
				}
			}

			Client->SendBulletHit( Client->GetID(), ship->getID(), 0, ship );

			newBullet->setVisible( false );
		}
	} );

	newBullet->addAnimator( coll );
	coll->drop();
}
