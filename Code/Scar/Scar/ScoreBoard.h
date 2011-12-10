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
#include <map>

class ScoreBoard
{

public:
	ScoreBoard()
	{
	}

	void Init()
	{
		uiMgr = MyIrrlichtEngine::GetEngine()->GetUIManager();
		Board = uiMgr->GetUIObjectByName( "ScoreBoard" );
		IsVisible = false;
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

		}
	}

public:
	bool IsVisible;

private:
	boost::shared_ptr<UIManager> uiMgr;
	IUIObject* Board;
	
};

#endif // ScoreBoard_h__
