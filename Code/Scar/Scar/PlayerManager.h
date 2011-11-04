/********************************************************************
    ����ʱ��: 2011-11-4   20:21
    �ļ���:   PlayerManager.h
    ����:     ���� ������
    ˵��:     ���������Ϣ����

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
** ���֣�PlayerHelper
** ˵����������ҵĹ��ߣ�������������ʾ��
**
*/
class PlayerHelper
{
public:
	Toolkit*	toolkit;	// ��������
	Node2DInfo	info2D;

	IUIObject*	Cursor;		// ���׼��
	IUIObject*	Speed1;		// �ٶȲ���
	IUIObject*	Speed2;		// �ٶȲۿ�
	IUIObject*	Shield1;	// ���ܲ���
	IUIObject*	Shield2;	// ���ܲۿ�
	IUIObject*	Armor1;		// ���ײ���
	IUIObject*	Armor2;		// ���ײۿ�
	IUIObject*	Gradienter;	// ˮƽ��
	IUIObject*	ShipTip;	// Ŀ��Ȧ�����Ѿ�
	IUIObject*	lock1;		// �����򡪡�������
	IUIObject*	indicator1;	// �о�ָʾ

	IShip*		playerShip;	// ����Լ��ķɴ�

	scene::ICameraSceneNode*	Camera;	// �����
	video::IVideoDriver*		Driver;
	gui::ICursorControl*		CursorControl;
	
	PlayerHelper()
	{
		Camera = MyIrrlichtEngine::GetEngine()->GetSceneManager()->getActiveCamera();
		Driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
		CursorControl = MyIrrlichtEngine::GetEngine()->GetDevice()->getCursorControl();

		toolkit = new Toolkit( Camera, Driver );
	}

	std::map<IShip*, IUIObject*>	m_ship_targetMap;		// ����Ȧס����ԲȦ��ӳ��

	// ���¿�ס�ɴ��Ŀ�����ʾ�ɴ�λ��
	void UpdateShipTip( IShip* ship )
	{
		// ������ȦȦȦסĿ��
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
				// ��δ������ʾ����ô�ʹ���һ���µ�
				shipTip = ShipTip->Clone();

				m_ship_targetMap[ ship ] = shipTip;
			}
			else	
			{
				shipTip = iter->second;
			}

			shipTip->SetVisible( true );				// ��ʾ�ɴ���ʾ
			shipTip->SetPosition( info2D.pos );
			shipTip->SetScale( vector2df(sca) );
		}
		
	}

	void Update()
	{
		// ׼��׷�����
		auto CursorPos = CursorControl->getPosition();
		Cursor->SetPosition( vector2df( (f32)CursorPos.X, (f32)CursorPos.Y ) );

		f32 ratio;
		f32 border;
		// �����ٶȲ�
		ratio = playerShip->GetVelocity() / playerShip->GetMaxSpeed();
		border = 389 * ( 1 - ratio );
		Speed1->SetSourceRect( vector2df( 0, border ), vector2df( 98, 389 ) );
		Speed2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 98, border ) );	
		// ���ƻ��ܲ�
		ratio = playerShip->GetShield() / playerShip->GetMaxShield();
		border = 389 * ( 1 - ratio );
		Shield1->SetSourceRect( vector2df( 0, border ), vector2df( 100, 389 ) );
		Shield2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 100, border ) );
		// ���ƻ��ײ�
		ratio = playerShip->GetArmor() / playerShip->GetMaxArmor();
		border = 360 * ( 1 - ratio );
		Armor1->SetSourceRect( vector2df( 0, border ), vector2df( 93, 360 ) );
		Armor2->SetSourceRect( vector2df( 0, 0 ) , vector2df( 93, border ) );

		// ˮƽ��ת��
		core::vector3df vec( 0, 1, 0 );
		f32 rott = (f32)acos( ( Camera->getUpVector().dotProduct( vector3df( 0, 1, 0 ) ) ) / Camera->getUpVector().getLength() ) * RADTODEG;
		Gradienter->SetRotation( rott );

		
	}

};

/*
** ���֣�PlayerManager
** ˵������ҹ���
**
*/
class PlayerManager
{
public:
	typedef std::map<int, IShip*>		PlayerMapType;

	PlayerMapType	m_playerList;		// ����б�

	PlayerHelper	m_playerHelper;		// ��Ҹ���

	// ������
	void AddPlayer( int id, IShip* player_node )
	{
		m_playerList[ id ] = player_node;
	}

	// �Ƴ����
	void RemovePlayer( int id )
	{
		m_playerList.erase( id );
	}

	// ��ȡ����б�
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