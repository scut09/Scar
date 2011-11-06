#include "PlayerManager.h"


PlayerHelper::PlayerHelper( UIManager* uiManager, IShip* player_ship )
	: m_uiManager( uiManager ), PlayerShip( player_ship ), LockedShip( NULL )
{
	Camera = MyIrrlichtEngine::GetEngine()->GetSceneManager()->getActiveCamera();
	Driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
	CursorControl = MyIrrlichtEngine::GetEngine()->GetDevice()->getCursorControl();

	toolkit = new Toolkit( Camera, Driver );



	// ��ȡ���׼��
	Cursor = m_uiManager->GetObjectByName("cursor");
	// ��ȡ�ٶȲ�
	Speed1 = m_uiManager->GetObjectByName( "speed1" );
	Speed2 = m_uiManager->GetObjectByName( "speed2" );
	// ��ȡ���ܲ�
	Shield1 = m_uiManager->GetObjectByName( "shield1");
	Shield2 = m_uiManager->GetObjectByName( "shield2");
	// ��ȡ���ײ�
	Armor1 = m_uiManager->GetObjectByName( "armor1");
	Armor2 = m_uiManager->GetObjectByName( "armor2");
	// ��ȡˮƽ��
	Gradienter = m_uiManager->GetObjectByName( "gradienter" );
	// ��ȡĿ��Ȧ
	ShipTip = m_uiManager->GetObjectByName( "target1" );
	ShipTip->SetVisible( false );
	// ��ȡ����Ȧ����������
	lock1 = m_uiManager->GetObjectByName( "lock1" );
	// ��ȡ�о�ָʾ
	indicator1 = m_uiManager->GetObjectByName( "indicator1" );
}

void PlayerHelper::UpdateShipTip( IShip* ship )
{
	if ( ship == PlayerShip )	return;

	IUIObject* shipTip;
	auto iter = m_ship_targetMap.find( ship );
	if ( iter == m_ship_targetMap.end() )
	{
		// ��δ������ʾ����ô�ʹ���һ���µ�
		shipTip = ShipTip->Clone();

		m_ship_targetMap[ ship ] = shipTip;

		//  Test
		LockedShip = ship;
		// End Test
	}
	else	
	{
		shipTip = iter->second;
	}

	// ������ȦȦȦסĿ��
	if ( toolkit->GetNode2DInfo( ship, &info2D ) )
	{
		f32 sca = info2D.height / 60.0f;
		if ( sca > 1.2f )
			sca = 1.2f;
		else if ( sca < 0.5f )
			sca = 0.5f;

		shipTip->SetVisible( true );				// ��ʾ�ɴ���ʾ
		shipTip->SetPosition( info2D.pos );
		shipTip->SetScale( vector2df(sca) );
	}
	else
	{
		shipTip->SetVisible( false );				// ��ʾ�ɴ���ʾ
	}
}

void PlayerHelper::Update()
{
	// ׼��׷�����
	auto CursorPos = CursorControl->getPosition();
	Cursor->SetPosition( vector2df( (f32)CursorPos.X, (f32)CursorPos.Y ) );

	f32 ratio;
	f32 border;
	// �����ٶȲ�
	ratio = PlayerShip->GetVelocity() / PlayerShip->GetMaxSpeed();
	border = 389 * ( 1 - ratio );
	Speed1->SetSourceRect( vector2df( 0, border ), vector2df( 98, 389 ) );
	Speed2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 98, border ) );	
	// ���ƻ��ܲ�
	ratio = PlayerShip->GetShield() / PlayerShip->GetMaxShield();
	border = 389 * ( 1 - ratio );
	Shield1->SetSourceRect( vector2df( 0, border ), vector2df( 100, 389 ) );
	Shield2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 100, border ) );
	// ���ƻ��ײ�
	ratio = PlayerShip->GetArmor() / PlayerShip->GetMaxArmor();
	border = 360 * ( 1 - ratio );
	Armor1->SetSourceRect( vector2df( 0, border ), vector2df( 93, 360 ) );
	Armor2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 93, border ) );

	// ˮƽ��ת��
	core::vector3df vec( 0, 1, 0 );
	f32 rott = (f32)acos( ( Camera->getUpVector().dotProduct( vector3df( 0, 1, 0 ) ) ) / Camera->getUpVector().getLength() ) * RADTODEG;
	Gradienter->SetRotation( rott );

	// ���·ɴ���ʾ��
	for ( auto iter = m_ship_targetMap.begin(); iter != m_ship_targetMap.end(); ++iter )
	{
		UpdateShipTip( iter->first );
	}

	// ����������
	UpdateLock();
}

void PlayerHelper::UpdateLock()
{
	if ( ! LockedShip )		return;

	// ������ȦȦȦסĿ��
	 if ( toolkit->GetNode2DInfo( LockedShip, &info2D ) )
	 {
		 indicator1->SetVisible( false );
		 f32 sca = info2D.height / 60.0f;
		 if ( sca > 1.2f )
			 sca = 1.2f;
		 else if ( sca < 0.5f )
			 sca = 0.5f;

		 lock1->SetPosition( info2D.pos );
		 lock1->SetScale( vector2df(sca) );
		 lock1->SetVisible( true );
	 }
	 else
	 {
		  lock1->SetVisible( false );
		  indicator1->SetVisible( true );
		  // �����ü�ͷ��ǵط�λ��
		  vector2df screenPos;
		  toolkit->To2DScreamPos( (LockedShip->getPosition() - Camera->getPosition()), &screenPos );
		  vector2df screenVec = screenPos - vector2df( Driver->getScreenSize().Width / 2.f, Driver->getScreenSize().Height / 2.f );
		  f32 ang = (f32)screenVec.getAngle();
		  ang = -(ang-90);

		  indicator1->SetRotation( ang );
	 } 
}


//////////////////////////////////////////////////////////////////////////
//
// Class PlayerManager
// 
PlayerManager::PlayerManager( UIManager* uiManager, IShip* player_ship ) : m_uiManager( uiManager ), m_playerHelper( uiManager, player_ship )
{

}

void PlayerManager::Update()
{
	m_playerHelper.Update();

	for ( PlayerMapType::iterator iter = m_playerList.begin(); iter != m_playerList.end(); ++iter )
	{
		m_playerHelper.UpdateShipTip( iter->second );
	}
}

void PlayerManager::AddPlayer( int id, IShip* player_node )
{
	m_playerList[ id ] = player_node;
	m_players.push_back( player_node );
	player_node->grab();
}

void PlayerManager::RemovePlayer( int id )
{
	auto iter = m_playerList.find( id );
	if ( iter != m_playerList.end() )
	{
		iter->second->drop();
		// ��vector�Ƴ�	
		 auto i = m_players.begin();
		for ( ; i != m_players.end(); ++i )
		{
			if ( *i == iter->second )
				break;
		}
		m_players.erase( i );
		
		m_playerList.erase( iter );
	}
}

const std::vector<IShip*>& PlayerManager::GetPlayers() const
{
	return m_players;
}

PlayerManager::~PlayerManager()
{
	for ( auto iter = m_playerList.begin(); iter != m_playerList.end(); ++iter )
	{
		iter->second->drop();
	}
}
