/********************************************************************
    创建时间: 2011-10-8   15:57
    文件名:   MultiplayerScene.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     多人游戏的游戏场景

*********************************************************************/

#ifndef MultiplayerScene_h__
#define MultiplayerScene_h__

#include "GameScene.h"
#include "MyIrrlichtEngine.h"
#include "PlayerHelper.h"
#include "PlayerManager.h"
#include "Boost_Client.h"
#include "Boost_Server.h"
#include "irrKlang.h"
#include "SceneNodeShader.h"
#include "LaserNode.h"

class MultiplayerScene : public GameScene
{
	//AnimationManager*			m_pAnimationMan;
	scene::ICameraSceneNode*	m_pCamera;
	scene::ISceneNode*			m_pSkyBox;
	ModelManager*				m_pModelMan;
	LaserNode* 					laser1;
	IShip* 						npc;

public:
	enum MultiState
	{
		Select_Camp,		// 选阵营
		Select_Ship,		// 选船
		Transition1,		// 过渡1，从星系拉近到行星
		Select_Equipment,	// 选武器装备
		First_Flight,		// 首次起飞
		Warp,				// 跃迁
		In_Battle,			// 战斗
		Dead,				// 死亡
		Game_Over,			// 游戏结束
		Quit,				// 返回到多人菜单
		Test				// 测试用
	};

public:
	MultiplayerScene() : m_pCamera( 0 ), m_pModelMan( 0 ), bRunOnce( true )
	{	
	}

	~MultiplayerScene();

	virtual void Run();

	void TestFuck() 
	{
		MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
		IVideoDriver* driver = pEngine->GetVideoDriver();
		if ( bRunOnce )
		{
			bRunOnce = false;

			Sleep( 1500 );

			auto rooms = client->GetRooms();
			auto localIP = client->GetLocalIP();

			auto iter = rooms.begin();
			for ( ; iter != rooms.end(); ++iter )
			{
				std::cout << "Room " << iter->first << " ";
				std::wcout << iter->second.room_name << std::endl;

				if ( rooms.size() > 1 && localIP.find( iter->first ) == localIP.end() )		// 非本机IP
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
	}

	void InBattle();

	virtual void Init();
	virtual void Release();
	virtual void Draw();

	void InitScene();

public:

	// 服务端与客户端
	boost::shared_ptr<Network::BoostClient> client;
	boost::shared_ptr<Network::BoostServer> server;

	// 测试用音效
	irrklang::ISoundEngine* pSoundEngine;
	irrklang::ISoundSource* fuck;

	// 测试用shader
	SceneNodeShader* shader;
	//RobotManager robotManager;

	// 玩家相关
	boost::shared_ptr<PlayerHelper>		m_playerHelper;
	boost::shared_ptr<PlayerManager>	m_playerManager;

	// 初始化标志
	bool bRunOnce;
	// 状态标志
	MultiState State;

	// 环境
	ISceneNode* Sun;						// 恒星
	ISceneNode* Flare;
	ISceneNode* Planet1;
	ISceneNode* Planet2;
	ISceneNode* Moon1;
	ISceneNode* Station1;
	ISceneNode* Station2;

	// 菜单
	IUIObject* SelectCampMenu;				// 阵营选择菜单
	IUIObject* SelectShipMenu;				// 舰船选择菜单
	IUIObject* SelectEquiMenu;				// 武器装备选择菜单

	

	irr::gui::IGUIStaticText* console;
	void UpdateConsole()
	{
		if ( ! console->isVisible() )	return;
		std::string buf = MyIrrlichtEngine::Console_Buffer.str();
		if ( buf.empty() )	
			return;

		std::wstring str( buf.begin(), buf.end() );
		str = console->getText() + str;
		std::size_t remain = 800;
		if ( str.length() > remain )
		{
			std::size_t pos = str.length() - remain;
			while ( pos )
			{
				if ( str[ pos ] == _T('\n') )
				{
					break;
				}
				pos--;
			}
			str = str.substr( pos );
		}
		console->setText( str.c_str() );
		MyIrrlichtEngine::Console_Buffer.clear();
	}

};


#endif // MultiplayerScene_h__