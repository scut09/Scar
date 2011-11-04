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

	IShip*		playerShip;	// 玩家自己的飞船

	scene::ICameraSceneNode*	Camera;	// 摄像机
	video::IVideoDriver*		Driver;
	gui::ICursorControl*		CursorControl;
	
	PlayerHelper()
	{
		Camera = MyIrrlichtEngine::GetEngine()->GetSceneManager()->getActiveCamera();
		Driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
		CursorControl = MyIrrlichtEngine::GetEngine()->GetDevice()->getCursorControl();

		toolkit = new Toolkit( Camera, Driver );
	}

	std::map<IShip*, IUIObject*>	m_ship_targetMap;		// 船和圈住船的圆圈的映射

	// 更新框住飞船的框以提示飞船位置
	void UpdateShipTip( IShip* ship )
	{
		// 测试用圈圈圈住目标
		if ( toolkit->GetNode2DInfo( ship, &info2D ) )
		{
			f32 sca = info2D.height / 60.0f;
			if ( sca > 1.2f )
				sca = 1.2f;
			else if ( sca < 0.5f )
				sca = 0.5f;

			IUIObject* shipTip;
			auto iter = m_ship_targetMap.find( ship );
			if ( iter == m_ship_targetMap.end() )
			{
				// 还未创建提示框，那么就创建一个新的
				shipTip = ShipTip->Clone();

				m_ship_targetMap[ ship ] = shipTip;
			}
			else	
			{
				shipTip = iter->second;
			}

			shipTip->SetVisible( true );				// 显示飞船提示
			shipTip->SetPosition( info2D.pos );
			shipTip->SetScale( vector2df(sca) );
		}
		
	}

	void Update()
	{
		// 准心追随鼠标
		auto CursorPos = CursorControl->getPosition();
		Cursor->SetPosition( vector2df( (f32)CursorPos.X, (f32)CursorPos.Y ) );

		f32 ratio;
		f32 border;
		// 绘制速度槽
		ratio = playerShip->GetVelocity() / playerShip->GetMaxSpeed();
		border = 389 * ( 1 - ratio );
		Speed1->SetSourceRect( vector2df( 0, border ), vector2df( 98, 389 ) );
		Speed2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 98, border ) );	
		// 绘制护盾槽
		ratio = playerShip->GetShield() / playerShip->GetMaxShield();
		border = 389 * ( 1 - ratio );
		Shield1->SetSourceRect( vector2df( 0, border ), vector2df( 100, 389 ) );
		Shield2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 100, border ) );
		// 绘制护甲槽
		ratio = playerShip->GetArmor() / playerShip->GetMaxArmor();
		border = 360 * ( 1 - ratio );
		Armor1->SetSourceRect( vector2df( 0, border ), vector2df( 93, 360 ) );
		Armor2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 93, border ) );

		// 水平仪转动
		core::vector3df vec( 0, 1, 0 );
		f32 rott = (f32)acos( ( Camera->getUpVector().dotProduct( vector3df( 0, 1, 0 ) ) ) / Camera->getUpVector().getLength() ) * RADTODEG;
		Gradienter->SetRotation( rott );

		
	}

};

/*
** 名字：PlayerManager
** 说明：玩家管理
**
*/
class PlayerManager
{
public:
	typedef std::map<int, IShip*>		PlayerMapType;

	PlayerMapType	m_playerList;		// 玩家列表

	PlayerHelper	m_playerHelper;		// 玩家辅助

	// 添加玩家
	void AddPlayer( int id, IShip* player_node )
	{
		m_playerList[ id ] = player_node;
	}

	// 移除玩家
	void RemovePlayer( int id )
	{
		m_playerList.erase( id );
	}

	// 获取玩家列表
	const PlayerMapType& GetPlayers() const
	{
		return m_playerList;
	}


	void Update()
	{
		m_playerHelper.Update();

		for ( PlayerMapType::iterator iter = m_playerList.begin(); iter != m_playerList.end(); ++iter )
		{
			m_playerHelper.UpdateShipTip( iter->second );
		}
	}

};

#endif // PlayerManager_h__