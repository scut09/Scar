#ifndef ScoreBoard_h__
#define ScoreBoard_h__

/********************************************************************
	��������:	2011/12/10
	�ļ���: 	C:\Users\Administrator\Desktop\����\SCAR��Ŀ��\opengl-scut\Code\Scar\Scar\ScoreBoard.h
	����:		������
	
	����:		������壬����Tab����ã���ʾ��ǰ��ң���ɱ����������
*********************************************************************/

#include "UIManager.h"
#include "MyIrrlichtEngine.h"
#include "irrlicht.h"
#include <map>

struct ScoreNode;

class ScoreBoard
{
private:
	struct ScoreItem
	{
		IUIObject* box;
		UIStaticText* player;
		UIStaticText* kills;
		UIStaticText* deads;
	};

	ScoreItem* CreateScoreItem( s32 team )
	{
		ScoreItem* item = new ScoreItem();
		boost::shared_ptr<UIManager> uiMgr = MyIrrlichtEngine::GetEngine()->GetUIManager();
		f32 offX;
		if( team == 1 )
			offX = -200;
		else
			offX = 200;
		item->box = uiMgr->AddUIImage( 0, 0, 0 );
		item->player = static_cast<UIStaticText*>(uiMgr->AddUIStaticText( item->box, 100, 20, L"�����", video::SColor(255, 255, 255, 255), 18U));
		item->player->SetPosition( core::vector2df( offX - 120, 0 ) );
		item->kills = static_cast<UIStaticText*>(uiMgr->AddUIStaticText( item->box, 100, 20, L"0", video::SColor(255, 255, 255, 255), 18U));
		item->kills->SetPosition( core::vector2df( offX + 35, 0 ) );
		item->deads = static_cast<UIStaticText*>(uiMgr->AddUIStaticText( item->box, 100, 20, L"0", video::SColor(255, 255, 255, 255), 18U));
		item->deads->SetPosition( core::vector2df( offX + 156, 0 ) );

		return item;
	}

public:
	ScoreBoard( std::map<u32, ScoreNode>& scoreNodeMap )
		: ScoreNodeMap(scoreNodeMap)
	{
		Init();
	}

	void Init()
	{
		uiMgr = MyIrrlichtEngine::GetEngine()->GetUIManager();
		Board = uiMgr->GetUIObjectByName( "ScoreBoard" );
		IsVisible = false;
		//test
		ScoreItem* item = CreateScoreItem( 1 );
		Board->AddChild( item->box );
	}

	void Show()
	{
		IsVisible = true;
		Board->SetVisible( true );
	}

	void Hide()
	{
		IsVisible = false;
		Board->SetVisible( false );
	}



	void Upadate()
	{
		if (IsVisible)
		{
			for ( auto iter = ScoreNodeMap.begin(); iter != ScoreNodeMap.end(); ++iter )
			{
				ScoreItem* item;
				auto iterator = ScoreItemMap.find( iter->second );
				if ( iterator == ScoreItemMap.end() )
				{
					// �������棬�����µ�
					//item = CreateScoreItem( iter->second );
					//item = new ScoreItem();
					//ScoreItemMap[iter->second] = item;
					//item setposition
					
				}
				else
				{
					item = iterator->second;
				}
				
			}
		}
	}

public:
	bool IsVisible;

private:
	boost::shared_ptr<UIManager> uiMgr;
	IUIObject* Board;
	std::map<ScoreNode, ScoreItem*> ScoreItemMap;
	std::map<u32, ScoreNode> ScoreNodeMap;
	f32 NextCItemPos, NextGItemPos;						// ��һ����Ŀ��λ��
	
};

#endif // ScoreBoard_h__
