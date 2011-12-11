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
#include "WarpFlyTubeContoller.h"
//#include "ScoreBoard.h"

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
		Loading,			// 装载画面
		Select_Camp,		// 选阵营
		Select_Ship,		// 选船
		Transition1,		// 过渡1，从星系拉近到行星
		Select_Equipment,	// 选武器装备
		Transition2,		// 过渡2, 从行星拉近至空间站
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

	// 三角形选择器
	IMetaTriangleSelector* m_sceneSelector;		// 场景三角形选择器，包含场景内所有的三角形选择器
	ITriangleSelector* m_mapSelector;		// 地图三角形选择器

	// 音效
	irrklang::ISoundEngine* m_pSoundEngine;
	irrklang::ISoundSource* SoundMenuBG;
	irrklang::ISoundSource* SoundBG1;
	irrklang::ISoundSource* SoundClick;
	irrklang::ISound*	SoundCurrentBG;		// 同一时刻只能有一个Bg存在
	irrklang::ISound*	SoundNextBG;
	irrklang::ISound*	SoundThruster;		// 推进器轰鸣

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
	int SubState;							// 状态中的子状态
	u32 LastTime;							// 上次时间

	// 环境
	ISceneNode* Sun;						// 恒星
	ISceneNode* Flare;
	ISceneNode* Planet1;
	ISceneNode* Planet2;
	ISceneNode* Moon1;
	ISceneNode* Station1;
	ISceneNode* Station2;
	ISceneNode* BattleField;
	ISceneNode* bfEarth;
	ISceneNode* bfMoon;
	ISceneNode* bfGate;
	WarpFlyTubeController WarpTube;

	// 菜单
	IUIObject* SelectCampMenu;				// 阵营选择菜单
	IUIObject* SelectShipMenu;				// 舰船选择菜单
	IUIObject* SelectEquiMenu;				// 武器装备选择菜单
	//IUIObject* ScoreBoard;					// 计分板

	// 装载画面
	IUIObject* LoadingImg;

	//记分板
	//ScoreBoard scBoard;

	

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