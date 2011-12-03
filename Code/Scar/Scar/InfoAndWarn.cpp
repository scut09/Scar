#include "InfoAndWarn.h"

void InfoAndWarn::Update()
{
	UpdateInfo();
	UpdateWarn();
}

void InfoAndWarn::AddInfo( PI_INFO info )
{
	// 首先判断列表中是否已经存在这条消息
	for ( auto iter = InfoList.begin(); iter != InfoList.end(); ++iter )
	{
		if ( (*iter).msg == info )
			return;
	}
	// 新增文字项
	PIItem item;
	item.msg = info;
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

void InfoAndWarn::AddWarn( PI_INFO warn )
{
	// 首先判断列表中是否已经存在这条消息
	for ( auto iter = WarnList.begin(); iter != WarnList.end(); ++iter )
	{
		if ( (*iter).msg == warn )
			return;
	}
	// 新增文字项
	PIItem item;
	item.msg = warn;
	// 初始化状态
	item.State = 0;
	// 复制图片
	auto iter = WarnMap.find( warn );
	item.MsgImg = iter->second->Clone();
	item.MsgImg->drop();
	item.MsgImg->SetAlpha( 0 );
	// 加入列表
	WarnList.push_back( item );
}

void InfoAndWarn::UpdateInfo()
{
	// 控制时间间隔
	u32 timeMs = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
	if ( !InfoBox->GetAnimators().empty() )
		return;

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
	}
}

void InfoAndWarn::UpdateWarn()
{
	// 控制时间间隔
	u32 timeMs = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
	if ( !WarnBox->GetAnimators().empty() )
		return;

	//加入新信息
	for( auto iter = WarnList.begin(); iter != WarnList.end(); ++iter )
	{
		if ( (*iter).State == 0 )
		{
			// 创建时间
			(*iter).CreateTime = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
			(*iter).State = 1;
			WarnCount++;
			// 设置位置
			(*iter).MsgImg->SetVisible( true );
			(*iter).MsgImg->SetPosition( vector2df( 0, NextWarnPos ) );
			// 列表向上滑动
			IUIAnimator* ani = MyIrrlichtEngine::GetEngine()->GetUIManager()->CreateAnimatorTranslation(
				0, FadeOutTime, vector2df( 0, -SlipDistance ) );
			WarnBox->AddAnimator( ani );
			ani->drop();
			// 创建淡入动画
			ani = MyIrrlichtEngine::GetEngine()->GetUIManager()->CreateAnimatorAlphaChange(
				0, FadeOutTime, 0, 255 );
			(*iter).MsgImg->AddAnimator( ani );
			ani->drop();
			// 下一个位置
			NextWarnPos += SlipDistance;

			// 如果列表中的条目已经超出最大数，则删除多余的
			if ( WarnCount > MaxInfoNum )
			{
				for ( auto iter2 = WarnList.begin(); iter2 != WarnList.end(); ++iter2 )
				{
					if ( (*iter2).State == 1 )
					{
						WarnCount--;
						(*iter2).State = 2;
						// 创建淡出动画
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

	// 删除过时的信息
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
	}
}
