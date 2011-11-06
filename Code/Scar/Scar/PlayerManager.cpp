#include "PlayerManager.h"


PlayerHelper::PlayerHelper( UIManager* uiManager, IShip* player_ship )
	: m_uiManager( uiManager ), PlayerShip( player_ship ), LockedShip( NULL )
{
	Camera = MyIrrlichtEngine::GetEngine()->GetSceneManager()->getActiveCamera();
	Driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
	CursorControl = MyIrrlichtEngine::GetEngine()->GetDevice()->getCursorControl();

	toolkit = new Toolkit( Camera, Driver );



	// 获取鼠标准心
	Cursor = m_uiManager->GetObjectByName("cursor");
	// 获取速度槽
	Speed1 = m_uiManager->GetObjectByName( "speed1" );
	Speed2 = m_uiManager->GetObjectByName( "speed2" );
	// 获取护盾槽
	Shield1 = m_uiManager->GetObjectByName( "shield1");
	Shield2 = m_uiManager->GetObjectByName( "shield2");
	// 获取护甲槽
	Armor1 = m_uiManager->GetObjectByName( "armor1");
	Armor2 = m_uiManager->GetObjectByName( "armor2");
	// 获取水平仪
	Gradienter = m_uiManager->GetObjectByName( "gradienter" );
	// 获取目标圈
	ShipTip = m_uiManager->GetObjectByName( "target1" );
	ShipTip->SetVisible( false );
	// 获取锁定圈——已锁定
	lock1 = m_uiManager->GetObjectByName( "lock1" );
	// 获取敌军指示
	indicator1 = m_uiManager->GetObjectByName( "indicator1" );
}

void PlayerHelper::UpdateShipTip( IShip* ship )
{
	if ( ship == PlayerShip )	return;

	IUIObject* shipTip;
	auto iter = m_ship_targetMap.find( ship );
	if ( iter == m_ship_targetMap.end() )
	{
		// 还未创建提示框，那么就创建一个新的
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

	// 测试用圈圈圈住目标
	if ( toolkit->GetNode2DInfo( ship, &info2D ) )
	{
		f32 sca = info2D.height / 60.0f;
		if ( sca > 1.2f )
			sca = 1.2f;
		else if ( sca < 0.5f )
			sca = 0.5f;

		shipTip->SetVisible( true );				// 显示飞船提示
		shipTip->SetPosition( info2D.pos );
		shipTip->SetScale( vector2df(sca) );
	}
	else
	{
		shipTip->SetVisible( false );				// 显示飞船提示
	}
}

void PlayerHelper::Update()
{
	// 准心追随鼠标
	auto CursorPos = CursorControl->getPosition();
	Cursor->SetPosition( vector2df( (f32)CursorPos.X, (f32)CursorPos.Y ) );

	f32 ratio;
	f32 border;
	// 绘制速度槽
	ratio = PlayerShip->GetVelocity() / PlayerShip->GetMaxSpeed();
	border = 389 * ( 1 - ratio );
	Speed1->SetSourceRect( vector2df( 0, border ), vector2df( 98, 389 ) );
	Speed2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 98, border ) );	
	// 绘制护盾槽
	ratio = PlayerShip->GetShield() / PlayerShip->GetMaxShield();
	border = 389 * ( 1 - ratio );
	Shield1->SetSourceRect( vector2df( 0, border ), vector2df( 100, 389 ) );
	Shield2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 100, border ) );
	// 绘制护甲槽
	ratio = PlayerShip->GetArmor() / PlayerShip->GetMaxArmor();
	border = 360 * ( 1 - ratio );
	Armor1->SetSourceRect( vector2df( 0, border ), vector2df( 93, 360 ) );
	Armor2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 93, border ) );

	// 水平仪转动
	core::vector3df vec( 0, 1, 0 );
	f32 rott = (f32)acos( ( Camera->getUpVector().dotProduct( vector3df( 0, 1, 0 ) ) ) / Camera->getUpVector().getLength() ) * RADTODEG;
	Gradienter->SetRotation( rott );

	// 更新飞船提示框
	for ( auto iter = m_ship_targetMap.begin(); iter != m_ship_targetMap.end(); ++iter )
	{
		UpdateShipTip( iter->first );
	}

	// 更新锁定框
	UpdateLock();
}

void PlayerHelper::UpdateLock()
{
	if ( ! LockedShip )		return;

	// 测试用圈圈圈住目标
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
		  // 测试用箭头标记地方位置
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
		// 从vector移除	
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
