#include "UIObject.h"
#include <iostream>

//////////////////////////////////////////////////////////////////
//名称：UIObject
//描述：UI基类
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////

//构造函数
UIObject::UIObject( IVideoDriver* driver, vector2d<s32> pos, int width, int height )
{
	Driver = driver;
	DstQuar[0].X = pos.X;
	DstQuar[0].Y = pos.Y;
	DstQuar[1].X = DstQuar[0].X + width;
	DstQuar[1].Y = DstQuar[0].Y;
	DstQuar[2].X = DstQuar[0].X + width;
	DstQuar[2].Y = DstQuar[0].Y + height;
	DstQuar[3].X = DstQuar[0].X;
	DstQuar[3].Y = DstQuar[0].Y + height;
}

//装载图片
void UIObject::SetImage( char * filename )
{
	Image = Driver->getTexture( filename );
}

//////////////////////////////////////////////////////////////////
//名称：UIImage 
//描述：仅处理静态图片,继承UIObject
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////


//绘制
void UIImage::Draw()
{
	int h = Image->getSize().Height;
	int w = Image->getSize().Width;
	rect<s32>r(0, 0, w, h);
	Driver->draw2DImage( Image, DstQuar, rect<s32>(0,0,w,h), 0, 0, true );
}
