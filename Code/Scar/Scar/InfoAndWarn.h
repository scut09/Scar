#ifndef PlayerInfo_h__
#define PlayerInfo_h__

/********************************************************************
	����ʱ��:	2011/11/28
	�ļ�����: 	InfoAndWarn
	����:		������ - Kid
	
	����:		������Ļ�ϵ���Ϣ����
				�Զ���ʾ�����뵭������ʧ
*********************************************************************/

#include "irrlicht.h"
#include <stdlib.h>
#include "MyIrrlichtEngine.h"
using namespace irr;
#undef LoadImage

class InfoAndWarn
{

public:	

	/*enum PI_INFO
	{
	PIW_PlayerLock,
	PIW_PlayerUnlock,
	PIW_MissleComing
	};*/

	enum PI_INFO
	{
		// ��B0��B8����û���κ��ô���������Ϣ����������ʱװ����
		PII_B0,PII_B1,PII_B2,PII_B3,PII_B4,PII_B5,PII_B6,PII_B7,PII_B8,PII_B9,
		PII_Lock,
		PII_Unlock,
		PII_QuitWarp,
		PIW_PlayerLock,
		PIW_PlayerUnlock,
		PIW_MissleComing,
		PIW_InBattle,
		PIW_LowShield,
		PIW_LowArmor,
		PIW_CrashWarn
	};

	struct PIItem
	{
		PI_INFO msg;
		u32 CreateTime;
		IUIObject* MsgImg;
		s32 State;	// 0�ȴ������� 1�Ѵ��� 2�ȴ�������
	};

private:
	u32 FadeOutTime;							// ���������룬����ʱ��
	u32 MaxAliveTime;							// ��Ϣ���ͣ��ʱ��
	u32 LastUpdateTime;							// �ϴθ���ʱ��
	s32 MaxInfoNum;								// �����Ϣ��Ŀ
	f32 SlipDistance;							// ���ֻ�������
	f32 NextInfoPos;							// ��һ����Ϣ�İڷ�λ��
	f32 NextWarnPos;							// ��һ������İڷ�λ��
	f32 Height;
	f32 Width;

	
	std::map<PI_INFO, IUIObject*> WarnMap;		// ����ӳ�䣬��������
	std::map<PI_INFO, IUIObject*> InfoMap;		// ��Ϣӳ�䣬��������
	IUIObject* InfoBox;							// ��Ϣ������
	IUIObject* WarnBox;							// ���������
	std::list<PIItem> InfoList;					// ��Ϣ�б�
	std::list<PIItem> WarnList;					// �����б�
	s32 InfoCount, WarnCount;					// �б��е�ǰ����
	

public:
	InfoAndWarn()
	{
		FadeOutTime = 600;
		MaxAliveTime = 5000;
		LastUpdateTime = 0;
		MaxInfoNum = 5;
		SlipDistance = 28;
		//Height = -80;
		Width = 300;
		NextInfoPos = NextWarnPos = 0;
		InfoCount = WarnCount = 0;

		Initialize();
	}

	// ��ʼ��
	void Initialize()
	{
		boost::shared_ptr<UIManager> uiMgr = MyIrrlichtEngine::GetEngine()->GetUIManager();
		//��������������λ�ø���
		f32 cenPosY = (f32)MyIrrlichtEngine::GetEngine()->GetVideoDriver()->getScreenSize().Height / 2.0f;
		f32 cenPosX = (f32)MyIrrlichtEngine::GetEngine()->GetVideoDriver()->getScreenSize().Width / 2.0f;
		f32 offsetY = ( MaxInfoNum * SlipDistance ) / 2.0f;
		InfoBox = uiMgr->AddUIImage( 0, 0, 0 );
		InfoBox->SetPosition( vector2df( cenPosX - Width, cenPosY + offsetY ) );
		WarnBox = uiMgr->AddUIImage( 0, 0, 0 );
		WarnBox->SetPosition( vector2df( cenPosX + Width, cenPosY + offsetY ) );

		IUIObject* t;
		s32 MSGH = 28;
		s32 MSGW = 159;

		// ����
		t = uiMgr->AddUIImage( WarnBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/playerlock.png" );
		t->SetVisible( false );
		WarnMap[PIW_PlayerLock] = t;
		t = uiMgr->AddUIImage( WarnBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/playerunlock.png" );
		t->SetVisible( false );
		WarnMap[PIW_PlayerUnlock] = t;
		t = uiMgr->AddUIImage( WarnBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/misslecoming.png" );
		t->SetVisible( false );
		WarnMap[PIW_MissleComing] = t;
		t = uiMgr->AddUIImage( WarnBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/inbattle.png" );
		t->SetVisible( false );
		WarnMap[PIW_InBattle] = t;
		t = uiMgr->AddUIImage( WarnBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/lowarmor.png" );
		t->SetVisible( false );
		WarnMap[PIW_LowArmor] = t;
		t = uiMgr->AddUIImage( WarnBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/lowshield.png" );
		t->SetVisible( false );
		WarnMap[PIW_LowShield] = t;
		t = uiMgr->AddUIImage( WarnBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/crashwarn.png" );
		t->SetVisible( false );
		WarnMap[PIW_CrashWarn] = t;


		// ��Ϣ
		t = uiMgr->AddUIImage( InfoBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/0.png" );
		t->SetVisible( false );
		InfoMap[PII_B0] = t;
		t = uiMgr->AddUIImage( InfoBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/1.png" );
		t->SetVisible( false );
		InfoMap[PII_B1] = t;
		t = uiMgr->AddUIImage( InfoBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/2.png" );
		t->SetVisible( false );
		InfoMap[PII_B2] = t;
		t = uiMgr->AddUIImage( InfoBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/3.png" );
		t->SetVisible( false );
		InfoMap[PII_B3] = t;
		t = uiMgr->AddUIImage( InfoBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/4.png" );
		t->SetVisible( false );
		InfoMap[PII_B4] = t;
		t = uiMgr->AddUIImage( InfoBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/5.png" );
		t->SetVisible( false );
		InfoMap[PII_B5] = t;
		t = uiMgr->AddUIImage( InfoBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/6.png" );
		t->SetVisible( false );
		InfoMap[PII_B6] = t;
		t = uiMgr->AddUIImage( InfoBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/7.png" );
		t->SetVisible( false );
		InfoMap[PII_B7] = t;
		t = uiMgr->AddUIImage( InfoBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/8.png" );
		t->SetVisible( false );
		InfoMap[PII_B8] = t;
		t = uiMgr->AddUIImage( InfoBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/9.png" );
		t->SetVisible( false );
		InfoMap[PII_B9] = t;
		t = uiMgr->AddUIImage( InfoBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/lock.png" );
		t->SetVisible( false );
		InfoMap[PII_Lock] = t;
		t = uiMgr->AddUIImage( InfoBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/unlock.png" );
		t->SetVisible( false );
		InfoMap[PII_Unlock] = t;
		t = uiMgr->AddUIImage( InfoBox, MSGW, MSGH );
		t->LoadImage( "../media/Message/quitwarp.png" );
		t->SetVisible( false );
		InfoMap[PII_QuitWarp] = t;
	}

	// ������Ϣ
	void AddInfo( PI_INFO info );
	// ���뾯��
	void AddWarn( PI_INFO warn );

	// ������Ϣ�б�
	void UpdateInfo();

	//���¾����б�
	void UpdateWarn();

	void Update();

};

#endif // PlayerInfo_h__
