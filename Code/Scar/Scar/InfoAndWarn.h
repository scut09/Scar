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
	struct PIItem
	{
		u32 CreateTime;
		IUIObject* MsgImg;
	};

	enum PI_INFO
	{
		// 从B0到B8都是没有任何用处的文字信息，仅供开场时装逼用
		PII_B0,PII_B1,PII_B2,PII_B3,PII_B4,PII_B5,PII_B6,PII_B7,PII_B8
	};

	enum PI_WARN
	{

	};

private:
	u32 FadeOutTime;							// 淡出，淡入，滑动时间
	u32 MaxAliveTime;							// 信息最大停留时间
	s32 MaxInfoNum;								// 最大信息数目
	f32 SlipDistance;							// 文字滑动距离
	f32 Height;
	f32 Width;

	std::map<PI_INFO, IUIObject*> InfoMap;		// 信息映射，供复制用
	std::map<PI_WARN, IUIObject*> WarnMap;		// 警告映射，供复制用
	IUIObject* InfoBox;							// 信息的容器
	IUIObject* WarnBox;							// 警告的容器
	std::list<PIItem> InfoList;					// 信息列表
	std::list<PIItem> WarnList;					// 警告列表
	

public:
	InfoAndWarn()
	{
		FadeOutTime = 1000;
		MaxAliveTime = 60000;
		MaxInfoNum = 6;
		SlipDistance = 32;
		Height = 500;
		Width = 250;
	}

	// 初始化
	void Initialize()
	{
		boost::shared_ptr<UIManager> uiMgr = MyIrrlichtEngine::GetEngine()->GetUIManager();
		//这两个容器仅有位置概念
		InfoBox = uiMgr->AddUIImage( 0, 0, 0 );
		InfoBox->SetPosition( vector2df( Height, -Width ) );
		WarnBox = uiMgr->AddUIImage( 0, 0, 0 );
		WarnBox->SetPosition( vector2df( Height, Width ) );

		IUIObject* t;
		s32 MSGH = 32;
		s32 MSGW = 177;

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
	}

	// 插入信息
	void AddInfo( PI_INFO info )
	{
		// 新增文字项
		PIItem item;
		// 创建时间
		item.CreateTime = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
		// 复制图片
		auto iter = InfoMap.find( info );
		item.MsgImg = iter->second->Clone();
		item.MsgImg->SetVisible( true );
		item.MsgImg->SetAlpha( 0 );
		item.MsgImg->SetPosition( vector2df( 0, Height - InfoBox->GetPosition().Y ) );
		InfoBox->AddChild( item.MsgImg );
		// 列表向上滑动
		IUIAnimator* ani = MyIrrlichtEngine::GetEngine()->GetUIManager()->CreateAnimatorTranslation(
			0, FadeOutTime, vector2df( 0, SlipDistance ) );
		InfoBox->AddAnimator( ani );
		ani->drop();
		// 创建淡入动画
		ani = MyIrrlichtEngine::GetEngine()->GetUIManager()->CreateAnimatorAlphaChange(
			0, FadeOutTime, 0, 255 );
		item.MsgImg->AddAnimator( ani );
		ani->drop();
	
	}
	// 插入警告
	void AddWarn( PI_WARN warn );

};

#endif // PlayerInfo_h__
