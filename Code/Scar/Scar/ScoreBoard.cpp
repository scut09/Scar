#include "ScoreBoard.h"
#include "PlayerHelper.h"

void ScoreBoard::Upadate()
{
	if (IsVisible)
	{
		s32 i, j;
		f32 upperLine = -200;
		for ( auto iter = ScoreNodeMap.begin(); iter != ScoreNodeMap.end(); ++iter )
		{
			stringw str;
			char buffer[50];
			ScoreItem* item;
			auto iterator = ScoreItemMap.find( iter->second );
			if ( iterator == ScoreItemMap.end() )
			{
				// 不在里面，创建新的
				item = CreateScoreItem( iter->second.Team );
				sprintf_s( buffer, "%s", iter->second.ip );
				str = buffer;
				item->player->SetText( str );
			}
			else
			{
				item = iterator->second;
			}
			sprintf_s( buffer, "%d", iter->second.KillCount );
			str = buffer;
			item->kills->SetText( str );
			sprintf_s( buffer, "%d", iter->second.DeathCount );
			str = buffer;
			item->deads->SetText( str );
		}
	}
}

ScoreItem* ScoreBoard::CreateScoreItem( s32 team )
{
	ScoreItem* item = new ScoreItem();
	boost::shared_ptr<UIManager> uiMgr = MyIrrlichtEngine::GetEngine()->GetUIManager();
	f32 offX;
	if( team == 1 )
		offX = -200;
	else
		offX = 200;
	item->box = uiMgr->AddUIImage( 0, 0, 0 );
	item->player = static_cast<UIStaticText*>(uiMgr->AddUIStaticText( item->box, 100, 20, L"新玩家", video::SColor(255, 255, 255, 255), 18U));
	item->player->SetPosition( core::vector2df( offX - 120, 0 ) );
	item->kills = static_cast<UIStaticText*>(uiMgr->AddUIStaticText( item->box, 100, 20, L"0", video::SColor(255, 255, 255, 255), 18U));
	item->kills->SetPosition( core::vector2df( offX + 35, 0 ) );
	item->deads = static_cast<UIStaticText*>(uiMgr->AddUIStaticText( item->box, 100, 20, L"0", video::SColor(255, 255, 255, 255), 18U));
	item->deads->SetPosition( core::vector2df( offX + 156, 0 ) );

	return item;
}

void ScoreBoard::Init()
{
	uiMgr = MyIrrlichtEngine::GetEngine()->GetUIManager();
	Board = uiMgr->GetUIObjectByName( "ScoreBoard" );
	IsVisible = false;
	//test
	/*ScoreItem* item = CreateScoreItem( 1 );
	Board->AddChild( item->box );*/
}

ScoreBoard::ScoreBoard( std::map<u32, ScoreNode>& scoreNodeMap ) : ScoreNodeMap(scoreNodeMap)
{
	Init();
}
