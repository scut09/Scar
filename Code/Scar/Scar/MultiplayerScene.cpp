/********************************************************************
创建时间: 2011-10-8   16:01
文件名:   MultiplayerScene.cpp
作者:     华亮 Cedric Porter [ Stupid ET ]	
说明:     多人游戏场景

*********************************************************************/


#include "AllAnimators.h"
#include "AllUIObjects.h"
#include "BulletNode.h"
#include "CSceneNodeAnimatorSelfDelFlyStraight.h"
#include "EngineHeader.h"
#include "Flame.h"
#include "Frigate.h"
#include "MultiplayerScene.h"
#include "MySceneManager.h"
#include "PlayerManager.h"
#include "PythonManager.h"
#include "RobotShip.h"
#include "Robot_Client.h"
#include "SpriteFlame.h"
#include "UIAnimators.h"
#include "UIManager.h"
#include <iostream>
#include "HumanPlayer.h"
#include "MySceneManager.h"
#include "GeneralCallBack.h"
#include "PythonWrapper.h"
#include "RunWay.h"
//#include "SunFlareCallBack.h"
#include "SunFlareAnimator.h"
#include "InfoAndWarn.h"

#define PRINT_POS( pos ) std::cout << #pos ## " " << pos.X << ' ' << pos.Y << ' ' << pos.Z << std::endl;

using namespace irrklang;

template< class T >
struct Fuck
{
	T data;
	Fuck( T d ) : data( d ) {}
};

MultiplayerScene::~MultiplayerScene()
{
	Release();

	// Test
	new Fuck< boost::shared_ptr<Network::BoostClient> >( client );
	new Fuck< boost::shared_ptr<Network::BoostServer> >( server );
}


void MultiplayerScene::Run()
{
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	ISceneManager* smgr = pEngine->GetSceneManager();
	IVideoDriver* driver = pEngine->GetVideoDriver();
	boost::shared_ptr<UIManager> uiManager = pEngine->GetUIManager();
	boost::shared_ptr<IPlayer> player = pEngine->GetCurrentPlayer();
	shader = new SceneNodeShader();

	switch ( State )
	{
	case Select_Camp:
		#pragma region SelectCamp
{
			// 如果是第一次运行，初始化
			if ( bRunOnce )
			{
				bRunOnce = false;
				// 在此处进行初始化工作
				// 装载场景


				// 创建网络 
				{

					Sleep( 1500 );

					auto rooms = client->GetRooms();
					auto localIP = client->GetLocalIP();

					auto iter = rooms.begin();
					for ( ; iter != rooms.end(); ++iter )
					{
						std::cout << "Room " << iter->first << " ";
						std::wcout << iter->second.room_name << std::endl;

						if ( rooms.size() > 1 && localIP.find( iter->first ) == localIP.end() )         // ·?±??úIP
						{       
							std::cout << "enter " << iter->first << std::endl;
							client->EnterRoom( iter->first );
							break;
						}
					}

					if ( iter == rooms.end()  ) 
						if ( ! localIP.empty() )
							client->EnterRoom( *localIP.begin() );          
						else
							client->EnterRoom( "127.0.0.1" );

					//Sleep( 2000 );

					//client->Send( "192.168.1.121" );

					while ( -11 == client->m_index )
					{
						Sleep( 500 );
					}

					std::cout << "m_index " << client->m_index << std::endl;

				}


				try
				{
					using namespace boost::python;
					object map = import( "SelectCampScene" );
					object LoadMap = map.attr( "LoadMap" );
					LoadMap();
				}
				catch ( ... )
				{
					PyErr_Print();
				}

				// 恒星
				Sun = smgr->getSceneNodeFromName( "Sun" );
				Flare = smgr->getSceneNodeFromName( "flare" );
				SunFlareAnimator* sunAni = new SunFlareAnimator();
				Flare->addAnimator( sunAni );
				sunAni->drop();

				// 行星与卫星
				Planet1 = smgr->getSceneNodeFromName( "planet1" );
				Planet2 = smgr->getSceneNodeFromName( "planet2" );
				Moon1 = smgr->getSceneNodeFromName( "Satellite1" );

				//// 跃迁管道
				//IMeshSceneNode* tube = smgr->addMeshSceneNode( smgr->getMesh( "../media/UnitModel/cylinder.3ds" ) );
				//tube->setMaterialFlag( EMF_LIGHTING, false );
				//tube->setMaterialFlag( EMF_BACK_FACE_CULLING, false );
				//tube->setMaterialType( EMT_TRANSPARENT_ADD_COLOR );
				//tube->setMaterialTexture( 0, driver->getTexture( "../media/Space/shieldhardening.png" ) );
				//tube->setScale( vector3df( 10, 10, 300 ) );

				// 空间站
				Station1 = smgr->getSceneNodeFromName( "station1" );
				Station2 = smgr->getSceneNodeFromName( "station2" );

				// 显示选择阵营菜单
				SelectCampMenu = uiManager->GetUIObjectByName( "scMenu" );
				SelectCampMenu->SetVisible( true );
				SelectCampMenu->SetAlpha( 0 );
				IUIAnimator* alpAni = uiManager->CreateAnimatorAlphaChange( 0, 1000, 0, 255 );
				SelectCampMenu->AddAnimator( alpAni );
				alpAni->drop();

				// 播放背景音乐
				SoundCurrentBG = m_pSoundEngine->play2D( SoundMenuBG, false, true );
				SoundCurrentBG->setIsPaused( false );

			}

			// 在此处进行游戏逻辑
			/*m_playerHelper->m_infoAndWarn.UpdateInfo();*/
			
			if ( player->GetTeam() != 0 )
			{
				m_pSoundEngine->play2D( SoundClick );
				State = Transition1;
				// 在此处释放资源或隐藏资源
				bRunOnce = true;
			}
		}
		break;
#pragma endregion SelectCamp
	case Transition1:
		#pragma region Transition1
		{
			ISceneNode* ActiveStation;
			if ( bRunOnce )
			{
				bRunOnce = false;
				// 选阵营菜单消失
				SelectCampMenu->SetVisible( false );

				// 显示
				Moon1->setVisible( true );
				if ( player->GetTeam() == 1 )
					ActiveStation = Station1;
				else 
					ActiveStation = Station2;
				ActiveStation->setVisible( true );

				// 拉镜头动画
				auto ani1 = smgr->createFlyStraightAnimator( vector3df(-5e5, -1e5, 8e5), vector3df(3e5,0.5e5,-1e5), 2500 );
				Planet1->addAnimator( ani1 );
				ani1->drop();
				auto ani2 = new CSceneNodeCameraTargetChange( 0, 2500, vector3df( 1,0,0) );
				m_pCamera->addAnimator( ani2 );
				ani2->drop();
				auto ani3 = pEngine->GetMySceneManager()->createScaleAnimator( 2000, 500, vector3df( 1.99f) );
				ActiveStation->addAnimator( ani3 );
				ani3->drop();
				auto ani4 = smgr->createFlyStraightAnimator( vector3df(0,0,18e5), vector3df(18e5,0,0), 2500 );
				Sun->addAnimator( ani4 );
				ani4->drop();
			}

			// 跳到下一场景
			if ( m_pCamera->getAnimators().empty() )
			{
				bRunOnce = true;
				State = Select_Ship;
			}
		}
		break;
#pragma endregion Transition1
	case Select_Ship:
		#pragma region SelectShip
{
			if ( bRunOnce )
			{
				bRunOnce = false;
				player->SetConfirm( false );
				// 隐藏不需要绘制的东西
				Planet2->setVisible( false );

				if( player->GetTeam() == 1 )
				{
					SelectShipMenu = uiManager->GetUIObjectByName( "ssMenuC" );
					player->SetShipName( L"cf1" );
				}
				else
				{
					SelectShipMenu = uiManager->GetUIObjectByName( "ssMenuG" );
					player->SetShipName( L"gf1" );
				}

				SelectShipMenu->SetVisible( true );
				SelectShipMenu->SetAlpha( 0 );
				IUIAnimator* alpAni = uiManager->CreateAnimatorAlphaChange( 0, 1000, 0, 255 );
				SelectShipMenu->AddAnimator( alpAni );
				alpAni->drop();
			}
			// 逻辑
			if ( player->GetTeam() == 1 )
			{
				if ( player->GetShipName() == L"cf1" )
				{
					SelectShipMenu->GetChildren()[0]->GetChildren()[0]->SetVisible( false );
					SelectShipMenu->GetChildren()[0]->GetChildren()[1]->SetVisible( true );
				}
				else if ( player->GetShipName() == L"cf2" )
				{
					SelectShipMenu->GetChildren()[1]->GetChildren()[0]->SetVisible( false );
					SelectShipMenu->GetChildren()[1]->GetChildren()[1]->SetVisible( true );
				}
			}
			else
			{
				if ( player->GetShipName() == L"gf1" )
				{
					SelectShipMenu->GetChildren()[0]->GetChildren()[0]->SetVisible( false );
					SelectShipMenu->GetChildren()[0]->GetChildren()[1]->SetVisible( true );
				}
				else if ( player->GetShipName() == L"gf2" )
				{
					SelectShipMenu->GetChildren()[1]->GetChildren()[0]->SetVisible( false );
					SelectShipMenu->GetChildren()[1]->GetChildren()[1]->SetVisible( true );
				}
			}
			// 跳至下一场景
			if ( player->GetConfirm() )
			{
				// 选中音效
				m_pSoundEngine->play2D( SoundClick );
				// 为玩家赋予选定的船
				IShip* ship;
				if ( player->GetTeam() == 1 )
				{
					if ( player->GetShipName() == L"cf1" )
					{
						ship = pEngine->GetMySceneManager()->addFrigateSceneNode( L"../model/ship/cf1.obj" );
					}
					else if ( player->GetShipName() == L"cf2" )
					{
						ship = pEngine->GetMySceneManager()->addFrigateSceneNode( L"../model/ship/cf1.obj" );
					}
				}
				else
				{
					if ( player->GetShipName() == L"gf1" )
					{
						ship = pEngine->GetMySceneManager()->addFrigateSceneNode( L"../model/ship/cf1.obj" );
					}
					else if ( player->GetShipName() == L"gf2" )
					{
						ship = pEngine->GetMySceneManager()->addFrigateSceneNode( L"../model/ship/cf1.obj" );
					}
				}
				GeneralCallBack* cb = new GeneralCallBack( ship );
				shader->ApplyShaderToSceneNode( ship, cb, "Shader/cf_1V.vert", "Shader/cf_1F.frag" );
				cb->drop();
				ship->setMaterialFlag( EMF_BACK_FACE_CULLING, false );
				ship->setVisible( false );
				player->SetShip( ship );

				State = Select_Equipment;
				bRunOnce = true;
			}
		}
		break;
#pragma endregion SelectShip
	case Select_Equipment:
		#pragma region SelectEquipment
{
			// 初始化
			if ( bRunOnce )
			{
				bRunOnce = false;
				player->SetConfirm( false );
				// 隐藏菜单
				SelectShipMenu->SetVisible( false );
				// 显示选装备菜单
				SelectEquiMenu = uiManager->GetUIObjectByName( "seMenu" );
				SelectEquiMenu->SetVisible( true );
			}

			// 导航栏
			if ( uiManager->GetUIObjectByName( "buyListGun" )->GetVisible() )
			{
				SelectEquiMenu->GetChildren()[0]->GetChildren()[0]->SetVisible( false );
				SelectEquiMenu->GetChildren()[0]->GetChildren()[1]->SetVisible( true );
			}
			else if ( uiManager->GetUIObjectByName( "buyListMissle" )->GetVisible() )
			{
				SelectEquiMenu->GetChildren()[1]->GetChildren()[0]->SetVisible( false );
				SelectEquiMenu->GetChildren()[1]->GetChildren()[1]->SetVisible( true );
			}

			// 跳转至下一个场景
			if ( player->GetConfirm() )
			{
				// 选中音效
				m_pSoundEngine->play2D( SoundClick );
				bRunOnce = true;
				State = Transition2;
			}
		}
		break;
#pragma endregion SelectEquipment
	case Transition2:
		#pragma region Transition2
{
			if ( bRunOnce )
			{
				bRunOnce = false;
				SelectEquiMenu->SetVisible( false );
				// 隐藏鼠标
				pEngine->GetDevice()->getCursorControl()->setVisible( false );
				// 使空间站暂时不相对行星静止
				ISceneNode* ActiveStation;
				if ( player->GetTeam() == 1 )
					ActiveStation = Station1;
				else
					ActiveStation = Station2;
				vector3df lastPos = ActiveStation->getAbsolutePosition();
				ActiveStation->setParent( smgr->getRootSceneNode() );
				ActiveStation->setPosition( lastPos );

				// 使行星和卫星相对摄像机静止
				auto relStay = pEngine->GetMySceneManager()->createRelateCameraStayAnimator(
					0, 1000, m_pCamera, Planet1->getAbsolutePosition() );
				Planet1->addAnimator( relStay );
				relStay->drop();

				//m_pCamera->setPosition( vector3df(1e3,0,0) );
				//m_pCamera->setTarget( vector3df(1e6,0,0) );
				//m_pCamera->setPosition( vector3df(0) );
				// 拖镜头，旋转
				if ( player->GetTeam() == 1 )
				{	
					player->GetShip()->setPosition( vector3df(2e5,-0.266e5,0.5e5) );
					auto ani = pEngine->GetMySceneManager()->createTheBeginMoveAnimator( 
						m_pCamera->getPosition(), vector3df(2e5,-0.266e5,0.5e5), 0, 3000, 1 );
					m_pCamera->addAnimator( ani );
					ani->drop();
				}
				else
				{
					player->GetShip()->setPosition( vector3df(2e5,-0.35e5,0.5e5) );
					auto ani = pEngine->GetMySceneManager()->createTheBeginMoveAnimator( 
						m_pCamera->getPosition(), vector3df(2e5,-0.35e5,0.5e5), 0, 3000, 1 );
					m_pCamera->addAnimator( ani );
					ani->drop();
				}
				player->GetShip()->setVisible( true );
				player->GetShip()->setRotation( vector3df( 0, 90, 0 ) );
				player->GetShip()->setTarget( player->GetShip()->getPosition() + vector3df(1,0,0) );
				/*auto ani = smgr->createFlyStraightAnimator( vector3df(0), vector3df(2e5,-0.35e5,0.5e5), 1000 );
				m_pCamera->addAnimator( ani );
				ani->drop();*/
			}

			if ( m_pCamera->getAnimators().empty() )
			{
				State = First_Flight;
				bRunOnce = true;
			}

		}
		break;
#pragma endregion Transition2
	case First_Flight:
		{
		#pragma region FirstFlight
			if ( bRunOnce )
			{
				bRunOnce = false;
				SubState = 0;
				m_pCamera->removeAnimators();
				// 将镜头平移至飞船
				m_pCamera->setTarget( player->GetShip()->getPosition() + vector3df(50,0,0) );
				auto ani = pEngine->GetMySceneManager()->createTheBeginMoveAnimator(
					m_pCamera->getPosition(), player->GetShip()->getPosition()+vector3df(-10,0,0), 0, 2000, 1 );
				m_pCamera->addAnimator( ani );
				ani->drop();
				// 换背景音效
				SoundNextBG = m_pSoundEngine->play2D( SoundBG1, false, true );
				SoundNextBG->setVolume( 0 );
				SoundNextBG->setIsPaused( false );
			}
			else if ( m_pCamera->getAnimators().empty() && SubState == 0 )
			{
				SubState = 1;
				IShip* playerShip = player->GetShip();
				playerShip->SetArmor( 0 );
				playerShip->SetShield( 0 );
				playerShip->SetEnergy( 0 );
				/*auto ctrlAni = new CSceneNodeAnimatorAircraftFPS( pEngine->GetDevice()->getCursorControl() );
				playerShip->addAnimator( ctrlAni );
				ctrlAni->drop();*/
				auto folowAni = new CSceneNodeAnimatorCameraFollowShip( player->GetShip(), 30 );
				m_pCamera->addAnimator( folowAni );
				folowAni->drop();
			}
			else if( SubState == 1 )
			{
				SubState = 2;
				m_playerHelper->LoadHelperUI( pEngine->GetUIManager() );
				player->SetConfirm( false );
				// 装逼文字
				m_playerHelper->AddInfoMsg( InfoAndWarn::PII_B0 );
				m_pSoundEngine->play2D( "../sound/connecting.ogg" );
				m_pSoundEngine->play2D( "../sound/onlogin04.wav" );
			}
			else if ( SubState == 2 )
			{
				// UI动画
				IShip* playerShip = player->GetShip();
				if ( m_playerHelper->Armor1->GetAlpha() > 0 && playerShip->GetArmor() < playerShip->GetMaxArmor() )
				{
					// 装逼文字
					if( playerShip->GetArmor() < 10 )
						m_playerHelper->AddInfoMsg( InfoAndWarn::PII_B1 );
					if( playerShip->GetArmor() > 980 )
						m_playerHelper->AddInfoMsg( InfoAndWarn::PII_B6 );
					playerShip->SetArmor( playerShip->GetArmor() + 5 );
				}
				if ( m_playerHelper->Shield1->GetAlpha() > 0 && playerShip->GetShield() < playerShip->GetMaxShield() )
				{
					playerShip->SetShield( playerShip->GetShield() + 5 );
				}
				if ( m_playerHelper->Energy1->GetAlpha() > 0 && playerShip->GetEnergy() < playerShip->GetMaxEnergy() )
				{
					// 装逼文字
					if ( playerShip->GetEnergy() < 10 )
					{
						m_playerHelper->AddInfoMsg( InfoAndWarn::PII_B3 );
						m_playerHelper->AddInfoMsg( InfoAndWarn::PII_B4 );
					}
					playerShip->SetEnergy( playerShip->GetEnergy() + 5 );
				}
				if ( m_playerHelper->Cursor->GetAlpha() == 255 && !player->GetConfirm() )
				{
					// 装逼文字
					m_playerHelper->AddInfoMsg( InfoAndWarn::PII_B7 );
					player->SetConfirm( true );
					ISceneNode* runway = pEngine->GetMySceneManager()->addRunWaySceneNode( 
						player->GetShip()->getPosition(), 400.0f, 300.0f, vector3df(0,63,255), vector3df(255,220,0), 25 );
					runway->setRotation( vector3df( 0, 90, 0) );
					runway->setID( 4002 );
					LastTime = pEngine->GetDevice()->getTimer()->getTime();
				}
				playerShip->SetVelocity( 0.5f );
				playerShip->setPosition( playerShip->getPosition() + vector3df( 0.5, 0, 0 ) );
				playerShip->setTarget( playerShip->getPosition() + vector3df( 1, 0, 0 ) );

				// 换背景音效
				if ( SoundNextBG->getVolume() < 1 )
				{
					SoundCurrentBG->setVolume( SoundCurrentBG->getVolume() - 0.005f );
					SoundNextBG->setVolume( SoundNextBG->getVolume() + 0.005f );
					if ( SoundNextBG->getVolume() >= 1 )
					{
						SoundCurrentBG->stop();
						SoundCurrentBG = SoundNextBG;
						SoundCurrentBG->setVolume( 1 );
						SoundNextBG->setVolume( 1 );
					}
				}

				if ( player->GetConfirm() && pEngine->GetDevice()->getTimer()->getTime() - LastTime > 4500 )
				{
					SubState = 3;
					auto ani = pEngine->GetMySceneManager()->createShakeAnimatorAnimator( 0, 1000, 3 );
					m_pCamera->addAnimator( ani );
					ani->drop();
					m_playerHelper->AddInfoMsg( InfoAndWarn::PII_B5 );
					m_pSoundEngine->play2D( "../sound/warpdirectional.wav" );
					m_pSoundEngine->play2D( "../sound/autopilotengaged.ogg" );
					SoundThruster = m_pSoundEngine->play2D( "../sound/booster_blue_b02a.ogg", true, true );
					SoundThruster->setVolume( 0 );
					LastTime = pEngine->GetDevice()->getTimer()->getTime();
				}

				m_playerHelper->Update();
				m_playerManager->Update();

			}
			else if ( SubState == 3 )
			{
				u32 timeMS = pEngine->GetDevice()->getTimer()->getTime();
				
				if ( timeMS - LastTime > 2500 )
				{
					SubState = 4;
					m_playerHelper->AddInfoMsg( InfoAndWarn::PII_B8 );
					m_pSoundEngine->play2D( "../sound/warpdriveactive.ogg" );
					SoundThruster->setIsPaused( false );
					//LastTime = pEngine->GetDevice()->getTimer()->getTime();
				}

			}
			else if ( SubState == 4 )
			{
				IShip* playerShip = player->GetShip();
				playerShip->SetVelocity( playerShip->GetVelocity() + 0.002f * playerShip->GetMaxSpeed() );
				if ( playerShip->GetVelocity() / playerShip->GetMaxSpeed() > 0.7 )
					SubState = 5;
			}
			else if ( SubState == 5 )
			{
				IShip* playerShip = player->GetShip();
				playerShip->SetVelocity( playerShip->GetVelocity() - 0.02f * playerShip->GetMaxSpeed() );
				if ( playerShip->GetVelocity() <= 0 )
				{
					playerShip->SetVelocity( 0 );
					SubState = 6;
					LastTime = pEngine->GetDevice()->getTimer()->getTime();
					auto ani = pEngine->GetMySceneManager()->createShakeAnimatorAnimator(
						0, 4500, 0, 2 );
					m_pCamera->addAnimator( ani );
					ani->drop();
				}
			}
			else if ( SubState == 6 )
			{
				u32 t = pEngine->GetDevice()->getTimer()->getTime() - LastTime;
				if ( t > 200 )
				{
					IShip* playerShip = player->GetShip();
					if ( playerShip->GetVelocity() < playerShip->GetMaxSpeed() )
						playerShip->SetVelocity( playerShip->GetVelocity() + 0.04f * playerShip->GetMaxSpeed() );
					else if ( playerShip->GetVelocity() > playerShip->GetMaxSpeed() )
						playerShip->SetVelocity( playerShip->GetMaxSpeed() );
					
					playerShip->setPosition( playerShip->getPosition() + vector3df( (f32)(t/10), 0, 0 ) );
					playerShip->setTarget( playerShip->getPosition() + vector3df( 1, 0, 0 ) );
				}
				if ( t > 2500 )
				{
					State = Warp;
					bRunOnce = true;
				}
			}

			if ( SubState > 2 )
			{
				IShip* playerShip = player->GetShip();
				if ( SubState < 4 )
					playerShip->SetVelocity( 0.5f );
				if ( SubState < 6 )
				{
					playerShip->setPosition( playerShip->getPosition() + vector3df( 0.5, 0, 0 ) );
					playerShip->setTarget( playerShip->getPosition() + vector3df( 1, 0, 0 ) );
				}
				
				SoundThruster->setVolume( playerShip->GetVelocity() / playerShip->GetMaxSpeed() );

				m_playerHelper->Update();
				m_playerManager->Update();
			}
			
			pEngine->GetDevice()->getCursorControl()->setPosition( 0.5f, 0.5f );

		}
#pragma endregion FirstFlight
		break;
	case Warp:
		{
			if ( bRunOnce )
			{
				bRunOnce = false;

				// 隐藏不必要的节点
				Station1->setVisible( false );
				Station2->setVisible( false );
				smgr->getSceneNodeFromId( 4002 )->setVisible( false );

				SubState = 0;
			}

			if ( SubState == 0 )
			{
				if ( m_pCamera->getAnimators().getSize() == 1 )
				{
					auto ani = pEngine->GetMySceneManager()->createShakeAnimatorAnimator(
						0, 10000, 2, 2 );
					m_pCamera->addAnimator( ani );
					ani->drop();
					SubState = 1;
				}
				//std::cout<< m_pCamera->getAnimators().getSize() << std::endl;
				//SubState = 1;
			}
			else if ( SubState == 1 )
			{
				// 卫星远离
				// 解除月球和行星的父子关系
				Moon1->setPosition( Moon1->getAbsolutePosition() );
				Moon1->setParent( smgr->getRootSceneNode() );
				auto ani = pEngine->GetMySceneManager()->createFlyStraightAnimator(
					Moon1->getPosition(),
					Moon1->getPosition() - ( m_pCamera->getTarget() - m_pCamera->getPosition() ).normalize() * 2e5,
					2000 );
				Moon1->addAnimator( ani );
				ani->drop();

				SubState = 2;
				LastTime = pEngine->GetDevice()->getTimer()->getTime();
			}
			else if ( SubState == 2 )
			{
				// 行星远离
				// 去掉相对镜头静止
				if (  pEngine->GetDevice()->getTimer()->getTime() - LastTime > 500 )
				{
					Planet1->removeAnimators();
					auto ani = pEngine->GetMySceneManager()->createFlyStraightAnimator(
						Planet1->getPosition(), 
						Planet1->getPosition() - ( m_pCamera->getTarget() - m_pCamera->getPosition() ).normalize() * 20e5,
						3000 );
					Planet1->addAnimator( ani );
					ani->drop();

					SubState = 3;
					LastTime = pEngine->GetDevice()->getTimer()->getTime();
				}
			}
			else if ( SubState == 3 )
			{
				if ( pEngine->GetDevice()->getTimer()->getTime() - LastTime > 2000 )
				{
					//SelectCampMenu->SetVisible( true );
					//m_pCamera->removeAnimator( (*m_pCamera->getAnimators().end()) );
					SubState = 4;
					State = In_Battle;
					bRunOnce = true;
				}
				
			}

			m_playerHelper->Update();
			m_playerManager->Update();
			//pEngine->GetDevice()->getCursorControl()->setPosition( 0.5f, 0.5f );
		}
		break;
	case In_Battle:
		{
			IShip* playerShip = player->GetShip();
			if ( bRunOnce )
			{
				//SelectCampMenu->SetVisible( false );
				//// 获取引擎
				//MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
				//scene::ISceneManager* smgr = pEngine->GetSceneManager();
				//smgr->clear();

				//m_pModelMan = pEngine->GetModelManager();
				//IVideoDriver* driver = pEngine->GetVideoDriver();

				//shader = new SceneNodeShader();


				//// 隐藏鼠标
				//pEngine->GetDevice()->getCursorControl()->setVisible(false);


				//// 创建飞船
				//IShip* cf1;
				//IMesh* cf1Mesh = smgr->getMesh( _T("../model/ship/cf1.obj") )->getMesh(0);
				//if ( cf1Mesh )
				//{
				//	IMesh* tangentMesh = smgr->getMeshManipulator()->createMeshWithTangents(cf1Mesh, true);
				//	cf1 = new CFrigate( tangentMesh, 0, smgr, -1 );	
				//	cf1->setName( "cf1" );
				//	cf1->setMaterialTexture( 1, driver->getTexture(_T("../model/ship/caldarifighter_tex_ngs.tga")) );
				//	cf1->setMaterialFlag( EMF_BACK_FACE_CULLING, false );
				//	GeneralCallBack* cb = new GeneralCallBack( cf1 );
				//	shader->ApplyShaderToSceneNode( cf1, cb, "Shader/cf_1V.vert", "Shader/cf_1F.frag" );
				//	cb->drop();
				//	tangentMesh->drop();
				//}
				////飞船尾焰
				//SpriteFlame spf;
				//spf.SetOffset( vector3df( -6, 0, -22 ) );
				//spf.AddFlameToShip( playership, smgr );
				//spf.SetOffset( vector3df( 6, 0, -22 ) );
				//spf.AddFlameToShip( cf1, smgr );

				playerShip->removeAnimators();
				m_pCamera->removeAnimators();
				playerShip->setTarget( playerShip->getPosition() + vector3df( 1, 0, 0 ) );
				playerShip->setUpVector( vector3df( 0, 1, 0 ) );

				auto ctrlAni = new CSceneNodeAnimatorAircraftFPS( pEngine->GetDevice()->getCursorControl() );
				playerShip->addAnimator( ctrlAni );
				ctrlAni->drop();
				auto flowAni = new CSceneNodeAnimatorCameraFollowShip( playerShip, 30 );
				m_pCamera->addAnimator( flowAni );
				flowAni->drop();

				// 创建子弹
				BulletNode* bullet = new BulletNode( smgr, smgr->getRootSceneNode() );
				bullet->setMaterialTexture( 0, driver->getTexture( "../media/Weapon/bullet.png" ) );
				bullet->SetVelocity( 1000 );
				bullet->SetInterval( 100 );
				playerShip->AddGun( bullet );
				bullet->drop();

				//飞船尾焰
				SpriteFlame spf;
				spf.SetOffset( vector3df( -6, 0, -22 ) );
				spf.AddFlameToShip( playerShip, smgr );
				spf.SetOffset( vector3df( 6, 0, -22 ) );
				spf.AddFlameToShip( playerShip, smgr );

				// 添加robot
				IShip* npc;
				boost::shared_ptr<ShipAgentPlayer> robot;
				// robot 1
				npc = new CFrigate( smgr->getMesh("../module/1234.obj"), 0, smgr, 99 );
				npc->SetMaxSpeed( 2 );
				npc->setPosition( vector3df( playerShip->getAbsolutePosition() + vector3df( 10000, 10000, 10000 ) ) );
				spf.SetOffset( vector3df( -6, 0, -22 ) );
				spf.AddFlameToShip( npc, smgr );
				spf.SetOffset( vector3df( 6, 0, -22 ) );
				spf.AddFlameToShip( npc, smgr );
				bullet = new BulletNode( smgr, smgr->getRootSceneNode() );
				bullet->setMaterialTexture( 0, driver->getTexture( "../media/Weapon/bullet.png" ) );
				bullet->SetVelocity( 1000 );
				bullet->SetInterval( 100 );
				npc->AddGun( bullet );
				bullet->drop();	
				robot = boost::shared_ptr<ShipAgentPlayer>( new ShipAgentPlayer( npc, &*m_playerManager, server ) );
				m_playerManager->AddPlayer( robot );
				// robot 2
				npc = new CFrigate( smgr->getMesh("../module/1234.obj"), 0, smgr, 98 );
				npc->SetMaxSpeed( 2 );
				npc->setPosition( vector3df( (f32)(rand() % 100), (f32)(rand() % 100), (f32)(1000 + rand() % 1000) ) );
				spf.SetOffset( vector3df( -6, 0, -22 ) );
				spf.AddFlameToShip( npc, smgr );
				spf.SetOffset( vector3df( 6, 0, -22 ) );
				spf.AddFlameToShip( npc, smgr );
				bullet = new BulletNode( smgr, smgr->getRootSceneNode() );
				bullet->setMaterialTexture( 0, driver->getTexture( "../media/Weapon/bullet.png" ) );
				bullet->SetVelocity( 1000 );
				bullet->SetInterval( 100 );
				npc->AddGun( bullet );
				bullet->drop();	
				robot = boost::shared_ptr<ShipAgentPlayer>( new ShipAgentPlayer( npc, &*m_playerManager, server ) );
				m_playerManager->AddPlayer( robot );

				// 创建火控
				auto fireAni = new ShipFireAnimator( client );
				playerShip->addAnimator( fireAni );
				fireAni->drop();


				bRunOnce = false;
			}

			InBattle();
		}
		break;
	case Dead:
		{

		}
		break;
	case Game_Over:
		{

		}
		break;
	case Quit:
		{

		}
		break;
	case Test:
		{
			InitScene();
			TestFuck();
			State = In_Battle;
		}
		break;
	}
}

void MultiplayerScene::Init()
{
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	IVideoDriver* driver = pEngine->GetVideoDriver();

	// 初始化状态为选阵营  测试可以将此处改为想要的状态
	State = Select_Camp;
	
	// 兼容Test状态
	if ( State != Test )
	{
		// 初始化摄像机
		//m_pCamera = pEngine->GetSceneManager()->addCameraSceneNodeFPS(0, 50.f, 1e2);
		m_pCamera = pEngine->GetSceneManager()->addCameraSceneNode();
		m_pCamera->setFarValue( 1e7 );
		m_pCamera->setFOV( 1 );
		m_pCamera->setAspectRatio( (f32)driver->getScreenSize().Width / (f32)driver->getScreenSize().Height );

		// 初始化玩家与飞船
		// 飞船为默认值，在玩家选船后更换模型
		IShip* playerShip = pEngine->GetMySceneManager()->addFrigateSceneNode( L"../model/ship/cf1.obj" );
		playerShip->setVisible( false );
		boost::shared_ptr<HumanPlayer> player = boost::shared_ptr<HumanPlayer>( new HumanPlayer( playerShip ) );
		pEngine->SetCurrentPlayer( player );

		// 加载UI界面
		pEngine->SetUIManager( boost::shared_ptr<UIManager>( new UIManager( pEngine->GetDevice()->getTimer() ) ) );
		try
		{
			using namespace boost::python;

			object UILoader = import( "MultiPlayIni" );
			object GetRoot = UILoader.attr( "GetRoot" );
			object root = GetRoot();	
		}
		catch ( ... )
		{
			PyErr_Print();
		}

		// 加载玩家管理类和玩家辅助类
		m_playerManager = boost::shared_ptr<PlayerManager>( new PlayerManager );
		m_playerManager->AddPlayer( player );
		m_playerHelper = boost::shared_ptr<PlayerHelper>( new PlayerHelper );
		//m_playerHelper->LoadHelperUI( pEngine->GetUIManager() );
		m_playerHelper->LoadPlayer( player );
		m_playerHelper->LoadPlayerManager( &*m_playerManager );


		// 加载音效
		m_pSoundEngine = createIrrKlangDevice();
		m_pSoundEngine->setSoundVolume( 0.6f );
		SoundMenuBG = m_pSoundEngine->addSoundSourceFromFile( "../sound/Ambient005.ogg" );
		SoundBG1 = m_pSoundEngine->addSoundSourceFromFile( "../sound/Ambient041.ogg" );
		SoundClick = m_pSoundEngine->addSoundSourceFromFile( "../sound/click.wav", irrklang::ESM_AUTO_DETECT, true );
		//std::cout<<SoundMenuBG->getDefaultVolume()<<std::endl;
		//std::cout<<"--------------------------------------"<<std::endl;



		server = boost::shared_ptr<Network::BoostServer>( new BoostServer );
		client = boost::shared_ptr<Network::BoostClient>( new Network::BoostClient( m_playerManager ) );

		server->Start( 1990, 2012 );
		client->Start( 2012, 1990 );

		client->QueryRoom();


		// 创建控制台
		IGUIEnvironment* gui = MyIrrlichtEngine::GetEngine()->GetDevice()->getGUIEnvironment();
		IGUISkin* skin = gui->getSkin();
		IGUIFont* font = gui->getFont("../media/fonthaettenschweiler.bmp");
		if (font)
			skin->setFont(font);
		skin->setFont( gui->getBuiltInFont(), EGDF_TOOLTIP );
		console = gui->addStaticText( _T(""), core::rect<s32>( 0, 20, 500, 600 ), true, true, 0, -1, true );
		console->setVisible(false);

		dynamic_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [this]( const SEvent& event )->void*
		{	
			MyIrrlichtEngine::GetEngine()->GetUIManager()->OnEvent( event );

			m_playerManager->OnEvent( event );

			if ( event.KeyInput.PressedDown )
			{
				if ( event.KeyInput.Key == KEY_F1 )
				{
					console->setVisible( ! console->isVisible() );
					if ( console->isVisible() )
					{
						UpdateConsole();
						//gui->setFocus( console );
					}
				}
			}

			return 0;
		} );

	}
}

void MultiplayerScene::Release()
{
	//	m_playerManager->RemoveAll();
	m_pSoundEngine->stopAllSounds();
	m_pSoundEngine->drop();

	try
	{
		//if ( client.use_count() > 0 && server.use_count() > 0 )
		//{
		//	client->Close();
		//	server->Close();
		//}
	}
	catch ( std::exception& e )
	{
		std::cerr << e.what() << std::endl;
	}
	catch ( ... )
	{
		std::cerr << "client" << std::endl;

	}



	//	m_pAnimationMan->RemoveAll();


}

void MultiplayerScene::Draw()
{
	//uiManager->RunTree();
	MyIrrlichtEngine::GetEngine()->GetUIManager()->DrawAll();
}

void MultiplayerScene::InitScene()
{
	// 获取引擎
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	scene::ISceneManager* smgr = pEngine->GetSceneManager();
	smgr->clear();

	m_pModelMan = pEngine->GetModelManager();
	IVideoDriver* driver = pEngine->GetVideoDriver();

	shader = new SceneNodeShader();


	// 隐藏鼠标
	pEngine->GetDevice()->getCursorControl()->setVisible(false);


	// 创建飞船
	IShip* cf1;
	IMesh* cf1Mesh = smgr->getMesh( _T("../model/ship/cf1.obj") )->getMesh(0);
	if ( cf1Mesh )
	{
		IMesh* tangentMesh = smgr->getMeshManipulator()->createMeshWithTangents(cf1Mesh, true);
		cf1 = new CFrigate( tangentMesh, 0, smgr, -1 );	
		cf1->setName( "cf1" );
		cf1->setMaterialTexture( 1, driver->getTexture(_T("../model/ship/caldarifighter_tex_ngs.tga")) );
		cf1->setMaterialFlag( EMF_BACK_FACE_CULLING, false );
		GeneralCallBack* cb = new GeneralCallBack( cf1 );
		shader->ApplyShaderToSceneNode( cf1, cb, "Shader/cf_1V.vert", "Shader/cf_1F.frag" );
		cb->drop();
		tangentMesh->drop();
	}
	//cf1->setPosition( vector3df(0,-40,0)); 

	//m_playerHelper.LoadPlayerShip( boost::shared_ptr<)

	//飞船尾焰
	SpriteFlame spf;
	spf.SetOffset( vector3df( -6, 0, -22 ) );
	spf.AddFlameToShip( cf1, smgr );
	spf.SetOffset( vector3df( 6, 0, -22 ) );
	spf.AddFlameToShip( cf1, smgr );

	// 创建子弹
	BulletNode* bullet = new BulletNode( smgr, smgr->getRootSceneNode() );
	bullet->setMaterialTexture( 0, driver->getTexture( "../media/Weapon/bullet.png" ) );
	bullet->SetVelocity( 1000 );
	bullet->SetInterval( 100 );
	cf1->AddGun( bullet );
	bullet->drop();

	//  加入摄像机
	//m_pCamera = smgr->addCameraSceneNodeFPS( 0, 100, 50.0f );
	m_pCamera = smgr->addCameraSceneNode();

	auto fpsAni = new CSceneNodeAnimatorAircraftFPS( pEngine->GetDevice()->getCursorControl() );
	cf1->addAnimator( fpsAni );
	fpsAni->drop();

	m_pCamera->setFOV( 1 );
	m_pCamera->setFarValue( 1e7f );

	/*auto shakeAni = new MySceneNodeAnimatorShake( 0, 80000, 1.2f );
	m_pCamera->addAnimator( shakeAni );
	shakeAni->drop();*/

	// 开场动画
	auto BeginMove = new TheBeginMove( vector3df(50000),vector3df(0), 1000, 5000, 1 );
	m_pCamera->addAnimator( BeginMove );
	BeginMove->drop();

	//m_pCamera->setParent( cf1 );
	// 飞船跟随照相机
	auto folowAni = new CSceneNodeAnimatorCameraFollowShip( cf1, 30 );
	m_pCamera->addAnimator( folowAni );
	folowAni->drop();

	//加载行星
	auto planet = smgr->addSphereSceneNode( 4e5, 64 );
	if ( planet )
	{
		// 设置名称
		planet->setName( "planet1" );
		// 加载纹理
		planet->setMaterialTexture( 0, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/planet5.jpg") ) );
		planet->setMaterialTexture( 1, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/night0.jpg") ) );
		planet->setMaterialTexture( 2, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/a.tga") ) );
		// 星球自转
		auto rot = smgr->createRotationAnimator( vector3df( 0, 0.005f, 0) );
		planet->addAnimator( rot );
		rot->drop();
		// Shader
		GeneralCallBack* cb = new GeneralCallBack( planet );
		shader->ApplyShaderToSceneNode( planet, cb, "Shader/PlanetGroundV.vert", "Shader/PlanetGroundF.frag" );
		cb->drop();
		//// 设置初始大小
		//planet->setScale( vector3df( .01f ) );
		//// 缩放动画
		//auto sca = new MySceneNodeAnimatorScale( 0, 8000, vector3df( 1.99f ), AS_MT_LOG );
		//planet->addAnimator( sca );
		//sca->drop();
		// 行星永远相对镜头
		auto relstayAni = new RelateCameraAnimatorStay( 0, 1000, m_pCamera, vector3df( -2e5, 0, 8e5 ) );
		planet->addAnimator( relstayAni );
		relstayAni->drop();
	}
	// 行星大气圈
	ISceneNode* planetAtmos = smgr->addSphereSceneNode( 4.2e5, 64, planet );
	if ( planetAtmos )
	{
		planetAtmos->setMaterialFlag( EMF_BACK_FACE_CULLING, false );
		planetAtmos->setMaterialFlag( EMF_FRONT_FACE_CULLING, true );
		//planetAtmos->setMaterialFlag( EMF_ZBUFFER, false );
		GeneralCallBack* cb = new GeneralCallBack( planetAtmos );
		// Shader
		shader->ApplyShaderToSceneNode( planetAtmos, cb, "Shader/PlanetAtmosV.vert", "Shader/PlanetAtmosF.frag",EMT_TRANSPARENT_ADD_COLOR );
		cb->drop();
	}


	//加载卫星
	auto moon = smgr->addSphereSceneNode( 1e5, 64 );
	if ( moon )
	{
		// 设置名称
		moon->setName( "moon1" );
		// 加载纹理
		moon->setMaterialTexture( 0, pEngine->GetVideoDriver()->getTexture( _T("../media/Planets/planet1.jpg") ) );
		// 星球自转
		auto rot = smgr->createRotationAnimator( vector3df( 0, -0.006f, 0) );
		moon->addAnimator( rot );
		rot->drop();
		//// 设置初始大小
		//moon->setScale( vector3df( .001f ) );
		//// 缩放动画
		//auto sca = new MySceneNodeAnimatorScale( 2000, 6000, vector3df( 1.999f ), AS_MT_LOG, 500 );
		//moon->addAnimator( sca );
		//sca->drop();
		//// 飞跃星球效果
		//auto relmovAni = new RelateCameraAnimatorMove( 2000, 6000, m_pCamera,
		//	vector3df(1e5, 0, 2.5e5), vector3df(1e5, 0, -2.5e5), RM_MT_LOG, 800 );
		//moon->addAnimator( relmovAni );
		//relmovAni->drop();
		// 卫星永远相对镜头
		auto relstayAni = new RelateCameraAnimatorStay( 0, 1000, m_pCamera, vector3df( 1e5, 0, 2.5e5 ) );
		moon->addAnimator( relstayAni );
		relstayAni->drop();
	}

	//pSoundEngine = createIrrKlangDevice();
	//fuck = pSoundEngine->addSoundSourceFromFile("../media/booster_blue_b02a.ogg");

	//fuck->setVolume( fuck->getVolume() - 10 );

	//加载空间站模型

	IMesh* stationMesh = smgr->getMesh( _T("../model/station/cs1.obj") );
	if ( stationMesh )
	{
		IMesh* tangentMesh = smgr->getMeshManipulator()->createMeshWithTangents(stationMesh, true);
		IMeshSceneNode* station = smgr->addMeshSceneNode( tangentMesh );
		station->setName( "station1" );
		station->setMaterialTexture( 1, driver->getTexture(_T("../model/station/cs1_tex_ngs.tga")) );
		GeneralCallBack* cb = new GeneralCallBack( station );
		shader->ApplyShaderToSceneNode( station, cb, "Shader/cs_1V.vert", "Shader/cs_1F.frag" );
		cb->drop();
		tangentMesh->drop();
	}

	////加载太阳
	//auto sun = smgr->addSphereSceneNode( 200000 );
	//if ( sun )
	//{
	//	// 设置名称
	//	moon->setName( "sun1" );
	//}

	// 太阳光（平行光）
	video::SLight light1;
	light1.Type = ELT_DIRECTIONAL;
	light1.SpecularColor = video::SColorf( 0.1f, 0.1f, 0.1f );
	light1.AmbientColor = video::SColorf( 0.15f, 0.15f, 0.15f );
	//light1.AmbientColor = video::SColorf( 0,0,0 );
	auto lsn = smgr->addLightSceneNode();
	lsn->setLightData( light1 );
	lsn->setRotation( vector3df( 0, 90, 0 ) );

	m_playerManager = boost::shared_ptr<PlayerManager>( new PlayerManager );
	m_playerHelper = boost::shared_ptr<PlayerHelper>( new PlayerHelper );

	// 加载UI界面
	pEngine->SetUIManager( boost::shared_ptr<UIManager>( new UIManager( pEngine->GetDevice()->getTimer() ) ) );

	try
	{
		using namespace boost::python;

		object UILoader = import( "MultiPlayIni" );
		object GetRoot = UILoader.attr( "GetRoot" );
		object root = GetRoot();

		m_playerHelper->LoadHelperUI( pEngine->GetUIManager() );
		m_playerHelper->LoadPlayerManager( &*m_playerManager );

		object map = import( "MapV1" );
		object LoadMap = map.attr( "LoadMap" );
		LoadMap();

	}
	catch ( ... )
	{
		PyErr_Print();
	}



	boost::shared_ptr<HumanPlayer>	humanPlayer( new HumanPlayer( cf1 ) );
	m_playerHelper->LoadPlayer( humanPlayer );
	m_playerManager->AddPlayer( humanPlayer );

	//playerManager = new PlayerManager( uiManager, cf1 );

	//playerManager->AddPlayer( cf1->getID(), cf1 );

	try
	{
		server = pEngine->GetServer();//boost::shared_ptr<Network::BoostServer>( new Network::BoostServer );
		if ( server.use_count() == 0 )
		{
			CreateRoom();
			server = pEngine->GetServer();
		}
		client = pEngine->GetClient();//boost::shared_ptr<Network::BoostClient>( new Network::BoostClient( &*m_playerManager ) );
		if ( client.use_count() == 0 )
		{
			auto playerManager = boost::shared_ptr<PlayerManager>( new PlayerManager );
			client = boost::shared_ptr<Network::BoostClient>( new Network::BoostClient( playerManager ) );
			pEngine->SetClient( client );
			client->Start( 2012, 1990 );
		}
	}
	catch ( std::exception& e )
	{
		std::cerr << e.what() << std::endl;
	}

	//server->Start( 1990, 2012 );
	//client->Start( 2012, 1990 );



	// 添加robot
	IShip* npc;
	boost::shared_ptr<ShipAgentPlayer> robot;
	// robot 1
	npc = new CFrigate( smgr->getMesh("../module/1234.obj"), 0, smgr, 99 );
	npc->SetMaxSpeed( 2 );
	npc->setPosition( vector3df( (f32)(rand() % 100), (f32)(rand() % 100), (f32)(1000 + rand() % 1000) ) );
	spf.SetOffset( vector3df( -6, 0, -22 ) );
	spf.AddFlameToShip( npc, smgr );
	spf.SetOffset( vector3df( 6, 0, -22 ) );
	spf.AddFlameToShip( npc, smgr );
	bullet = new BulletNode( smgr, smgr->getRootSceneNode() );
	bullet->setMaterialTexture( 0, driver->getTexture( "../media/Weapon/bullet.png" ) );
	bullet->SetVelocity( 1000 );
	bullet->SetInterval( 100 );
	npc->AddGun( bullet );
	bullet->drop();	
	robot = boost::shared_ptr<ShipAgentPlayer>( new ShipAgentPlayer( npc, &*m_playerManager, server ) );
	m_playerManager->AddPlayer( robot );
	// robot 2
	npc = new CFrigate( smgr->getMesh("../module/1234.obj"), 0, smgr, 98 );
	npc->SetMaxSpeed( 2 );
	npc->setPosition( vector3df( (f32)(rand() % 100), (f32)(rand() % 100), (f32)(1000 + rand() % 1000) ) );
	spf.SetOffset( vector3df( -6, 0, -22 ) );
	spf.AddFlameToShip( npc, smgr );
	spf.SetOffset( vector3df( 6, 0, -22 ) );
	spf.AddFlameToShip( npc, smgr );
	bullet = new BulletNode( smgr, smgr->getRootSceneNode() );
	bullet->setMaterialTexture( 0, driver->getTexture( "../media/Weapon/bullet.png" ) );
	bullet->SetVelocity( 1000 );
	bullet->SetInterval( 100 );
	npc->AddGun( bullet );
	bullet->drop();	
	robot = boost::shared_ptr<ShipAgentPlayer>( new ShipAgentPlayer( npc, &*m_playerManager, server ) );
	m_playerManager->AddPlayer( robot );

	// 创建火控
	auto fireAni = new ShipFireAnimator( client );
	cf1->addAnimator( fireAni );
	fireAni->drop();

	//
	client->QueryRoom();

	//

	IGUIEnvironment* gui = MyIrrlichtEngine::GetEngine()->GetDevice()->getGUIEnvironment();
	IGUISkin* skin = gui->getSkin();
	IGUIFont* font = gui->getFont("../media/fonthaettenschweiler.bmp");
	if (font)
		skin->setFont(font);

	skin->setFont( gui->getBuiltInFont(), EGDF_TOOLTIP );

	IGUIEditBox* box = gui->addEditBox( _T(""), core::rect<s32>( 0, 0, 100, 50 ) );


	console = gui->addStaticText( _T(""), core::rect<s32>( 0, 20, 500, 600 ), true, true, 0, -1, true );
	console->setVisible(false);


	//	gui->addScrollBar( false, core::recti( 0, 0, 200, 200 ), console );

	box->setVisible( false );

	//auto as = core::rect<s32>;

	MyIrrlichtEngine::GetEngine()->SetMotionBlur( true );

	console->setText( _T("Press F1 to show or close this box" ) );

	// 创建并注册receiver的事件处理回调函数
	dynamic_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc(
		[ this, gui, box ]( const SEvent& event )->void*
	{	
		m_playerManager->OnEvent( event );

		if ( event.KeyInput.PressedDown )
		{
			if ( event.KeyInput.Key == KEY_KEY_T )
			{
				box->setText( _T("") );
				box->setVisible( true );
				gui->setFocus( box );		
			}
			else if ( event.KeyInput.Key == KEY_RETURN )
			{
				box->setVisible( false );
				gui->setFocus( 0 );		
				client->BroadcastMessage( client->m_index, box->getText() );
				std::wcout << box->getText() << std::endl;
			}
			else if ( event.KeyInput.Key == KEY_ESCAPE )
			{
				box->setVisible( false );
				gui->setFocus( 0 );		
			}
			else if ( event.KeyInput.Key == KEY_KEY_I )
			{
				MyIrrlichtEngine::GetEngine()->SetMotionBlur( true );
			}
			else if ( event.KeyInput.Key == KEY_KEY_O )
			{
				MyIrrlichtEngine::GetEngine()->SetMotionBlur( false );
			}
			else if ( event.KeyInput.Key == KEY_F1 )
			{
				console->setVisible( ! console->isVisible() );
				if ( console->isVisible() )
				{
					UpdateConsole();
					//gui->setFocus( console );
				}
			}
			else if ( event.KeyInput.Key == KEY_KEY_P )
			{
				auto smgr = MyIrrlichtEngine::GetEngine()->GetGameSceneManager();
				smgr->SetCurrentGameScene( smgr->GetSceneByName( "MainMenu" ) );
			}
		}
		return 0;
	} );


}

void MultiplayerScene::InBattle()
{
	try
	{	
		auto pos = m_pCamera->getPosition();
		client->SendHeroMove( client->m_index, pos.X, pos.Y, pos.Z );
		auto rot = m_pCamera->getRotation();
		client->SendHeroRot( client->m_index, rot.X, rot.Y, rot.Z );
	}
	catch ( std::exception& e )
	{
		std::cerr << e.what() << std::endl;
	}
	catch ( ... )
	{
		std::cerr << "ERROR!!!!!!!!!!!!!!!!1" << std::endl;
	}

	UpdateConsole();

	m_playerHelper->Update();

	m_playerManager->Update();
}

