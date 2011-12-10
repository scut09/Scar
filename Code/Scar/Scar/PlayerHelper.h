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
#include "InfoAndWarn.h"
#include <list>
#include "ScoreBoard.h"

using scene::ISceneNode;
struct ScoreNode
{
	unsigned int ip;
	int KillCount;
	int DeathCount;
};
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
	void LoadHelperUI( boost::shared_ptr<UIManager> uiManager );

	// ����Ļ�м���������Ϣ
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
	// ���¿�ס�ɴ��Ŀ�����ʾ�ɴ�λ��
	void UpdateShipTip( IShip* ship );

	// ����������
	void UpdateLock();

	// �����״�
	void UpdateRadar();

	// �����˺���ʾ
	void UpdateHarmAlert();


private:
	boost::shared_ptr<IPlayer>		Player;		// ���

	IShip*			LockedShip;	// �����Ĵ�

public:
	IUIObject*		Armor1;		// ���ײ���
	IUIObject*		Armor2;		// ���ײۿ�
	IUIObject*		Cursor;		// ���׼��
	IUIObject*		Gradienter;	// ˮƽ��
	IUIObject*		Shield1;	// ���ܲ���
	IUIObject*		Shield2;	// ���ܲۿ�
	IUIObject*		ShipTipE;	// Ŀ��Ȧ�����о�
	IUIObject*		ShipTipF;	// Ŀ��Ȧ�����Ѿ�
	IUIObject*		Speed1;		// �ٶȲ���
	IUIObject*		Speed2;		// �ٶȲۿ�
	IUIObject*		Energy1;	// ��������
	IUIObject*		Energy2;	// �����ۿ�
	IUIObject*		indicator1;	// �о�ָʾ
	IUIObject*		lock1;		// �����򡪡�������
	IUIObject*		Radar;		// �״�Ȧ
	IUIObject*		REnemy;		// �״�Ȧ�ϵĵ���
	IUIObject*		RFriend;	// �״�Ȧ�ϵ��Ѿ�
	IUIObject*		RedMask;	// ��Ļ��ɫ����

	ISceneNode*		Horizon;	// ˮƽ���
	ISceneNode*		Vertical;	// ��ֱ���

	UIStaticText*	ArmorText;	// ��������
	UIStaticText*	ShieldText;	// ��������
	UIStaticText*	SpeedText;	// �ٶ�����	
	UIStaticText*	EnergyText;	// ��������
	UIStaticText*	TargetShield;
	UIStaticText*	TargetArmor;
	UIStaticText*	TargetDistance;

private:
	Node2DInfo		info2D;
	PlayerManager*	m_playerManager;	// �����Ϣ������
	boost::shared_ptr<Toolkit>	toolkit;	// �������ߣ��ṩ3D��2Dӳ��Ĺ���

	gui::ICursorControl*		CursorControl;
	scene::ICameraSceneNode*	Camera;	// �����
	video::IVideoDriver*		Driver;

	std::map<IShip*, IUIObject*>	m_ship_targetMap;		// ����Ȧס����ԲȦ��ӳ��
	std::map<IShip*, IUIObject*>	m_ship_radarMap;		// �����״��ϵı�ǵ�ӳ��

	InfoAndWarn						m_infoAndWarn;			// ������Ϣ������

	f32								LastArmor, LastShield;	// ��һ�ε�Ѫ��

	std::map<u32, ScoreNode>		m_ScoreList;	// �Ʒְ�
	ScoreBoard*						scBoard;
	
};

#endif // PlayerHelper_h__