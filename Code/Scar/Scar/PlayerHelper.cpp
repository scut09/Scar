#include "PlayerHelper.h"
#include "MyIrrlichtEngine.h"
#include <iostream>
#include <string>

PlayerHelper::PlayerHelper()
	: LockedShip( NULL )
{
	Camera = MyIrrlichtEngine::GetEngine()->GetSceneManager()->getActiveCamera();
	Driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
	CursorControl = MyIrrlichtEngine::GetEngine()->GetDevice()->getCursorControl();

	toolkit = boost::shared_ptr<Toolkit>( new Toolkit( Camera, Driver ) );

//	LoadHelperUI();
}

void PlayerHelper::UpdateShipTip( IShip* ship )
{
	if ( ship == Player->GetShip() )	return;	// 如果是自己的船，不需要被框住

	IUIObject* shipTip;
	auto iter = m_ship_targetMap.find( ship );
	if ( iter == m_ship_targetMap.end() )
	{
		// 还未创建提示框，那么就创建一个新的
		shipTip = ShipTipE->Clone();

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
	using namespace irr::core;
	// 准心追随鼠标
	auto CursorPos = CursorControl->getPosition();
	Cursor->SetPosition( vector2df( (f32)CursorPos.X, (f32)CursorPos.Y ) );

	IShip* playerShip = Player->GetShip();

	f32 ratio;
	f32 border;
	char buffer[20];	// 数字转字符串缓冲
	f32 val;			// 数字
	stringw str;		// 字符串
	f32 h, w;			// 元件高和宽
	// 绘制速度槽
	w = Speed1->GetOriginSize().Width;
	h = Speed1->GetOriginSize().Height;
	ratio = playerShip->GetVelocity() / playerShip->GetMaxSpeed();
	border = h * ( 1 - ratio );
	Speed1->SetSourceRect( vector2df( 0, border ), vector2df( w, h ) );
	Speed2->SetSourceRect( vector2df( 0, 0 ) , vector2df( w, border ) );
	val = playerShip->GetVelocity() * 350;
	str = L"速度：";
	sprintf_s( buffer, "%d", (s32)val );
	str += buffer;
	str += L"m/s";
	SpeedText->SetText( str );
	// 绘制护盾槽
	w = Shield1->GetOriginSize().Width;
	h = Shield1->GetOriginSize().Height;
	ratio = playerShip->GetShield() / playerShip->GetMaxShield();
	border = h * ( 1 - ratio );
	Shield1->SetSourceRect( vector2df( 0, border ), vector2df( w, h ) );
	Shield2->SetSourceRect( vector2df( 0, 0 ) , vector2df( w, border ) );
	val = playerShip->GetShield();
	str = L"护盾：";
	sprintf_s( buffer, "%d", (s32)val );
	str += buffer;
	ShieldText->SetText( str );
	// 绘制护甲槽
	w = Armor1->GetOriginSize().Width;
	h = Armor1->GetOriginSize().Height;
	ratio = playerShip->GetArmor() / playerShip->GetMaxArmor();
	border = h * ( 1 - ratio );
	Armor1->SetSourceRect( vector2df( 0, border ), vector2df( w, h ) );
	Armor2->SetSourceRect( vector2df( 0, 0 ) , vector2df( w, border ) );
	val = playerShip->GetArmor();
	str = L"护甲：";
	sprintf_s( buffer, "%d", (s32)val );
	str += buffer;
	ArmorText->SetText( str );
	// 绘制能量槽
	w = Energy1->GetOriginSize().Width;
	h = Energy1->GetOriginSize().Height;
	ratio = (f32)playerShip->GetEnergy() / (f32)playerShip->GetMaxEnergy();
	border = h * ( 1 - ratio );
	Energy1->SetSourceRect( vector2df( 0, border ), vector2df( w, h ) );
	Energy2->SetSourceRect( vector2df( 0, 0 ) , vector2df( w, border ) );
	val = (f32)playerShip->GetEnergy();
	str = L"能量：";
	sprintf_s( buffer, "%d", (s32)val );
	str += buffer;
	EnergyText->SetText( str );

	// 水平仪转动
	core::vector3df vec( 0, 1, 0 );
	f32 rott = (f32)acos( ( Camera->getUpVector().dotProduct( vector3df( 0, 1, 0 ) ) ) / Camera->getUpVector().getLength() ) * RADTODEG;
	Gradienter->SetRotation( rott );

	auto playerList = m_playerManager->GetPlayers();

	// 更新飞船提示框
	for ( auto iter = playerList.begin(); iter != playerList.end(); ++iter )
	{
		UpdateShipTip( (*iter)->GetShip() );
	}

	// 更新锁定框
	UpdateLock();

	// 更新雷达
	UpdateRadar();
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
		vector3df cam2ship = LockedShip->getPosition() - Camera->getPosition();
		toolkit->To2DScreamPos( cam2ship, &screenPos );
		vector2df screenVec = screenPos - vector2df( Driver->getScreenSize().Width / 2.f, Driver->getScreenSize().Height / 2.f );
		f32 ang = (f32)screenVec.getAngle();
		vector3df direction = Camera->getTarget() - Camera->getPosition();
		f32 dotProd = cam2ship.dotProduct( direction );
		//std::cout<< dotProd <<std::endl;
		if ( dotProd > 0 )
			ang = -(ang-90);
		else
			ang = ang - 90;
		indicator1->SetRotation( ang );
	} 
}

void PlayerHelper::LoadHelperUI( boost::shared_ptr<UIManager> uiManager )
{
	// 获取鼠标准心
	Cursor = uiManager->GetUIObjectByName("cursor");
	Cursor->SetVisible( true );
	uiManager->GetUIObjectByName( "centerCursor" )->SetVisible( true );
	// 获取速度槽
	Speed1 = uiManager->GetUIObjectByName( "speed1" );
	Speed1->SetVisible( true );
	Speed2 = uiManager->GetUIObjectByName( "speed2" );
	Speed2->SetVisible( true );
	SpeedText = (UIStaticText*)uiManager->GetUIObjectByName( "speedText" );
	SpeedText->SetVisible( true );
	// 获取护盾槽
	Shield1 = uiManager->GetUIObjectByName( "shield1" );
	Shield1->SetVisible( true );
	Shield2 = uiManager->GetUIObjectByName( "shield2" );
	Shield2->SetVisible( true );
	ShieldText = (UIStaticText*)uiManager->GetUIObjectByName( "shieldText" );
	ShieldText->SetVisible( true );
	// 获取护甲槽
	Armor1 = uiManager->GetUIObjectByName( "armor1" );
	Armor1->SetVisible( true );
	Armor2 = uiManager->GetUIObjectByName( "armor2" );
	Armor2->SetVisible( true );
	ArmorText = (UIStaticText*)uiManager->GetUIObjectByName( "armorText" );
	ArmorText->SetVisible( true );
	// 获取能量槽
	Energy1 = uiManager->GetUIObjectByName( "energy1" );
	Energy1->SetVisible( true );
	Energy2 = uiManager->GetUIObjectByName( "energy2" );
	Energy2->SetVisible( true );
	EnergyText = (UIStaticText*)uiManager->GetUIObjectByName( "energyText" );
	EnergyText->SetVisible( true );
	// 获取水平仪
	//uiManager->GetUIObjectByName( "ring" )->SetVisible( true );
	Gradienter = uiManager->GetUIObjectByName( "gradienter" );
	//Gradienter->SetVisible( true );
	// 获取目标圈
	ShipTipE = uiManager->GetUIObjectByName( "target1" );
	// 获取锁定圈——已锁定
	lock1 = uiManager->GetUIObjectByName( "lock1" );
	// 获取敌军指示
	indicator1 = uiManager->GetUIObjectByName( "indicator1" );
	// 获取雷达圈
	uiManager->GetUIObjectByName( "radarBox" )->SetVisible( true );
	Radar = uiManager->GetUIObjectByName( "radar" );
	REnemy = uiManager->GetUIObjectByName( "rEnemy" );
	RFriend = uiManager->GetUIObjectByName( "rFriend" );
}

void PlayerHelper::UpdateRadar()
{
	using namespace irr::core;

	IShip* playerShip = Player->GetShip();
	vector3df direction = playerShip->getTarget() - playerShip->getPosition();
	// 旋转并绘制雷达圈
	f32 ang = direction.getHorizontalAngle().Y;
	if( playerShip->getUpVector().Y > 0 )
		ang = -ang;
	// 将敌舰标识在雷达上
	auto playerList = m_playerManager->GetPlayers();
	for ( auto iter = playerList.begin(); iter != playerList.end(); ++iter )
	{
		IShip* ship = (*iter)->GetShip();
		// 如果是自己的船，不需要显示在雷达上
		if ( ship == Player->GetShip() )	
			continue;

		vector3df distance = ship->getPosition() - playerShip->getPosition();
		vector2df dir2d = vector2df( distance.X, -distance.Z );
		if( playerShip->getUpVector().Y < 0 )
			dir2d = vector2df( -distance.X, -distance.Z );
		f32 amount = dir2d.getLength();
		dir2d = dir2d.normalize();

		IUIObject* onRadar;
		auto iterator = m_ship_radarMap.find( ship );
		if ( iterator == m_ship_radarMap.end() )
		{
			// 还未创建提示框，那么就创建一个新的
			// 在此处判断敌方还是友方
			onRadar = REnemy->Clone();

			m_ship_radarMap[ ship ] = onRadar;
		}
		else	
		{
			onRadar = iterator->second;
		}
		if ( amount > 6e3 )
		{
			onRadar->SetVisible( false );
		}
		else
		{
			onRadar->SetVisible( true );
			onRadar->SetPosition( dir2d * 0.0333f * amount );// 200 ÷ 6e3
		}
		
	}

	Radar->SetRotation( ang );
}
