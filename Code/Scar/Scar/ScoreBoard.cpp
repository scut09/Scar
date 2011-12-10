#include "ScoreBoard.h"
#include "PlayerHelper.h"

void ScoreBoard::Upadate()
{
	if (IsVisible)
	{
		for ( auto iter = ScoreNodeMap.begin(); iter != ScoreNodeMap.end(); ++iter )
		{
			stringw str;
			char buffer[50];
			ScoreItem* item;
			auto iterator = ScoreItemMap.find( iter->second );
			if ( iterator == ScoreItemMap.end() )
			{
				// 不在里面，创建新的
				/*item = CreateScoreItem( iter->second.Team );
				sprintf_s( buffer, "%s", iter->second.ip );
				str = buffer;
				item->player->SetText( str );*/
				//item = new ScoreItem();
				//ScoreItemMap[iter->second] = item;
				//item setposition

			}
			else
			{
				item = iterator->second;
			}
			/*sprintf_s( buffer, "%d", iter->second.KillCount );
			str = buffer;
			item->kills->SetText( str );
			sprintf_s( buffer, "%d", iter->second.DeathCount );
			str = buffer;
			item->deads->SetText( str );*/
		}
	}
}
