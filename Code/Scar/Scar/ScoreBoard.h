#ifndef ScoreBoard_h__
#define ScoreBoard_h__

/********************************************************************
	创建日期:	2011/12/10
	文件名: 	C:\Users\Administrator\Desktop\工作\SCAR项目组\opengl-scut\Code\Scar\Scar\ScoreBoard.h
	作者:		屠文翔
	
	描述:		积分面板，按下Tab后调用，显示当前玩家，击杀数和死亡数
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
	f32 NextCItemPos, NextGItemPos;						// 下一个条目的位置
	
};

#endif // ScoreBoard_h__
