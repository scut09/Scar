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
	if ( ship == Player->GetShip() )	return;	// ������Լ��Ĵ�������Ҫ����ס

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
	using namespace irr::core;
	// ׼��׷�����
	auto CursorPos = CursorControl->getPosition();
	Cursor->SetPosition( vector2df( (f32)CursorPos.X, (f32)CursorPos.Y ) );

	IShip* playerShip = Player->GetShip();

	f32 ratio;
	f32 border;
	char buffer[20];	// ����ת�ַ�������
	f32 val;			// ����
	stringw str;		// �ַ���
	f32 h, w;			// Ԫ���ߺͿ�
	// �����ٶȲ�
	w = Speed1->GetOriginSize().Width;
	h = Speed1->GetOriginSize().Height;
	ratio = playerShip->GetVelocity() / playerShip->GetMaxSpeed();
	border = h * ( 1 - ratio );
	Speed1->SetSourceRect( vector2df( 0, border ), vector2df( w, h ) );
	Speed2->SetSourceRect( vector2df( 0, 0 ) , vector2df( w, border ) );
	val = playerShip->GetVelocity() * 350;
	str = L"�ٶȣ�";
	sprintf_s( buffer, "%d", (s32)val );
	str += buffer;
	str += L"m/s";
	SpeedText->SetText( str );
	// ���ƻ��ܲ�
	w = Shield1->GetOriginSize().Width;
	h = Shield1->GetOriginSize().Height;
	ratio = playerShip->GetShield() / playerShip->GetMaxShield();
	border = h * ( 1 - ratio );
	Shield1->SetSourceRect( vector2df( 0, border ), vector2df( w, h ) );
	Shield2->SetSourceRect( vector2df( 0, 0 ) , vector2df( w, border ) );
	val = playerShip->GetShield();
	str = L"���ܣ�";
	sprintf_s( buffer, "%d", (s32)val );
	str += buffer;
	ShieldText->SetText( str );
	// ���ƻ��ײ�
	w = Armor1->GetOriginSize().Width;
	h = Armor1->GetOriginSize().Height;
	ratio = playerShip->GetArmor() / playerShip->GetMaxArmor();
	border = h * ( 1 - ratio );
	Armor1->SetSourceRect( vector2df( 0, border ), vector2df( w, h ) );
	Armor2->SetSourceRect( vector2df( 0, 0 ) , vector2df( w, border ) );
	val = playerShip->GetArmor();
	str = L"���ף�";
	sprintf_s( buffer, "%d", (s32)val );
	str += buffer;
	ArmorText->SetText( str );
	// ����������
	w = Energy1->GetOriginSize().Width;
	h = Energy1->GetOriginSize().Height;
	ratio = (f32)playerShip->GetEnergy() / (f32)playerShip->GetMaxEnergy();
	border = h * ( 1 - ratio );
	Energy1->SetSourceRect( vector2df( 0, border ), vector2df( w, h ) );
	Energy2->SetSourceRect( vector2df( 0, 0 ) , vector2df( w, border ) );
	val = playerShip->GetEnergy();
	str = L"������";
	sprintf_s( buffer, "%d", (s32)val );
	str += buffer;
	EnergyText->SetText( str );

	// ˮƽ��ת��
	core::vector3df vec( 0, 1, 0 );
	f32 rott = (f32)acos( ( Camera->getUpVector().dotProduct( vector3df( 0, 1, 0 ) ) ) / Camera->getUpVector().getLength() ) * RADTODEG;
	Gradienter->SetRotation( rott );

	auto playerList = m_playerManager->GetPlayers();

	// ���·ɴ���ʾ��
	for ( auto iter = playerList.begin(); iter != playerList.end(); ++iter )
	{
		UpdateShipTip( (*iter)->GetShip() );
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
	// ��ȡ���׼��
	Cursor = uiManager->GetUIObjectByName("cursor");
	// ��ȡ�ٶȲ�
	Speed1 = uiManager->GetUIObjectByName( "speed1" );
	Speed2 = uiManager->GetUIObjectByName( "speed2" );
	SpeedText = (UIStaticText*)uiManager->GetUIObjectByName( "speedText" );
	// ��ȡ���ܲ�
	Shield1 = uiManager->GetUIObjectByName( "shield1" );
	Shield2 = uiManager->GetUIObjectByName( "shield2" );
	ShieldText = (UIStaticText*)uiManager->GetUIObjectByName( "shieldText" );
	// ��ȡ���ײ�
	Armor1 = uiManager->GetUIObjectByName( "armor1" );
	Armor2 = uiManager->GetUIObjectByName( "armor2" );
	ArmorText = (UIStaticText*)uiManager->GetUIObjectByName( "armorText" );
	// ��ȡ������
	Energy1 = uiManager->GetUIObjectByName( "energy1" );
	Energy2 = uiManager->GetUIObjectByName( "energy2" );
	EnergyText = (UIStaticText*)uiManager->GetUIObjectByName( "energyText" );
	// ��ȡˮƽ��
	Gradienter = uiManager->GetUIObjectByName( "gradienter" );
	// ��ȡĿ��Ȧ
	ShipTip = uiManager->GetUIObjectByName( "target1" );
	ShipTip->SetVisible( false );
	// ��ȡ����Ȧ����������
	lock1 = uiManager->GetUIObjectByName( "lock1" );
	// ��ȡ�о�ָʾ
	indicator1 = uiManager->GetUIObjectByName( "indicator1" );
}
