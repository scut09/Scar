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
		return;
	int h = Image->getSize().Height;
	int w = Image->getSize().Width;
	rect<s32>r(0, 0, w, h);

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

	SColor colors[4];
	for (int i=0; i<4; i++)
	{
		colors[i] = SColor((u32)GetAbsoluteAlpha(),255,255,255);
	}

	//Driver->enableMaterial2D();
	Driver->draw2DImage( Image, intDstQuar, rect<s32>(0,0,w,h), 0, colors/*&SColor(Alpha,255,255,255)*/, true );
	//sDriver->enableMaterial2D( false );
	
	//Driver->draw2DImage( Image, vector2d<s32>(0,0));
}

UIImage::~UIImage()
{
	std::cout << "====> UIImage destruction\n";
}
