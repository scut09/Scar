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
#include "UIManager.h"
#include <vector>
#include "AllUIObjects.h"

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

	IUIObject*		Cursor;		// ���׼��
	IUIObject*		Speed1;		// �ٶȲ���
	IUIObject*		Speed2;		// �ٶȲۿ�
	UIStaticText*	SpeedText;	// �ٶ�����
	IUIObject*		Shield1;	// ���ܲ���
	IUIObject*		Shield2;	// ���ܲۿ�
	UIStaticText*	ShieldText;	// ��������
	IUIObject*		Armor1;		// ���ײ���
	IUIObject*		Armor2;		// ���ײۿ�
	UIStaticText*	ArmorText;	// ��������
	IUIObject*		Gradienter;	// ˮƽ��
	IUIObject*		ShipTip;	// Ŀ��Ȧ�����Ѿ�
	IUIObject*		lock1;		// �����򡪡�������
	IUIObject*		indicator1;	// �о�ָʾ

	IShip*		PlayerShip;	// ����Լ��ķɴ�

	IShip*		LockedShip;	// �����Ĵ�

	scene::ICameraSceneNode*	Camera;	// �����
	video::IVideoDriver*		Driver;
	gui::ICursorControl*		CursorControl;

	UIManager*		m_uiManager;
	
	PlayerHelper( UIManager* uiManager, IShip* player_ship );

	std::map<IShip*, IUIObject*>	m_ship_targetMap;		// ����Ȧס����ԲȦ��ӳ��

	// ���¿�ס�ɴ��Ŀ�����ʾ�ɴ�λ��
	void UpdateShipTip( IShip* ship );

	void UpdateLock();

	void Update();

};

typedef std::map<int, IShip*>		PlayerMapType;


/*
** ���֣�PlayerManager
** ˵������ҹ���
**
*/
class PlayerManager
{
public:

	PlayerMapType	m_playerList;		// ����б�

	PlayerHelper	m_playerHelper;		// ��Ҹ���

	UIManager*		m_uiManager;

	std::vector<IShip*> m_players;
	
	PlayerManager( UIManager* uiManager, IShip* player_ship );

	~PlayerManager();

	// ������
	void AddPlayer( int id, IShip* player_node );

	// �Ƴ����
	void RemovePlayer( int id );

	// ��ȡ����б�
	const std::vector<IShip*>& GetPlayers() const;

	void Update();

	//void SetLockShip( )

};

#endif // PlayerManager_h__