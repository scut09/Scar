/********************************************************************
    创建时间: 2011-11-4   20:21
    文件名:   PlayerManager.h
    作者:     华亮 屠文翔
    说明:     其他玩家信息管理

*********************************************************************/

#ifndef PlayerManager_h__
#define PlayerManager_h__

#include <irrlicht.h>
#include <hash_map>
#include <map>
#include "IUIObject.h"
#include "MyIrrlichtEngine.h"
#include "IShip.h"
#include "Toolkit.h"
#include <boost/foreach.hpp>
#include "UIManager.h"


using scene::ISceneNode;

/*
** 名字：PlayerHelper
** 说明：辅助玩家的工具，包括锁定框，提示框
**
*/
class PlayerHelper
{
public:
	Toolkit*	toolkit;	// 辅助工具
	Node2DInfo	info2D;

	IUIObject*	Cursor;		// 鼠标准心
	IUIObject*	Speed1;		// 速度槽慢
	IUIObject*	Speed2;		// 速度槽空
	IUIObject*	Shield1;	// 护盾槽满
	IUIObject*	Shield2;	// 护盾槽空
	IUIObject*	Armor1;		// 护甲槽满
	IUIObject*	Armor2;		// 护甲槽空
	IUIObject*	Gradienter;	// 水平仪
	IUIObject*	ShipTip;	// 目标圈——友军
	IUIObject*	lock1;		// 锁定框——已锁定
	IUIObject*	indicator1;	// 敌军指示

	IShip*		PlayerShip;	// 玩家自己的飞船

	IShip*		LockedShip;	// 锁定的船

	scene::ICameraSceneNode*	Camera;	// 摄像机
	video::IVideoDriver*		Driver;
	gui::ICursorControl*		CursorControl;

	UIManager*		m_uiManager;
	
	PlayerHelper( UIManager* uiManager, IShip* player_ship );

	std::map<IShip*, IUIObject*>	m_ship_targetMap;		// 船和圈住船的圆圈的映射

	// 更新框住飞船的框以提示飞船位置
	void UpdateShipTip( IShip* ship );

	void UpdateLock();

	void Update();

};

typedef std::map<int, IShip*>		PlayerMapType;


/*
** 名字：PlayerManager
** 说明：玩家管理
**
*/
class PlayerManager
{
public:

	PlayerMapType	m_playerList;		// 玩家列表

	PlayerHelper	m_playerHelper;		// 玩家辅助

	UIManager*		m_uiManager;

	
	PlayerManager( UIManager* uiManager, IShip* player_ship );

	~PlayerManager();

	// 添加玩家
	void AddPlayer( int id, IShip* player_node );

	// 移除玩家
	void RemovePlayer( int id );

	// 获取玩家列表
	const PlayerMapType& GetPlayers() const;


	void Update();

};

#endif // PlayerManager_h__