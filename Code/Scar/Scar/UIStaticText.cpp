#include "UIStaticText.h"
#include "MyIrrlichtEngine.h"

#pragma comment(lib, "freetype247MT.lib")

#define FONT_PATH L"..\\media\\msyh.ttf"


UIStaticText::UIStaticText( IUIObject* parent, s32 width, s32 hegit, stringw text, SColor color, u32 fontsize /*= 14*/, bool hcenter /*= false*/, bool vcenter /*= false*/, s32 order /*= 0*/, int shape /*= SQUARE*/, const vector2d<f32>& position /*= vector2d<f32>(0,0)*/, f32 rotdeg /*= 0*/, const vector2d<f32>& scale /*= vector2d<f32>(1,1) */, bool isvisible /*= true*/ )
	: IUIObject( parent, width,  hegit, order, shape, position, rotdeg, scale )
{
	Text = text;
	HorizontalCenter = hcenter;
	VerticalCenter = vcenter;
	Color = color;
	FontSize = fontsize;
	IsVisible = isvisible;
	Guienv = MyIrrlichtEngine::GetEngine()->GetDevice()->getGUIEnvironment();
	Font = CGUITTFont::createTTFont( Guienv, FONT_PATH, FontSize );
}


void UIStaticText::Draw()
{
	if(!IsVisible)
		return;
	UpdateAbsolutePosition();
	vector2d<s32> intDstQuar[4];
	ub::vector<f32> temp(3);
	temp(2) = 1;
	//std::cout<<AbsoluteTransformation<<std::endl;
	for( int i=0; i<4; i++)
	{
		temp(0) = DestinationQuadrangle[i].X;
		temp(1) = DestinationQuadrangle[i].Y;
		temp = prod( temp, AbsoluteTransformation );
		intDstQuar[i].set( (s32)temp(0), (s32)temp(1) );
	}
	
	
	rect<s32> intrec( intDstQuar[0], intDstQuar[2] );

	Font->draw( Text, intrec, Color, HorizontalCenter, VerticalCenter);
}