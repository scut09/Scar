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


class MultiplayerScene : public GameScene
{
	//AnimationManager*			m_pAnimationMan;
	scene::ICameraSceneNode*	m_pCamera;
	scene::ISceneNode*			m_pSkyBox;
	ModelManager*				m_pModelMan;

public:
	MultiplayerScene() : m_pCamera( 0 ), m_pModelMan( 0 ), bRunOnce( true )
	{	
	}

	~MultiplayerScene();

	virtual void Run();
	virtual void Init();
	virtual void Release();
	virtual void Draw();

public:

	//boost::shared_ptr<Network::BoostClient> client;
	boost::shared_ptr<Network::BoostClient> client;

	boost::shared_ptr<Network::BoostServer> server;

	//scene::ISceneNode* node;

	IUIObject* root;	//测试用


	irrklang::ISoundEngine* pSoundEngine;
	irrklang::ISoundSource* fuck;

	//测试用shader
	SceneNodeShader* shader;
	//RobotManager robotManager;

	boost::shared_ptr<PlayerHelper>		m_playerHelper;
	boost::shared_ptr<PlayerManager>	m_playerManager;

	bool bRunOnce;

	

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