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
	// 绘制速度槽
	ratio = playerShip->GetVelocity() / playerShip->GetMaxSpeed();
	border = 389 * ( 1 - ratio );
	Speed1->SetSourceRect( vector2df( 0, border ), vector2df( 98, 389 ) );
	Speed2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 98, border ) );
	val = playerShip->GetVelocity() * 350;
	str = L"速度：";
	sprintf_s( buffer, "%d", (s32)val );
	str += buffer;
	str += L"m/s";

	SpeedText->SetText( str );

	// 绘制护盾槽
	ratio = playerShip->GetShield() / playerShip->GetMaxShield();
	border = 389 * ( 1 - ratio );
	Shield1->SetSourceRect( vector2df( 0, border ), vector2df( 100, 389 ) );
	Shield2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 100, border ) );
	// 绘制护甲槽
	ratio = playerShip->GetArmor() / playerShip->GetMaxArmor();
	border = 360 * ( 1 - ratio );
	Armor1->SetSourceRect( vector2df( 0, border ), vector2df( 93, 360 ) );
	Armor2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 93, border ) );

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

void PlayerHelper::LoadHelperUI( UIManager* uiManager )
{
	// 获取鼠标准心
	Cursor = uiManager->GetUIObjectByName("cursor");
	// 获取速度槽
	Speed1 = uiManager->GetUIObjectByName( "speed1" );
	Speed2 = uiManager->GetUIObjectByName( "speed2" );
	//SpeedText = new UIStaticText( uiManager->GetRoot(), 100, 100, L"速度：", irr::video::SColor(255,255,255,255), 20 );
	//SpeedText->SetPosition( vector2df( 200, 200 ) );
	SpeedText = (UIStaticText*)uiManager->GetUIObjectByName( "speedText" );
	// 获取护盾槽
	Shield1 = uiManager->GetUIObjectByName( "shield1" );
	Shield2 = uiManager->GetUIObjectByName( "shield2" );
	ShieldText = (UIStaticText*)uiManager->GetUIObjectByName( "speedText" );
	// 获取护甲槽
	Armor1 = uiManager->GetUIObjectByName( "armor1" );
	Armor2 = uiManager->GetUIObjectByName( "armor2" );
	ArmorText = (UIStaticText*)uiManager->GetUIObjectByName( "armorText" );
	// 获取水平仪
	Gradienter = uiManager->GetUIObjectByName( "gradienter" );
	// 获取目标圈
	ShipTip = uiManager->GetUIObjectByName( "target1" );
	ShipTip->SetVisible( false );
	// 获取锁定圈——已锁定
	lock1 = uiManager->GetUIObjectByName( "lock1" );
	// 获取敌军指示
	indicator1 = uiManager->GetUIObjectByName( "indicator1" );
}
