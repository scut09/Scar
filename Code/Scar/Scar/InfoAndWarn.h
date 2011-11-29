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
	enum PI_INFO
	{
		// ��B0��B8����û���κ��ô���������Ϣ����������ʱװ����
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

	std::map<PI_INFO, IUIObject*> InfoMap;		// ��Ϣӳ�䣬��������
	std::map<PI_WARN, IUIObject*> WarnMap;		// ����ӳ�䣬��������
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

	// ������Ϣ
	void AddInfo( PI_INFO info )
	{
		// �����ж��б����Ƿ��Ѿ�����������Ϣ
		for ( auto iter = InfoList.begin(); iter != InfoList.end(); ++iter )
		{
			if ( (*iter).msg.info == info )
				return;
		}
		// ����������
		PIItem item;
		item.msg.info = info;
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
	void AddWarn( PI_WARN warn );

	// ������Ϣ�б�
	void UpdateInfo()
	{
		// ����ʱ����
		u32 timeMs = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
		if ( !InfoBox->GetAnimators().empty() )
			return;
		/*if ( timeMs - LastUpdateTime < 2000 )
			return;
		LastUpdateTime = timeMs;*/

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
			//auto item = InfoList.begin();
			//if ( (*item).State == 1 && timeMs - (*item).CreateTime >= MaxAliveTime )
			//{
			//	InfoCount--;
			//	(*item).State = 2;
			//	// ������������
			//	auto ani = MyIrrlichtEngine::GetEngine()->GetUIManager()->CreateAnimatorAlphaChange(
			//		0, FadeOutTime, 255, 0 );
			//	(*item).MsgImg->AddAnimator( ani );
			//	ani->drop();
			//	InfoList.pop_front();
			//}
		}
	}

	//���¾����б�
	void UpdateWarn()
	{

	}

	void Update();

};

#endif // PlayerInfo_h__
