#include "PlayerHelper.h"
#include "MyIrrlichtEngine.h"
#include <iostream>
#include <string>
#include "VerticalCallBack.h"
#include "MultiplayerScene.h"
#include "ExplosionMyself.h"

PlayerHelper::PlayerHelper()
	: LockedShip( NULL )
{
	Camera = MyIrrlichtEngine::GetEngine()->GetSceneManager()->getActiveCamera();
	Driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
	CursorControl = MyIrrlichtEngine::GetEngine()->GetDevice()->getCursorControl();

	toolkit = boost::shared_ptr<Toolkit>( new Toolkit( Camera, Driver ) );

	IsJustDie = false;
	m_DieTimePoint = 0;
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
		if ( ship->GetTeam() == Player->GetTeam() )
			shipTip = ShipTipF->Clone();
		else
			shipTip = ShipTipE->Clone();

		m_ship_targetMap[ ship ] = shipTip;

		//  Test
		// LockedShip = ship;
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
	val = (f32)playerShip->GetEnergy();
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
	// �����״�
	UpdateRadar();
	// �����˺�����
	UpdateHarmAlert();
	// ������Ϣ����
	m_infoAndWarn.Update();
	// ���¼Ƿְ�
	scBoard->Upadate();

	// ��ʾ�����ʱ
	if (playerShip->GetArmor() <= 0.0f )
	{
		if ( static_cast<MultiplayerScene*>(MyIrrlichtEngine::GetEngine()->GetGameSceneManager()->GetCurrentGameScene())
			->State == MultiplayerScene::In_Battle )
		{

			if (!IsJustDie)
			{
				ExplosionMyself e(playerShip, playerShip->getPosition());
				m_DieTimePoint = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
				ReConStr->SetVisible(true);
				e.Explode();
				e.EndExplode();
				printf("explode \n");
			}
			Revive();
			IsJustDie = true;
		}
		
	}
	else
		IsJustDie = false;
}
void PlayerHelper::Revive()
{
	IShip* playerShip = Player->GetShip();
	u32 duration = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime() - m_DieTimePoint;
	duration /= 1000;
	switch(duration)
	{
	case 0:
		Num1->SetVisible(false);
		Num2->SetVisible(false);
		Num3->SetVisible(false);
		Num4->SetVisible(false);
		Num5->SetVisible(true);
		break;
	case 1:
		Num1->SetVisible(false);
		Num2->SetVisible(false);
		Num3->SetVisible(false);
		Num4->SetVisible(true);
		Num5->SetVisible(false);
		break;
	case 2:
		Num1->SetVisible(false);
		Num2->SetVisible(false);
		Num3->SetVisible(true);
		Num4->SetVisible(false);
		Num5->SetVisible(false);
		break;
	case 3:
		Num1->SetVisible(false);
		Num2->SetVisible(true);
		Num3->SetVisible(false);
		Num4->SetVisible(false);
		Num5->SetVisible(false);
		break;
	case 4:
		Num1->SetVisible(true);
		Num2->SetVisible(false);
		Num3->SetVisible(false);
		Num4->SetVisible(false);
		Num5->SetVisible(false);
		break;
	default:
		Num1->SetVisible(false);
		Num2->SetVisible(false);
		Num3->SetVisible(false);
		Num4->SetVisible(false);
		Num5->SetVisible(false);
		ReConStr->SetVisible(false);
		playerShip->SetArmor(1000.f);
		playerShip->SetShield(1000.f);
		playerShip->setPosition(vector3df(500.f, 500.f, 500.f));
		printf("cccccccccccccccccccccccccc\n");
		break;
	}
}

void PlayerHelper::UpdateLock()
{
	if ( ! LockedShip )		return;

	// ������ȦȦȦסĿ��
	if ( toolkit->GetNode2DInfo( LockedShip, &info2D ) )
	{
		////indicator1->SetVisible( false );
		//f32 sca = info2D.height / 60.0f;
		//if ( sca > 1.2f )
		//	sca = 1.2f;
		//else if ( sca < 0.8f )
		//	sca = 0.8f;

		lock1->SetPosition( info2D.pos );
		//lock1->SetScale( vector2df(sca) );
		lock1->SetVisible( true );
		// ����Ŀ����Ϣ����
		char buffer[20];	// ����ת�ַ�������
		f32 val;			// ����
		stringw str;		// �ַ���
		// ����
		val = LockedShip->GetShield() / LockedShip->GetMaxShield() * 100;
		str = L"���ܣ�";
		sprintf_s( buffer, "%.0f%%", val );
		str += buffer;
		TargetShield->SetText( str );
		// ����
		val = LockedShip->GetArmor() / LockedShip->GetMaxArmor() * 100;
		str = L"���ף�";
		sprintf_s( buffer, "%.0f%%", val );
		str += buffer;
		TargetArmor->SetText( str );
		// ����
		val = ( LockedShip->getPosition() - Player->GetShip()->getPosition() ).getLength() / 20.0f;
		str = L"���룺";
		sprintf_s( buffer, "%.0fkm", val );
		str += buffer;
		TargetDistance->SetText( str );
	}
	else
	{
		lock1->SetVisible( false );
		//indicator1->SetVisible( true );
		//// �����ü�ͷ��ǵط�λ��
		//vector2df screenPos;
		//vector3df cam2ship = LockedShip->getPosition() - Camera->getPosition();
		//toolkit->To2DScreamPos( cam2ship, &screenPos );
		//vector2df screenVec = screenPos - vector2df( Driver->getScreenSize().Width / 2.f, Driver->getScreenSize().Height / 2.f );
		//f32 ang = (f32)screenVec.getAngle();
		//vector3df direction = Camera->getTarget() - Camera->getPosition();
		//f32 dotProd = cam2ship.dotProduct( direction );
		////std::cout<< dotProd <<std::endl;
		//if ( dotProd > 0 )
		//	ang = -(ang-90);
		//else
		//	ang = ang - 90;
		//indicator1->SetRotation( ang );
	}
	IVideoDriver* driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
	s32 width = driver->getViewPort().getWidth(), height = driver->getViewPort().getHeight();
	position2df pos;
	toolkit->To2DScreamPos( LockedShip->getPosition(), &pos );
	pos = pos - position2df( (f32)width * 0.5f, (f32)height * 0.5f );
	if ( pos.getLength() > 293 )
	{
		SetLockedShip( NULL );
		MyIrrlichtEngine::GetEngine()->GetCurrentPlayer()->SetLockedShip( NULL );
		lock1->SetVisible( false );
		indicator1->SetVisible( false );
		// ��ʾ����
		AddInfoMsg( InfoAndWarn::PII_Unlock );
	}
}

void PlayerHelper::LoadHelperUI( boost::shared_ptr<UIManager> uiManager )
{
	IUIAnimator* ani;

	// ��ȡ���׼��
	Cursor = uiManager->GetUIObjectByName("cursor");
	Cursor->SetVisible( true );
	ani = uiManager->CreateAnimatorAlphaChange( 1500, 1000, 0, 255 );
	Cursor->AddAnimator( ani );
	ani->drop();
	IUIObject* cenCur = uiManager->GetUIObjectByName( "centerCursor" );
	cenCur->SetVisible( true );
	ani = uiManager->CreateAnimatorAlphaChange( 2000, 1000, 0, 255 );
	cenCur->AddAnimator( ani );
	ani->drop();
	// ��ȡ�ٶȲ�
	Speed1 = uiManager->GetUIObjectByName( "speed1" );
	Speed1->SetVisible( true );
	ani = uiManager->CreateAnimatorAlphaChange( 500, 1000, 0, 255 );
	Speed1->AddAnimator( ani );
	ani->drop();
	Speed2 = uiManager->GetUIObjectByName( "speed2" );
	Speed2->SetVisible( true );
	ani = uiManager->CreateAnimatorAlphaChange( 500, 1000, 0, 255 );
	Speed2->AddAnimator( ani );
	ani->drop();
	SpeedText = (UIStaticText*)uiManager->GetUIObjectByName( "speedText" );
	SpeedText->SetVisible( true );
	
	// ��ȡ���ܲ�
	Shield1 = uiManager->GetUIObjectByName( "shield1" );
	Shield1->SetVisible( true );
	ani = uiManager->CreateAnimatorAlphaChange( 1000, 1000, 0, 255 );
	Shield1->AddAnimator( ani );
	ani->drop();
	Shield2 = uiManager->GetUIObjectByName( "shield2" );
	Shield2->SetVisible( true );
	ani = uiManager->CreateAnimatorAlphaChange( 1000, 1000, 0, 255 );
	Shield2->AddAnimator( ani );
	ani->drop();
	ShieldText = (UIStaticText*)uiManager->GetUIObjectByName( "shieldText" );
	ShieldText->SetVisible( true );
	// ��ȡ���ײ�
	Armor1 = uiManager->GetUIObjectByName( "armor1" );
	Armor1->SetVisible( true );
	ani = uiManager->CreateAnimatorAlphaChange( 500, 1000, 0, 255 );
	Armor1->AddAnimator( ani );
	ani->drop();
	Armor2 = uiManager->GetUIObjectByName( "armor2" );
	Armor2->SetVisible( true );
	ani = uiManager->CreateAnimatorAlphaChange( 500, 1000, 0, 255 );
	Armor2->AddAnimator( ani );
	ani->drop();
	ArmorText = (UIStaticText*)uiManager->GetUIObjectByName( "armorText" );
	ArmorText->SetVisible( true );
	// ��ȡ������
	Energy1 = uiManager->GetUIObjectByName( "energy1" );
	Energy1->SetVisible( true );
	ani = uiManager->CreateAnimatorAlphaChange( 1000, 1000, 0, 255 );
	Energy1->AddAnimator( ani );
	ani->drop();
	Energy2 = uiManager->GetUIObjectByName( "energy2" );
	Energy2->SetVisible( true );
	ani = uiManager->CreateAnimatorAlphaChange( 1000, 1000, 0, 255 );
	Energy2->AddAnimator( ani );
	ani->drop();
	EnergyText = (UIStaticText*)uiManager->GetUIObjectByName( "energyText" );
	EnergyText->SetVisible( true );
	// ��ȡˮƽ��
	//uiManager->GetUIObjectByName( "ring" )->SetVisible( true );
	Gradienter = uiManager->GetUIObjectByName( "gradienter" );
	//Gradienter->SetVisible( true );
	// ��ȡĿ��Ȧ
	ShipTipE = uiManager->GetUIObjectByName( "target1" );
	ShipTipF = uiManager->GetUIObjectByName( "target2" );
	// ��ȡ����Ȧ����������
	lock1 = uiManager->GetUIObjectByName( "lock1" );
	// ��ȡ�о�ָʾ
	indicator1 = uiManager->GetUIObjectByName( "indicator1" );
	// ��ȡ�״�Ȧ
	IUIObject* radarBox = uiManager->GetUIObjectByName( "radarBox" );
	radarBox->SetVisible( true );
	ani = uiManager->CreateAnimatorAlphaChange( 3000, 1000, 0, 255 );
	radarBox->AddAnimator( ani );
	ani->drop();
	Radar = uiManager->GetUIObjectByName( "radar" );
	REnemy = uiManager->GetUIObjectByName( "rEnemy" );
	RFriend = uiManager->GetUIObjectByName( "rFriend" );
	// ��ȡ����Ŀ��״̬����
	TargetShield = static_cast<UIStaticText*>(uiManager->GetUIObjectByName( "targetShield" ));
	TargetArmor = static_cast<UIStaticText*>(uiManager->GetUIObjectByName( "targetArmor" ));
	TargetDistance = static_cast<UIStaticText*>(uiManager->GetUIObjectByName( "targetDistance" ));
	// ˮƽ�Ǻʹ�ֱ��
	Vertical = MyIrrlichtEngine::GetEngine()->GetSceneManager()->getSceneNodeFromName( "vertical" );
	//Vertical->setVisible( true );
	VerticalCallBack* cb = new VerticalCallBack();
	SceneNodeShader shader;
	shader.ApplyShaderToSceneNode( Vertical, cb, "Shader/Vertical.vert", "Shader/Vertical.frag", EMT_TRANSPARENT_ADD_COLOR );
	cb->drop();
	Horizon = MyIrrlichtEngine::GetEngine()->GetSceneManager()->getSceneNodeFromName( "horizon" );
	//Horizon->setVisible( true );
	
	// ��ȡ��Ļ��ɫ����
	RedMask = uiManager->GetUIObjectByName( "redMaskCtrl" );

	// ��ʼ���Ƿְ�
	scBoard = new ScoreBoard( m_ScoreList );

	// ���뵹��ʱͼƬ

	const rect<s32> r = MyIrrlichtEngine::GetEngine()->GetDevice()->getVideoDriver()->getViewPort();

	ReConStr = uiManager->GetUIObjectByName( "ReconnectString" );
	ReConStr->SetPosition(vector2df((f32)(r.getWidth() - 150), (f32)(r.getHeight() - 150) ));

	Num1 = uiManager->GetUIObjectByName( "1s" );
	Num1->SetPosition(vector2df( (f32)(r.getWidth() - 50), (f32)(r.getHeight() - 100) ));

	Num2 = uiManager->GetUIObjectByName( "2s" );
	Num2->SetPosition(vector2df((f32)(r.getWidth() - 50), (f32)(r.getHeight() - 100) ));

	Num3 = uiManager->GetUIObjectByName( "3s" );
	Num3->SetPosition(vector2df((f32)(r.getWidth() - 50), (f32)(r.getHeight() - 100) ));

	Num4 = uiManager->GetUIObjectByName( "4s" );
	Num4->SetPosition(vector2df((f32)(r.getWidth() - 50), (f32)(r.getHeight() - 100) ));

	Num5 = uiManager->GetUIObjectByName( "5s" );
	Num5->SetPosition(vector2df((f32)(r.getWidth() - 50), (f32)(r.getHeight() - 100) ));




}

void PlayerHelper::UpdateRadar()
{
	using namespace irr::core;

	IShip* playerShip = Player->GetShip();
	vector3df direction = playerShip->getTarget() - playerShip->getPosition();
	// ��ת�������״�Ȧ
	f32 ang = direction.getHorizontalAngle().Y;
	if( playerShip->getUpVector().Y > 0 )
		ang = -ang;
	// ���н���ʶ���״���
	auto playerList = m_playerManager->GetPlayers();
	for ( auto iter = playerList.begin(); iter != playerList.end(); ++iter )
	{
		IShip* ship = (*iter)->GetShip();
		// ������Լ��Ĵ�������Ҫ��ʾ���״���
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
			// ��δ������ʾ����ô�ʹ���һ���µ�
			// �ڴ˴��жϵз������ѷ�
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
			onRadar->SetPosition( dir2d * 0.0333f * amount );// 200 �� 6e3
		}
		
	}

	Radar->SetRotation( ang );
}

void PlayerHelper::UpdateHarmAlert()
{
	if ( static_cast<MultiplayerScene*>(MyIrrlichtEngine::GetEngine()->GetGameSceneManager()->GetCurrentGameScene())->State != MultiplayerScene::In_Battle )
		return;

	IShip* playerShip = Player->GetShip();
	f32 CurrentShield = playerShip->GetShield();
	f32 CurrentArmor = playerShip->GetArmor();

	if ( CurrentShield != LastShield )
	{
		if ( CurrentShield < LastShield )
		{
			if ( CurrentShield / playerShip->GetMaxShield() < 0.3f )
			{
				AddWarnMsg( InfoAndWarn::PIW_LowShield );
			}
		}

		LastShield = CurrentShield;
	}

	if ( CurrentArmor != LastArmor )
	{
		if ( CurrentArmor < LastArmor )
		{
			if ( CurrentArmor / playerShip->GetMaxArmor() < 0.3f )
			{
				AddWarnMsg( InfoAndWarn::PIW_LowArmor );
			}
		}

		LastArmor = CurrentArmor;
	}

	// ��Ļ����
	if ( CurrentArmor / playerShip->GetMaxArmor() > 0.25f )
	{
		RedMask->SetVisible( false );
	}
	else
	{
		RedMask->SetVisible( true );
		f32 alpha = ( 1 - CurrentArmor / playerShip->GetMaxArmor() * 4 ) * 255;
		RedMask->SetAlpha( alpha );
	}

}
