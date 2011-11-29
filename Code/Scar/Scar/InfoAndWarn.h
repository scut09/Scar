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
	enum PI_INFO
	{
		// 从B0到B8都是没有任何用处的文字信息，仅供开场时装逼用
		PII_B0,PII_B1,PII_B2,PII_B3,PII_B4,PII_B5,PII_B6,PII_B7,PII_B8,PII_B9
	};

	enum PI_WARN
	{

	};

	union PI_MSG
	{
		PI_INFO info;
		PI_WARN warn;
	};

	struct PIItem
	{
		PI_MSG msg;
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

	std::map<PI_INFO, IUIObject*> InfoMap;		// 信息映射，供复制用
	std::map<PI_WARN, IUIObject*> WarnMap;		// 警告映射，供复制用
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
	}

	// 插入信息
	void AddInfo( PI_INFO info )
	{
		// 首先判断列表中是否已经存在这条消息
		for ( auto iter = InfoList.begin(); iter != InfoList.end(); ++iter )
		{
			if ( (*iter).msg.info == info )
				return;
		}
		// 新增文字项
		PIItem item;
		item.msg.info = info;
		// 初始化状态
		item.State = 0;
		// 复制图片
		auto iter = InfoMap.find( info );
		item.MsgImg = iter->second->Clone();
		item.MsgImg->drop();
		item.MsgImg->SetAlpha( 0 );
		// 加入列表
		InfoList.push_back( item );
		
	
	}
	// 插入警告
	void AddWarn( PI_WARN warn );

	// 更新信息列表
	void UpdateInfo()
	{
		// 控制时间间隔
		u32 timeMs = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
		if ( !InfoBox->GetAnimators().empty() )
			return;
		/*if ( timeMs - LastUpdateTime < 2000 )
			return;
		LastUpdateTime = timeMs;*/

		//加入新信息
		for( auto iter = InfoList.begin(); iter != InfoList.end(); ++iter )
		{
			if ( (*iter).State == 0 )
			{
				// 创建时间
				(*iter).CreateTime = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
				(*iter).State = 1;
				InfoCount++;
				// 设置位置
				(*iter).MsgImg->SetVisible( true );
				(*iter).MsgImg->SetPosition( vector2df( 0, NextInfoPos ) );
				// 列表向上滑动
				IUIAnimator* ani = MyIrrlichtEngine::GetEngine()->GetUIManager()->CreateAnimatorTranslation(
					0, FadeOutTime, vector2df( 0, -SlipDistance ) );
				InfoBox->AddAnimator( ani );
				ani->drop();
				// 创建淡入动画
				ani = MyIrrlichtEngine::GetEngine()->GetUIManager()->CreateAnimatorAlphaChange(
					0, FadeOutTime, 0, 255 );
				(*iter).MsgImg->AddAnimator( ani );
				ani->drop();
				// 下一个位置
				NextInfoPos += SlipDistance;

				// 如果列表中的条目已经超出最大数，则删除多余的
				if ( InfoCount > MaxInfoNum )
				{
					for ( auto iter2 = InfoList.begin(); iter2 != InfoList.end(); ++iter2 )
					{
						if ( (*iter2).State == 1 )
						{
							InfoCount--;
							(*iter2).State = 2;
							// 创建淡出动画
							ani = MyIrrlichtEngine::GetEngine()->GetUIManager()->CreateAnimatorAlphaChange(
								0, FadeOutTime, 255, 0 );
							(*iter2).MsgImg->AddAnimator( ani );
							ani->drop();
							break;
							//InfoList.pop_front();
						}	
					}
				}
				break;
			}
		}

		// 删除过时的信息
		if ( !InfoList.empty() )
		{
			for( auto iter = InfoList.begin(); iter != InfoList.end(); ++iter )
			{
				if ( (*iter).State == 2 )
				{
					if ( (*iter).MsgImg->GetAnimators().empty() )
					{
						(*iter).MsgImg->SetVisible( false );
						InfoBox->RemoveChild( (*iter).MsgImg );
						InfoList.pop_front();
						if ( !InfoList.empty() )
							iter = InfoList.begin();
						else
							break;
					}
				}
				else if ( (*iter).State == 1 )
				{
					if ( (*iter).State == 1 && timeMs - (*iter).CreateTime >= MaxAliveTime )
					{
						InfoCount--;
						(*iter).State = 2;
						// 创建淡出动画
						auto ani = MyIrrlichtEngine::GetEngine()->GetUIManager()->CreateAnimatorAlphaChange(
							0, FadeOutTime, 255, 0 );
						(*iter).MsgImg->AddAnimator( ani );
						ani->drop();
					}
					break;
				}
				else
					break;
			}
			//auto item = InfoList.begin();
			//if ( (*item).State == 1 && timeMs - (*item).CreateTime >= MaxAliveTime )
			//{
			//	InfoCount--;
			//	(*item).State = 2;
			//	// 创建淡出动画
			//	auto ani = MyIrrlichtEngine::GetEngine()->GetUIManager()->CreateAnimatorAlphaChange(
			//		0, FadeOutTime, 255, 0 );
			//	(*item).MsgImg->AddAnimator( ani );
			//	ani->drop();
			//	InfoList.pop_front();
			//}
		}
	}

	//更新警告列表
	void UpdateWarn()
	{

	}

	void Update();

};

#endif // PlayerInfo_h__
