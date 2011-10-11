#include "UIObject.h"

//////////////////////////////////////////////////////////////////
//名称：UIObject
//描述：UI基类
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////

//构造函数
UIObject::UIObject( vector2d<s32> pos, int width, int height )
{
	DstQuar[0].X = pos.X;
	DstQuar[0].Y = pos.Y;
	DstQuar[1].X = DstQuar[0].X + width;
	DstQuar[1].Y = DstQuar[0].Y;
	DstQuar[2].X = DstQuar[0].X + width;
	DstQuar[2].Y = DstQuar[0].Y + height;
	DstQuar[3].X = DstQuar[0].X;
	DstQuar[3].Y = DstQuar[0].Y + height;
	printf("%d",Image);
}
