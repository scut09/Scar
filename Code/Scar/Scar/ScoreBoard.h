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

struct ScoreItem
{
	IUIObject* box;
	UIStaticText* player;
	UIStaticText* kills;
	UIStaticText* deads;
};

struct ScoreNode;

class ScoreBoard
{
private:
	ScoreItem* CreateScoreItem( s32 team );

public:
	ScoreBoard( std::map<u32, ScoreNode>& scoreNodeMap );

	void Init();

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



	void Upadate();

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
