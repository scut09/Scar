/********************************************************************
    ����ʱ��: 2011-11-9   1:32
    �ļ���:   PlayerHelper.h
    ����:     ���� ������
    ˵��:     ��Ҹ�����Ϣ��ʾ���ߣ�����

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
** ���֣�PlayerHelper
** ˵����������ҵĹ��ߣ�������������ʾ��
**
*/
class PlayerHelper
{
public:
	PlayerHelper();

	// ���£�ÿ֡��Ӧ�õ����Ը�����ʾ���
	void Update();

	// װ����ҹ�����
	void LoadPlayerManager( PlayerManager* mgr )
	{
		m_playerManager = mgr;
	}

	// װ��������Ի�ȡ��ҷɴ�����Ϣ
	void LoadPlayer( boost::shared_ptr<IPlayer> player )
	{
		Player = player;
	}

	// 
	void LoadHelperUI( UIManager* uiManager );


private:
	// ���¿�ס�ɴ��Ŀ�����ʾ�ɴ�λ��
	void UpdateShipTip( IShip* ship );

	// ����������
	void UpdateLock();


private:
	boost::shared_ptr<IPlayer>		Player;		// ���

	IShip*			LockedShip;	// �����Ĵ�

	IUIObject*		Armor1;		// ���ײ���
	IUIObject*		Armor2;		// ���ײۿ�
	IUIObject*		Cursor;		// ���׼��
	IUIObject*		Gradienter;	// ˮƽ��
	IUIObject*		Shield1;	// ���ܲ���
	IUIObject*		Shield2;	// ���ܲۿ�
	IUIObject*		ShipTip;	// Ŀ��Ȧ�����Ѿ�
	IUIObject*		Speed1;		// �ٶȲ���
	IUIObject*		Speed2;		// �ٶȲۿ�
	IUIObject*		indicator1;	// �о�ָʾ
	IUIObject*		lock1;		// �����򡪡�������

	UIStaticText*	ArmorText;	// ��������
	UIStaticText*	ShieldText;	// ��������
	UIStaticText*	SpeedText;	// �ٶ�����	
	
	Node2DInfo		info2D;
	PlayerManager*	m_playerManager;	// �����Ϣ������
	boost::shared_ptr<Toolkit>	toolkit;	// �������ߣ��ṩ3D��2Dӳ��Ĺ���

	gui::ICursorControl*		CursorControl;
	scene::ICameraSceneNode*	Camera;	// �����
	video::IVideoDriver*		Driver;

	std::map<IShip*, IUIObject*>	m_ship_targetMap;		// ����Ȧס����ԲȦ��ӳ��
};

#endif // PlayerHelper_h__