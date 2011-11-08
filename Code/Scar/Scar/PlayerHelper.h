/********************************************************************
    创建时间: 2011-11-9   1:32
    文件名:   PlayerHelper.h
    作者:     华亮 屠文翔
    说明:     玩家辅助信息提示工具，例如

*********************************************************************/

#ifndef PlayerHelper_h__
#define PlayerHelper_h__

#include "PlayerManager.h"
#include "UIManager.h"
#include "AllUIObjects.h"
#include "Toolkit.h"
#include <map>

using scene::ISceneNode;

/*
** 名字：PlayerHelper
** 说明：辅助玩家的工具，包括锁定框，提示框
**
*/
class PlayerHelper
{
public:
	PlayerHelper();

	// 更新，每帧都应该调用以更新显示面板
	void Update();

	// 装载玩家管理类
	void LoadPlayerManager( PlayerManager* mgr )
	{
		m_playerManager = mgr;
	}

	// 装载玩家类以获取玩家飞船的信息
	void LoadPlayer( boost::shared_ptr<IPlayer> player )
	{
		Player = player;
	}

	// 
	void LoadHelperUI( UIManager* uiManager );


private:
	// 更新框住飞船的框以提示飞船位置
	void UpdateShipTip( IShip* ship );

	// 更新锁定框
	void UpdateLock();


private:
	boost::shared_ptr<IPlayer>		Player;		// 玩家

	IShip*			LockedShip;	// 锁定的船

	IUIObject*		Armor1;		// 护甲槽满
	IUIObject*		Armor2;		// 护甲槽空
	IUIObject*		Cursor;		// 鼠标准心
	IUIObject*		Gradienter;	// 水平仪
	IUIObject*		Shield1;	// 护盾槽满
	IUIObject*		Shield2;	// 护盾槽空
	IUIObject*		ShipTip;	// 目标圈——友军
	IUIObject*		Speed1;		// 速度槽慢
	IUIObject*		Speed2;		// 速度槽空
	IUIObject*		indicator1;	// 敌军指示
	IUIObject*		lock1;		// 锁定框——已锁定

	UIStaticText*	ArmorText;	// 护甲文字
	UIStaticText*	ShieldText;	// 护盾文字
	UIStaticText*	SpeedText;	// 速度文字	
	
	Node2DInfo		info2D;
	PlayerManager*	m_playerManager;	// 玩家信息管理类
	boost::shared_ptr<Toolkit>	toolkit;	// 辅助工具，提供3D到2D映射的工具

	gui::ICursorControl*		CursorControl;
	scene::ICameraSceneNode*	Camera;	// 摄像机
	video::IVideoDriver*		Driver;

	std::map<IShip*, IUIObject*>	m_ship_targetMap;		// 船和圈住船的圆圈的映射
};

#endif // PlayerHelper_h__