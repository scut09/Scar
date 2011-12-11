/********************************************************************
����ʱ��: 2011:9:27   14:54
�ļ���:   MyIrrlichtEngine.cpp
����:     ���� Cedric Porter [ Stupid ET ]	
˵��:     

*********************************************************************/

#include "MyIrrlichtEngine.h"
#include "IUIObject.h"
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "PostProcessMotionBlur.h"
#include "BulletNode.h"
#include "MissleNode.h"
#include "CSceneNodeAnimatorSelfDelFlyStraight.h"
#include "GameBag.h"
#include "MultiplayerScene.h"
#include "MissleFlame.h"
#include "GameBag.h"
#include "ShipFactory.h"
#include "HumanPlayer.h"
#include "CSceneNodeAutoTrackAnimator.h"

MyIrrlichtEngine* MyIrrlichtEngine::m_pIrrlichtEngine = NULL;
IEventReceiver*	MyIrrlichtEngine::pEventReceiver = NULL;

// ���ڴ�С
int MyIrrlichtEngine::screen_width = 1000;
int MyIrrlichtEngine::screen_height = 640;
// ȫ�����ã�Ĭ��Ϊ����
bool MyIrrlichtEngine::bFullScreen = true;

std::stringstream MyIrrlichtEngine::Console_Buffer;	// ����


MyIrrlichtEngine::MyIrrlichtEngine() :
m_lastUpdateTime( 0 ),
	m_bMotionBlur( false ),
	IsServer( true ), 
	NetworkSetting( 0 )
{
	m_gameSceneMgr = new GameSceneManager;
}


MyIrrlichtEngine::~MyIrrlichtEngine()
{
//	delete m_gameSceneMgr;
	delete m_MySceneManager;
}


/*
** ���֣�MyIrrlichtEngine::GetEngine()
** ˵������ȡ����ָ��
**
*/
MyIrrlichtEngine* MyIrrlichtEngine::GetEngine()
{
	if ( ! m_pIrrlichtEngine )
	{
		video::E_DRIVER_TYPE driverType = (video::E_DRIVER_TYPE)video::EDT_OPENGL;

		SIrrlichtCreationParameters param;

		param.WindowSize = core::dimension2d<u32>( screen_width, screen_height );
		param.AntiAlias = 2;
		param.EventReceiver = pEventReceiver;
		param.DriverType = driverType;
		param.Fullscreen = bFullScreen;

		auto pDevice = irr::createDeviceEx( param );

		// �����豸ʧ�ܣ�����NULL
		if ( ! pDevice ) return NULL;

		// �������
		//pDevice->getCursorControl()->setVisible( false );

		// һЩ��ʼ������
		m_pIrrlichtEngine = new MyIrrlichtEngine;
		m_pIrrlichtEngine->m_pDevice = pDevice;
		m_pIrrlichtEngine->m_pDriver = pDevice->getVideoDriver();
		m_pIrrlichtEngine->m_pSmgr = pDevice->getSceneManager();
		m_pIrrlichtEngine->m_pColMan = m_pIrrlichtEngine->m_pSmgr->getSceneCollisionManager();
		m_pIrrlichtEngine->m_currentUIManager = boost::shared_ptr<UIManager>( new UIManager( pDevice->getTimer() ) );

		m_pIrrlichtEngine->m_MySceneManager = new MySceneManager;	// һ��Ҫ�������������ΪMySceneManager���ڹ���ʱֱ��ʹ��MyIrrlichtEngine

		m_pIrrlichtEngine->m_runCallbackFunc = []( void* )->void* { return 0; };

		// ������������ʱ����һЩ�ӵ�������
		m_pIrrlichtEngine->BulletFucker = new BulletNode( m_pIrrlichtEngine->m_pSmgr, m_pIrrlichtEngine->m_pSmgr->getRootSceneNode() );
		m_pIrrlichtEngine->BulletFucker->setID( 8888 );
		m_pIrrlichtEngine->BulletFucker->setMaterialTexture( 0, 
			pDevice->getVideoDriver()->getTexture( "../media/Weapon/bullet.png" ) );
		m_pIrrlichtEngine->BulletFucker->SetVelocity( 1600 );
		m_pIrrlichtEngine->BulletFucker->SetInterval( 60 );

		IMesh* missleMesh = m_pIrrlichtEngine->m_pSmgr->getMesh( _T("../media/Weapon/missle.3ds") ); 
		m_pIrrlichtEngine->MissileFucker = new MissleNode( missleMesh, m_pIrrlichtEngine->m_pSmgr->getRootSceneNode(), m_pIrrlichtEngine->m_pSmgr, 8889 );

	}

	return m_pIrrlichtEngine;
}

scene::ISceneManager* MyIrrlichtEngine::GetSceneManager()
{
	return m_pSmgr;
}

scene::ISceneCollisionManager* MyIrrlichtEngine::GetCollisionManager()
{
	return m_pColMan;
}

video::IVideoDriver* MyIrrlichtEngine::GetVideoDriver()
{
	return m_pDriver;
}

void MyIrrlichtEngine::Run()
{
	core::dimension2d<u32> size = m_pDevice->getVideoDriver()->getScreenSize();
	u32 frameTime = 16;
	wchar_t tmp[255];
	s32 now = 0;
	s32 lastfps = 0;
	s32 sceneStartTime = m_pDevice->getTimer()->getTime();
	//gui::IGUIStaticText* statusText;
	const int lwidth = size.Width - 20;
	const int lheight = 16;
	auto gui = m_pDevice->getGUIEnvironment();

	//core::rect<int> pos( 10, size.Height - lheight - 10, 10 + lwidth, size.Height - 10 );
	////m_pDevice->getGUIEnvironment()->addImage(pos);
	//statusText = m_pDevice->getGUIEnvironment()->addStaticText( L"Loading...",	pos, true );
	//statusText->setOverrideColor( video::SColor( 255, 205, 200, 200 ) );
	//IGUIFont* font = gui->getFont( _T("../media/msyh.ttf") );
	//statusText->setOverrideFont( font );

	// 2D�����
	m_pDriver->getMaterial2D().TextureLayer[0].BilinearFilter = true;
	m_pDriver->getMaterial2D().AntiAliasing = video::EAAM_FULL_BASIC;
	//m_pDriver->enableMaterial2D();

	// �˶�ģ��
	f32	blurStrength = 0.3f;
	IPostProcessMotionBlur *Blur = new IPostProcessMotionBlur( m_pSmgr->getRootSceneNode(), m_pSmgr, 201212 );   
	Blur->initiate( m_pDriver->getScreenSize().Width, m_pDriver->getScreenSize().Height, blurStrength, m_pSmgr );   

	// ����ԭʼ���ʣ��Ա��ڻ���2Dʱ�ָ�ԭʼ�Ĳ�������ӳ��
	auto oldMaterial = m_pDriver->getMaterial2D();

	while ( m_pDevice->run() )
	{
		//if ( ! m_pDevice->isWindowActive() )	continue;

		if ( m_gameSceneMgr->GetCurrentGameScene() == NULL )		return;		// �޳�����������Ϸѭ��

		u32 now = m_pDevice->getTimer()->getRealTime();

		//if ( now - m_lastUpdateTime < frameTime )	// ����֡��
		//{
		//	boost::thread::sleep( boost::get_system_time() + boost::posix_time::milliseconds( 2 ) );
		//	continue;
		//}

		// ����ע��Ļص�����
		m_runCallbackFunc( (void*)this );

		//m_AnimationManager.Run();

		// ������³���
		m_gameSceneMgr->GetCurrentGameScene()->Run();

		m_pDriver->beginScene( true, true, 0 );  //This time the setup is a little bit harder than normal.    
		{
			if ( m_bMotionBlur )
			{
				Blur->render();                     //For to hold it simple you just have to call two functions:                              
				m_pDriver->setRenderTarget( 0 );    //render(), which does the mainwork(blending the differen Frames together)         
				Blur->renderFinal();                //and renderFinal(); which will render the result into the given renderTarget.
			}
			else
			{
				m_pSmgr->drawAll();
			}

			m_pDriver->setMaterial( oldMaterial );		// �ָ�ԭʼ��ͼӳ��
			m_gameSceneMgr->GetCurrentGameScene()->Draw();
			gui->drawAll();
		}
		m_pDriver->endScene();               //remark, that Render() will automticly set the right Rendertargets. so no need setting                             


		ClearDeletionList();	// ɾ����ɾ�������еĶ�������Ҫ�ṩ����ɾ������ʹ��

		// write statistics
		const s32 nowfps = m_pDriver->getFPS();

		swprintf(tmp, 255, L"%ls fps:%3d triangles:%0.3f mio/s",
			m_pDriver->getName(), m_pDriver->getFPS(),
			m_pDriver->getPrimitiveCountDrawn(1) * (1.f / 1000000.f));

		//statusText->setText(tmp);
		if ( nowfps != lastfps )
		{
			m_pDevice->setWindowCaption(tmp);
			lastfps = nowfps;
		}

		m_lastUpdateTime = now;
	}
}

void MyIrrlichtEngine::SetCallbackFunc( EngineRunCallbackFuncType func )
{
	m_runCallbackFunc = func;
}

IrrlichtDevice* MyIrrlichtEngine::GetDevice()
{
	return m_pDevice;
}

ModelManager* MyIrrlichtEngine::GetModelManager()
{
	return &m_ModelManager;
}

void MyIrrlichtEngine::AddToDeletionQueue( scene::ISceneNode* node )
{
	if ( ! node )	return;

	node->grab();

	m_ISceneNodeDeletionList.push_back( node );
}

void MyIrrlichtEngine::AddToDeletionQueue( IUIObject* node )
{
	if ( ! node )	return;

	node->grab();

	m_IUIObjectDeleteionList.push_back( node );
}

void MyIrrlichtEngine::AddToDeletionQueue( GameScene* scene )
{
	m_GameSceneDeletionList.push_back( scene );
}

void MyIrrlichtEngine::ClearDeletionList()
{
	// 3D�ڵ�ɾ��
	if ( ! m_ISceneNodeDeletionList.empty() )
	{
		for ( auto iter = m_ISceneNodeDeletionList.begin(); iter != m_ISceneNodeDeletionList.end(); ++iter )
		{
			(*iter)->remove();
			(*iter)->drop();
		}
		m_ISceneNodeDeletionList.clear();
	}

	// 2D�ڵ�ɾ��
	if ( ! m_IUIObjectDeleteionList.empty() )
	{
		for ( auto iter = m_IUIObjectDeleteionList.begin(); iter != m_IUIObjectDeleteionList.end(); ++iter )
		{
			(*iter)->remove();
			(*iter)->drop();
		}
		m_IUIObjectDeleteionList.clear();
	}

	// ��Ϸ������Դ�ͷ�
	if ( ! m_GameSceneDeletionList.empty() )
	{
		for ( auto iter = m_GameSceneDeletionList.begin(); iter != m_GameSceneDeletionList.end(); ++iter )
		{
			(*iter)->Release();
		}
		m_GameSceneDeletionList.clear();
	}

	{
		boost::mutex::scoped_lock lock( m_cloneMutex );
		using namespace Network;
		// ����
		while ( ! m_CloneQueue.empty() )
		{
			switch ( m_CloneQueue.front().GetCMD() )
			{
			case PLAYER_LOCK: 
				{
					dynamic_cast<MultiplayerScene*>( GetGameSceneManager()->GetCurrentGameScene() )->m_playerHelper->AddWarnMsg( InfoAndWarn::PIW_PlayerLock );
				}
				break;
			case NEW_PLAYER_JOIN:
				{
					OnePlayerInfoBag oneplayer;
					PACKAGE p = static_cast<PACKAGE>(m_CloneQueue.front());
					oneplayer = *(OnePlayerInfoBag*)p.GetData();
					
					auto smgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();
					ShipFactory shipFactory;
					IShip* ship = shipFactory.CreateShip( oneplayer.ship_name );
					// ���ô���id
					ship->setID( oneplayer.player_index );
					// ���������Ϣ
					dynamic_cast<MultiplayerScene*>( GetGameSceneManager()->GetCurrentGameScene() )->client->m_players[ oneplayer.player_index ] = ship;;
					ship->grab();	///!!!!!!!!!!һ��Ҫȥdrop,��û
					// ����
					ship->setPosition( core::vector3df( 123141, 12312, 1000000 ) );
					// ������ҹ���
					boost::shared_ptr<HumanPlayer> player = boost::shared_ptr<HumanPlayer>( new HumanPlayer( ship ) );
					player->SetID( oneplayer.player_index );
					//player->SetName( oneplayer.player_name );
					dynamic_cast<MultiplayerScene*>(
						MyIrrlichtEngine::GetEngine()->GetGameSceneManager()->GetCurrentGameScene()
						)->m_playerManager->AddPlayer( player );
					std::cout << "NEW_PLAYER_JOIN " << oneplayer.player_index << std::endl;
				}
				break;
			default:
				CloneWeapon( m_CloneQueue.front() );
				break;
			}
			m_CloneQueue.pop();
		}
	}
	
}

void MyIrrlichtEngine::SetMotionBlur( bool bOpen /*= true */ )
{
	m_bMotionBlur = bOpen;
}

void MyIrrlichtEngine::DestoryEngine()
{
	if ( m_pIrrlichtEngine )
	{
		delete m_pIrrlichtEngine;
		m_pIrrlichtEngine = NULL;
	}
}

void MyIrrlichtEngine::CloneWeapon( const Network::PACKAGE& p )
{
	using namespace Network;

	switch ( p.GetCMD() )
	{
	case BULLET_CREATE:
		{
			BulletCreateBag* bag;
			bag = (BulletCreateBag*)p.GetData();
			switch ( bag->type )
			{
			case 0:
				{
					// �����ӵ�
					ISceneNode* newBullet = MyIrrlichtEngine::GetEngine()->BulletFucker->Clone( 0, 0 );

					newBullet->setMaterialType( EMT_TRANSPARENT_ALPHA_CHANNEL );
					newBullet->setMaterialFlag( EMF_LIGHTING, false );


					// ֱ�ɺ���ɾ������
					auto ani = new CSceneNodeAnimatorSelfDelFlyStraight( 
						bag->start_point, bag->end_point, bag->life, MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime() );
					auto del = MyIrrlichtEngine::GetEngine()->GetSceneManager()->createDeleteAnimator( bag->life );

					// ���ӵ����϶����������ȥ
					newBullet->addAnimator( ani );
					newBullet->addAnimator( del );
					del->drop();
					ani->drop();
				}
				break;
			case 1:
				{
					ISceneNode* newMissle = MyIrrlichtEngine::GetEngine()->MissileFucker->Clone( 0, 0 );
					MissleFlame mfe;
					mfe.AddFlameToScene( newMissle, MyIrrlichtEngine::GetEngine()->GetSceneManager() );
					//Ŀ�괬��ID����startpoint�ĵ�һλ��
					auto missleAni = new CSceneNodeAnimatorAutoTrack( GetSceneManager()->getSceneNodeFromId( (int) bag->start_point.X ) );
					newMissle->addAnimator( missleAni );
					missleAni->drop();
				}
				break;
			default:
				break;
			}
			
		}
	}	
}

//AnimationManager* MyIrrlichtEngine::GetAnimationManager()
//{
//	return &m_AnimationManager;
//}
