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
		PIW_InBattle
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
	void AddInfo( PI_INFO info )
	{
		// �����ж��б����Ƿ��Ѿ�����������Ϣ
		for ( auto iter = InfoList.begin(); iter != InfoList.end(); ++iter )
		{
			if ( (*iter).msg == info )
				return;
		}
		// ����������
		PIItem item;
		item.msg = info;
		// ��ʼ��״̬
		item.State = 0;
		// ����ͼƬ
		auto iter = InfoMap.find( info );
		item.MsgImg = iter->second->Clone();
		item.MsgImg->drop();
		item.MsgImg->SetAlpha( 0 );
		// �����б�
		InfoList.push_back( item );
		
	
	}
	// ���뾯��
	void AddWarn( PI_INFO warn )
	{
		// �����ж��б����Ƿ��Ѿ�����������Ϣ
		for ( auto iter = WarnList.begin(); iter != WarnList.end(); ++iter )
		{
			if ( (*iter).msg == warn )
				return;
		}
		// ����������
		PIItem item;
		item.msg = warn;
		// ��ʼ��״̬
		item.State = 0;
		// ����ͼƬ
		auto iter = WarnMap.find( warn );
		item.MsgImg = iter->second->Clone();
		item.MsgImg->drop();
		item.MsgImg->SetAlpha( 0 );
		// �����б�
		WarnList.push_back( item );
	}

	// ������Ϣ�б�
	void UpdateInfo()
	{
		// ����ʱ����
		u32 timeMs = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
		if ( !InfoBox->GetAnimators().empty() )
			return;

		//��������Ϣ
		for( auto iter = InfoList.begin(); iter != InfoList.end(); ++iter )
		{
			if ( (*iter).State == 0 )
			{
				// ����ʱ��
				(*iter).CreateTime = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
				(*iter).State = 1;
				InfoCount++;
				// ����λ��
				(*iter).MsgImg->SetVisible( true );
				(*iter).MsgImg->SetPosition( vector2df( 0, NextInfoPos ) );
				// �б����ϻ���
				IUIAnimator* ani = MyIrrlichtEngine::GetEngine()->GetUIManager()->CreateAnimatorTranslation(
					0, FadeOutTime, vector2df( 0, -SlipDistance ) );
				InfoBox->AddAnimator( ani );
				ani->drop();
				// �������붯��
				ani = MyIrrlichtEngine::GetEngine()->GetUIManager()->CreateAnimatorAlphaChange(
					0, FadeOutTime, 0, 255 );
				(*iter).MsgImg->AddAnimator( ani );
				ani->drop();
				// ��һ��λ��
				NextInfoPos += SlipDistance;

				// ����б��е���Ŀ�Ѿ��������������ɾ�������
				if ( InfoCount > MaxInfoNum )
				{
					for ( auto iter2 = InfoList.begin(); iter2 != InfoList.end(); ++iter2 )
					{
						if ( (*iter2).State == 1 )
						{
							InfoCount--;
							(*iter2).State = 2;
							// ������������
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

		// ɾ����ʱ����Ϣ
		if ( !InfoList.empty() )
		{
			for( auto iter = InfoList.begin(); iter != InfoList.end(); ++iter )
			{
				if ( (*iter).State == 2 )
				{
					if ( (*iter).MsgImg->GetAnimators().empty() )
					{
						(*iter).MsgImg->SetVisible( false );
						//InfoBox->RemoveChild( (*iter).MsgImg );
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
						// ������������
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
		}
	}

	//���¾����б�
	void UpdateWarn()
	{
		// ����ʱ����
		u32 timeMs = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
		if ( !WarnBox->GetAnimators().empty() )
			return;

		//��������Ϣ
		for( auto iter = WarnList.begin(); iter != WarnList.end(); ++iter )
		{
			if ( (*iter).State == 0 )
			{
				// ����ʱ��
				(*iter).CreateTime = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
				(*iter).State = 1;
				WarnCount++;
				// ����λ��
				(*iter).MsgImg->SetVisible( true );
				(*iter).MsgImg->SetPosition( vector2df( 0, NextWarnPos ) );
				// �б����ϻ���
				IUIAnimator* ani = MyIrrlichtEngine::GetEngine()->GetUIManager()->CreateAnimatorTranslation(
					0, FadeOutTime, vector2df( 0, -SlipDistance ) );
				WarnBox->AddAnimator( ani );
				ani->drop();
				// �������붯��
				ani = MyIrrlichtEngine::GetEngine()->GetUIManager()->CreateAnimatorAlphaChange(
					0, FadeOutTime, 0, 255 );
				(*iter).MsgImg->AddAnimator( ani );
				ani->drop();
				// ��һ��λ��
				NextWarnPos += SlipDistance;

				// ����б��е���Ŀ�Ѿ��������������ɾ�������
				if ( WarnCount > MaxInfoNum )
				{
					for ( auto iter2 = WarnList.begin(); iter2 != WarnList.end(); ++iter2 )
					{
						if ( (*iter2).State == 1 )
						{
							WarnCount--;
							(*iter2).State = 2;
							// ������������
							ani = MyIrrlichtEngine::GetEngine()->GetUIManager()->CreateAnimatorAlphaChange(
								0, FadeOutTime, 255, 0 );
							(*iter2).MsgImg->AddAnimator( ani );
							ani->drop();
							break;
							//WarnList.pop_front();
						}	
					}
				}
				break;
			}
		}

		// ɾ����ʱ����Ϣ
		if ( !WarnList.empty() )
		{
			for( auto iter = WarnList.begin(); iter != WarnList.end(); ++iter )
			{
				if ( (*iter).State == 2 )
				{
					if ( (*iter).MsgImg->GetAnimators().empty() )
					{
						(*iter).MsgImg->SetVisible( false );
						//WarnBox->RemoveChild( (*iter).MsgImg );
						WarnList.pop_front();
						if ( !WarnList.empty() )
							iter = WarnList.begin();
						else
							break;
					}
				}
				else if ( (*iter).State == 1 )
				{
					if ( (*iter).State == 1 && timeMs - (*iter).CreateTime >= MaxAliveTime )
					{
						WarnCount--;
						(*iter).State = 2;
						// ������������
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
		}
	}

	void Update();

};

#endif // PlayerInfo_h__
