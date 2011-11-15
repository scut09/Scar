#pragma once
#include "MyIrrlichtEngine.h"
#undef LoadImage
class CHouseHelper
{     IUIObject * house;
public:
	CHouseHelper( MyIrrlichtEngine * pEngine,std::string name, IUIObject * parent = 0)
	{
		house = pEngine->GetUIManager()->AddUIImage( parent, 200, 200 );
		house->SetPosition(vector2df( 800, 400) );
		house->SetName(name);
		house->LoadImage("../media/UIResource/Menu/scrollbar_hbackground.png");
		IUIObject* text1 = pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40, L"房间", SColor( 255,255,255,255));
		IUIObject* text2 = pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40, L"疤痕", SColor( 255,255,255,255));
		IUIObject* text3 = pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40, L"地图", SColor( 255,255,255,255));
		IUIObject* text4 = pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40, L"宇宙", SColor( 255,255,255,255));
		IUIObject* text5 =pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40, L"人数", SColor( 255,255,255,255));
		IUIObject* text6 = pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40,L"100", SColor( 255,255,255,255));
		IUIObject* text7 =pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40, L"最大人数", SColor( 255,255,255,255));
		IUIObject* text8 = pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40, L"200", SColor( 255,255,255,255));
		IUIObject* text9 = pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40, L"延迟", SColor( 255,255,255,255));
		IUIObject* text10 = pEngine->GetUIManager()->AddUIStaticText( 0, 20, 40, L"0", SColor( 255,255,255,255));
		f32 PosX = -50;
		f32 PosY = -50;
		f32 Base = 80;
		text1->SetPosition( vector2df( PosX, PosY));
		house->AddChild( text1 );
		text2->SetPosition( vector2df( PosX + Base, PosY ));
		house->AddChild( text2 );
		text3->SetPosition( vector2df( PosX, PosY + 30));
		house->AddChild( text3 );
		text4->SetPosition( vector2df ( PosX + Base, PosY + 30));
		house->AddChild( text4 );
		text5->SetPosition( vector2df( PosX, PosY + 60));
		house->AddChild( text5 );
		text6->SetPosition( vector2df( PosX + Base , PosY + 60));
		house->AddChild( text6 );
		text7->SetPosition( vector2df( PosX, PosY + 90 ));
		house->AddChild( text7 );
		text8->SetPosition( vector2df( PosX + Base ,PosY + 90));
		house->AddChild( text8 );
		text9->SetPosition( vector2df( PosX, PosY + 120));
		house->AddChild( text9 );
		text10->SetPosition( vector2df( PosX +  Base, PosY + 120));
		house->AddChild( text10 );
	}
	IUIObject * GetHouse()const
	{
		
		return house;
	}
	~CHouseHelper(void);
};

