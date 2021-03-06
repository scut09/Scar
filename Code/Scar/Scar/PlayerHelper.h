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
#include "InfoAndWarn.h"
#include <list>
#include "ScoreBoard.h"

using scene::ISceneNode;
struct ScoreNode
{
	unsigned int ip;
	int KillCount;
	int DeathCount;
	int Team;

	bool operator<( const ScoreNode& node )const
	{
		return ip < node.ip;
	}
};
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

	void Revive();

	// 
	void LoadHelperUI( boost::shared_ptr<UIManager> uiManager );

	// 向屏幕中加入文字信息
	void AddInfoMsg( InfoAndWarn::PI_INFO info )
	{
		m_infoAndWarn.AddInfo( info );
	}

	void SetLockedShip ( IShip* lockership )
	{
		LockedShip = lockership;
	}

	void AddWarnMsg( InfoAndWarn::PI_INFO warn )
	{
		m_infoAndWarn.AddWarn( warn );
	}

	void SetPlayerScore( u32 ip, const ScoreNode& score )
	{
		m_ScoreList[ ip ] = score;
	}

	bool IsScoreBoardVisible;
	void ShowScoreBoard()
	{
		scBoard->Show();
		IsScoreBoardVisible = true;
	}
	void HideScoreBoard()
	{
		scBoard->Hide();
		IsScoreBoardVisible = false;
	}


private:
	// 更新框住飞船的框以提示飞船位置
	void UpdateShipTip( IShip* ship );

	// 更新锁定框
	void UpdateLock();

	// 更新雷达
	void UpdateRadar();

	// 更新伤害提示
	void UpdateHarmAlert();


private:
	boost::shared_ptr<IPlayer>		Player;		// 玩家

	IShip*			LockedShip;	// 锁定的船

public:
	IUIObject*		Armor1;		// 护甲槽满
	IUIObject*		Armor2;		// 护甲槽空
	IUIObject*		Cursor;		// 鼠标准心
	IUIObject*		Gradienter;	// 水平仪
	IUIObject*		Shield1;	// 护盾槽满
	IUIObject*		Shield2;	// 护盾槽空
	IUIObject*		ShipTipE;	// 目标圈——敌军
	IUIObject*		ShipTipF;	// 目标圈——友军
	IUIObject*		Speed1;		// 速度槽慢
	IUIObject*		Speed2;		// 速度槽空
	IUIObject*		Energy1;	// 能量槽满
	IUIObject*		Energy2;	// 能量槽空
	IUIObject*		indicator1;	// 敌军指示
	IUIObject*		lock1;		// 锁定框——已锁定
	IUIObject*		Radar;		// 雷达圈
	IUIObject*		REnemy;		// 雷达圈上的敌人
	IUIObject*		RFriend;	// 雷达圈上的友军
	IUIObject*		RedMask;	// 屏幕红色遮罩
	IUIObject*		ReConStr;	// 倒计时剩下5s
	IUIObject*		Num1;		// 倒计时剩下1s
	IUIObject*		Num2;		// 倒计时剩下2s
	IUIObject*		Num3;		// 倒计时剩下3s
	IUIObject*		Num4;		// 倒计时剩下4s
	IUIObject*		Num5;		// 倒计时剩下5s

	ISceneNode*		Horizon;	// 水平标尺
	ISceneNode*		Vertical;	// 垂直标尺

	UIStaticText*	ArmorText;	// 护甲文字
	UIStaticText*	ShieldText;	// 护盾文字
	UIStaticText*	SpeedText;	// 速度文字	
	UIStaticText*	EnergyText;	// 能量文字
	UIStaticText*	TargetShield;
	UIStaticText*	TargetArmor;
	UIStaticText*	TargetDistance;

private:
	Node2DInfo		info2D;
	PlayerManager*	m_playerManager;	// 玩家信息管理类
	boost::shared_ptr<Toolkit>	toolkit;	// 辅助工具，提供3D到2D映射的工具

	gui::ICursorControl*		CursorControl;
	scene::ICameraSceneNode*	Camera;	// 摄像机
	video::IVideoDriver*		Driver;

	std::map<IShip*, IUIObject*>	m_ship_targetMap;		// 船和圈住船的圆圈的映射
	std::map<IShip*, IUIObject*>	m_ship_radarMap;		// 船和雷达上的标记的映射

	InfoAndWarn						m_infoAndWarn;			// 文字信息管理类

	f32								LastArmor, LastShield;	// 上一次的血量

	std::map<u32, ScoreNode>		m_ScoreList;	// 计分榜
	ScoreBoard*						scBoard;
	u32								m_DieTimePoint;
	bool							IsJustDie;
	
};

#endif // PlayerHelper_h__