/********************************************************************
创建时间: 2011:9:27   14:54
文件名:   MyIrrlichtEngine.h
作者:     华亮 Cedric Porter [ Stupid ET ]	
说明:     引擎的包装

*********************************************************************/

#ifndef _MYIRRLICHTENGINE_H_
#define _MYIRRLICHTENGINE_H_

#include "Boost_Client.h"
#include "Boost_Server.h"
#include "GameScene.h"
#include "GameSceneManager.h"
#include "ModelManager.h"
#include "MySceneManager.h"
#include "PlayerManager.h"
#include "UIManager.h"
#include "def.h"
#include <functional>
#include <irrlicht.h>
#include <list>
#include <sstream>
//#include "AnimationManager.h"
//#include "IMovable.h"

class IUIObject;

using namespace irr;

typedef std::function< void*( void* ) > EngineRunCallbackFuncType;

/*
** 名字：MyIrrlichtEngine
** 说明：单例模式
**
*/
class MyIrrlichtEngine
{
private:
	IrrlichtDevice*					m_pDevice;		// 设备
	video::IVideoDriver*			m_pDriver;		// 驱动
	scene::ISceneManager*			m_pSmgr;		// 场景管理器
	scene::ISceneCollisionManager*	m_pColMan;		// 碰撞管理器
	scene::ICameraSceneNode*		m_pCamera;		// 相机，暂时没用

	static MyIrrlichtEngine*		m_pIrrlichtEngine;	// 单例模式，唯一的引擎
	EngineRunCallbackFuncType		m_runCallbackFunc;  // 每次帧运行时都会调用的回调函数

	bool							m_bMotionBlur;		// 是否开启运动模糊

	boost::shared_ptr<UIManager>	m_currentUIManager;	// 2D的UIManager

	GameSceneManager*				m_gameSceneMgr;		// 场景管理类

	MySceneManager*					m_MySceneManager;	// 类似irrlicht的场景管理类

	boost::shared_ptr<Network::BoostClient> m_client;

	boost::shared_ptr<Network::BoostServer> m_server;

	boost::shared_ptr<IPlayer>		m_currentPlayer;	// 当前玩家



private:
	ModelManager					m_ModelManager;
	//AnimationManager				m_AnimationManager;		// 过时，抛弃这个。使用irrlicht内部的动画管理
	u32								m_lastUpdateTime;
	std::list<IUIObject*>			m_IUIObjectDeleteionList;// 针对IUIOjbect的删除缓冲队列
	std::list<scene::ISceneNode*>	m_ISceneNodeDeletionList;// 待删除列表，在每次引擎总循环的一次循环结束后会清空它。
	// 使用它可以让我们实现通过IUIAnimator来删除IUIObject
	std::list<GameScene*>			m_GameSceneDeletionList;// 延迟场景删除

public:
	static int						screen_width;	// 屏幕宽度
	static int						screen_height;	// 屏幕高度
	static IEventReceiver*			pEventReceiver;	// 消息处理者
	static bool						bFullScreen;	// 是否全屏
	//static GameScene*				currentScene;	// 当前场景

	static std::stringstream		Console_Buffer;	

private:
	// 禁止直接创建实例
	MyIrrlichtEngine();

public:

	~MyIrrlichtEngine();

	// 获取当前玩家
	boost::shared_ptr<IPlayer> GetCurrentPlayer() const
	{
		return m_currentPlayer;
	}

	// 设置当前玩家
	void SetCurrentPlayer( boost::shared_ptr<IPlayer> player )
	{
		m_currentPlayer = player;
	}

	void SetServer( boost::shared_ptr<Network::BoostServer> svr ) 
	{
		m_server = svr;
	}

	boost::shared_ptr<Network::BoostServer> GetServer() const
	{
		return m_server;
	}

	boost::shared_ptr<Network::BoostClient> GetClient() const
	{
		return m_client;
	}

	void SetClient( boost::shared_ptr<Network::BoostClient> c )
	{
		m_client = c;
	}



	// 设置当前UI管理类
	void SetUIManager( boost::shared_ptr<UIManager> mgr )
	{
		m_currentUIManager = mgr;
	}

	// 获取当前UI管理类
	boost::shared_ptr<UIManager> GetUIManager() const
	{
		return m_currentUIManager;
	}

	// 获取场景管类
	GameSceneManager* GetGameSceneManager() const
	{
		return m_gameSceneMgr;
	}

	MySceneManager* GetMySceneManager() const
	{
		return m_MySceneManager;
	}

	// 获取引擎指针
	static MyIrrlichtEngine* GetEngine();

	static void DestoryEngine();

	scene::ISceneManager* GetSceneManager();

	scene::ISceneCollisionManager* GetCollisionManager();

	video::IVideoDriver* GetVideoDriver();

	IrrlichtDevice*	GetDevice();

	ModelManager* GetModelManager();

	// 设置是否开启运动模糊
	void SetMotionBlur( bool bOpen = true );

	//AnimationManager* GetAnimationManager();	// 历史问题，动画管理交给

	void Run();

	void SetCallbackFunc( EngineRunCallbackFuncType func );

	void CloneWeapon( const Network::PACKAGE& p );

	IWeapon*	BulletFucker;
	IWeapon*	MissileFucker;

	// 添加节点到删除队列中
	void AddToDeletionQueue( scene::ISceneNode* node );
	void AddToDeletionQueue( IUIObject* node );
	void AddToDeletionQueue( GameScene* scene );

	// 删除所有删除队列中的节点，这个会在每次循环后被调用
	void ClearDeletionList();
};


#endif