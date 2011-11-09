#include "UIImage.h"
#include "MyIrrlichtEngine.h"
#include <iostream>

//////////////////////////////////////////////////////////////////
//名称：UIImage 
//描述：仅处理静态图片,继承IUIObject
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////

//绘制
void UIImage::Draw()
{
	UpdateAbsolutePosition();
	
	// 如果大小为0，那就没必要画自己了
	/*if( DestinationQuadrangle[0] == DestinationQuadrangle[2] )
		return;*/

	if (Image==NULL)
	{
		return;

	}
		
	int h = Image->getSize().Height;
	int w = Image->getSize().Width;
	rect<s32>SrcRect( (s32)LeftTop.X, (s32)LeftTop.Y, (s32)RightBottom.X, (s32)RightBottom.Y );

	vector2d<s32> intDstQuar[4];
	ub::vector<f32> temp(3);
	temp(2) = 1;

	temp(0) = DestinationQuadrangle[0].X + LeftTop.X;
	temp(1) = DestinationQuadrangle[0].Y + LeftTop.Y;
	temp = prod( temp, AbsoluteTransformation );
	intDstQuar[0].set( (s32)temp(0), (s32)temp(1) );
	temp(0) = DestinationQuadrangle[1].X + RightBottom.X - w;
	temp(1) = DestinationQuadrangle[1].Y + LeftTop.Y;
	temp = prod( temp, AbsoluteTransformation );
	intDstQuar[1].set( (s32)temp(0), (s32)temp(1) );
	temp(0) = DestinationQuadrangle[2].X + RightBottom.X - w;
	temp(1) = DestinationQuadrangle[2].Y + RightBottom.Y - h;
	temp = prod( temp, AbsoluteTransformation );
	intDstQuar[2].set( (s32)temp(0), (s32)temp(1) );
	temp(0) = DestinationQuadrangle[3].X + LeftTop.X;
	temp(1) = DestinationQuadrangle[3].Y + RightBottom.Y - h;
	temp = prod( temp, AbsoluteTransformation );
	intDstQuar[3].set( (s32)temp(0), (s32)temp(1) );

	SColor colors[4];
	for (int i=0; i<4; i++)
	{
		colors[i] = SColor((u32)GetAbsoluteAlpha(),255,255,255);
	}

	if ( bAntiAliasing )
	{
		Driver->enableMaterial2D();
	}
	rect<s32> * clipre = NULL;
	if ( ClipRect )
	{
		rect<f32> t= GetAbsoluteClipRect();
		rect<s32> re = rect<s32>( ( s32)t.UpperLeftCorner.X,( s32)t.UpperLeftCorner.Y,( s32)t.LowerRightCorner.X,( s32)t.LowerRightCorner.Y);
		clipre = &re;
	}
	Driver->draw2DImage( Image, intDstQuar, SrcRect, clipre, colors/*&SColor(Alpha,255,255,255)*/, true );
	if ( bAntiAliasing )
	{
		Driver->enableMaterial2D( false );
	}
	
	//Driver->draw2DImage( Image, vector2d<s32>(0,0));
}

UIImage::~UIImage()
{
	std::cout << "====> UIImage destruction\n";
}
