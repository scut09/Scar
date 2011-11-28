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
	struct PIItem
	{
		u32 CreateTime;
		IUIObject* MsgImg;
	};

	enum PI_INFO
	{
		// ��B0��B8����û���κ��ô���������Ϣ����������ʱװ����
		PII_B0,PII_B1,PII_B2,PII_B3,PII_B4,PII_B5,PII_B6,PII_B7,PII_B8
	};

	enum PI_WARN
	{

	};

private:
	u32 FadeOutTime;							// ���������룬����ʱ��
	u32 MaxAliveTime;							// ��Ϣ���ͣ��ʱ��
	s32 MaxInfoNum;								// �����Ϣ��Ŀ
	f32 SlipDistance;							// ���ֻ�������
	f32 Height;
	f32 Width;

	std::map<PI_INFO, IUIObject*> InfoMap;		// ��Ϣӳ�䣬��������
	std::map<PI_WARN, IUIObject*> WarnMap;		// ����ӳ�䣬��������
	IUIObject* InfoBox;							// ��Ϣ������
	IUIObject* WarnBox;							// ���������
	std::list<PIItem> InfoList;					// ��Ϣ�б�
	std::list<PIItem> WarnList;					// �����б�
	

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

	// ��ʼ��
	void Initialize()
	{
		boost::shared_ptr<UIManager> uiMgr = MyIrrlichtEngine::GetEngine()->GetUIManager();
		//��������������λ�ø���
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

	// ������Ϣ
	void AddInfo( PI_INFO info )
	{
		// ����������
		PIItem item;
		// ����ʱ��
		item.CreateTime = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
		// ����ͼƬ
		auto iter = InfoMap.find( info );
		item.MsgImg = iter->second->Clone();
		item.MsgImg->SetVisible( true );
		item.MsgImg->SetAlpha( 0 );
		item.MsgImg->SetPosition( vector2df( 0, Height - InfoBox->GetPosition().Y ) );
		InfoBox->AddChild( item.MsgImg );
		// �б����ϻ���
		IUIAnimator* ani = MyIrrlichtEngine::GetEngine()->GetUIManager()->CreateAnimatorTranslation(
			0, FadeOutTime, vector2df( 0, SlipDistance ) );
		InfoBox->AddAnimator( ani );
		ani->drop();
		// �������붯��
		ani = MyIrrlichtEngine::GetEngine()->GetUIManager()->CreateAnimatorAlphaChange(
			0, FadeOutTime, 0, 255 );
		item.MsgImg->AddAnimator( ani );
		ani->drop();
	
	}
	// ���뾯��
	void AddWarn( PI_WARN warn );

};

#endif // PlayerInfo_h__
