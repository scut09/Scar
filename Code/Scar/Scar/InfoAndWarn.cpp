#include "InfoAndWarn.h"

void InfoAndWarn::Update()
{
	UpdateInfo();
	UpdateWarn();
}

void InfoAndWarn::AddInfo( PI_INFO info )
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

void InfoAndWarn::AddWarn( PI_INFO warn )
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

void InfoAndWarn::UpdateInfo()
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

void InfoAndWarn::UpdateWarn()
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
