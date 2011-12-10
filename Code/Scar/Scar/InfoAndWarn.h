#ifndef PlayerInfo_h__
#define PlayerInfo_h__

/********************************************************************
	创建时间:	2011/11/28
	文件名称: 	InfoAndWarn
	作者:		屠文翔 - Kid
	
	描述:		管理屏幕上的信息文字
				自动显示，淡入淡出，消失
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
		// 从B0到B8都是没有任何用处的文字信息，仅供开场时装逼用
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
		s32 State;	// 0等待被创建 1已创建 2等待被销毁
	};

private:
	u32 FadeOutTime;							// 淡出，淡入，滑动时间
	u32 MaxAliveTime;							// 信息最大停留时间
	u32 LastUpdateTime;							// 上次更新时间
	s32 MaxInfoNum;								// 最大信息数目
	f32 SlipDistance;							// 文字滑动距离
	f32 NextInfoPos;							// 下一条信息的摆放位置
	f32 NextWarnPos;							// 下一条警告的摆放位置
	f32 Height;
	f32 Width;

	
	std::map<PI_INFO, IUIObject*> WarnMap;		// 警告映射，供复制用
	std::map<PI_INFO, IUIObject*> InfoMap;		// 信息映射，供复制用
	IUIObject* InfoBox;							// 信息的容器
	IUIObject* WarnBox;							// 警告的容器
	std::list<PIItem> InfoList;					// 信息列表
	std::list<PIItem> WarnList;					// 警告列表
	s32 InfoCount, WarnCount;					// 列表中当前数量
	

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

	// 初始化
	void Initialize()
	{
		boost::shared_ptr<UIManager> uiMgr = MyIrrlichtEngine::GetEngine()->GetUIManager();
		//这两个容器仅有位置概念
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

		// 警告
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


		// 信息
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

	// 插入信息
	void AddInfo( PI_INFO info );
	// 插入警告
	void AddWarn( PI_INFO warn );

	// 更新信息列表
	void UpdateInfo();

	//更新警告列表
	void UpdateWarn();

	void Update();

};

#endif // PlayerInfo_h__
