#include "UIObject.h"
#include "MyIrrlichtEngine.h"


//////////////////////////////////////////////////////////////////
//名称：IUIObject
//描述：UI基类
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////

//构造函数
//IUIObject::IUIObject( IVideoDriver* driver, const vector2d<f32>& pos, s32 width, s32 height, s32 order )
//{
//	Driver = driver;
//
//	Center = pos;
//	DstQuar[0].X = pos.X - width / 2;
//	DstQuar[0].Y = pos.Y - height / 2;
//	DstQuar[1].X = DstQuar[0].X + width;
//	DstQuar[1].Y = DstQuar[0].Y;
//	DstQuar[2].X = DstQuar[0].X + width;
//	DstQuar[2].Y = DstQuar[0].Y + height;
//	DstQuar[3].X = DstQuar[0].X;
//	DstQuar[3].Y = DstQuar[0].Y + height;
//	
//	Image = NULL;
//	Alpha = 255;
//	Order = order;
//}


//////////////////////////////////////////////////////////////////
//名称：UIImage 
//描述：仅处理静态图片,继承IUIObject
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////

//绘制
void UIImage::Draw()
{
	UpdateAbsolutePosition();

	if (Image==NULL)
		return;
	int h = Image->getSize().Height;
	int w = Image->getSize().Width;
	rect<s32>r(0, 0, w, h);

	vector2d<s32> intDstQuar[4];
	ub::vector<f32> temp(3);
	temp(2) = 1;
	std::cout<<AbsoluteTransformation<<std::endl;
	for( int i=0; i<4; i++)
	{
		temp(0) = DestinationQuadrangle[i].X;
		temp(1) = DestinationQuadrangle[i].Y;
		temp = prod( temp, AbsoluteTransformation );
		intDstQuar[i].set( (s32)temp(0), (s32)temp(1) );
	}

	SColor colors[4];
	for (int i=0; i<4; i++)
	{
		colors[i] = SColor((u32)GetAbsoluteAlpha(),255,255,255);
	}

	Driver->draw2DImage( Image, intDstQuar, rect<s32>(0,0,w,h), 0, colors/*&SColor(Alpha,255,255,255)*/, true );
	//Driver->draw2DImage( Image, vector2d<s32>(0,0));
}
