#include "UIObject.h"
#include "MyIrrlichtEngine.h"


//////////////////////////////////////////////////////////////////
//名称：UIAnima
//描述：实现UI的平移，旋转，缩放，Alpah改变等动画
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////

//构造函数
UIAnima::UIAnima( UIObject* host, int duration, ANIMA_END_OPTION opflag, int interval )
{
	Host = host;
	SetUIAnima( duration, opflag, interval);
	LastFrameTime = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
	CurrentFrame = 0;
	HasRotate = HasScale = HasTranslate = false;
}
//设置动画信息
void UIAnima::SetUIAnima( int duration, ANIMA_END_OPTION opflag, int interval)
{
	Duration = duration;
	Interval = interval;
	EndOption = opflag;
	NumOfFrame = Duration / Interval;
}
//添加缩放动画
void UIAnima::AddScale( const vector2d<f32>& stretch, const vector2d<s32>& scalePoint )
{
	HasScale = true;
	StepStr.X = stretch.X / NumOfFrame;
	StepStr.Y = stretch.Y / NumOfFrame;
	StrCen = scalePoint;
}
//添加旋转动画
void UIAnima::AddRotate( float degree, const vector2d<s32>& rotatePoint )
{
	HasRotate = true;
	StepDeg = degree / NumOfFrame;
	RotCen = rotatePoint;
}
//添加平移动画
void UIAnima::AddTranslate( const vector2d<s32> &offset )
{
	HasTranslate = true;
	StepTran.X = offset.X / NumOfFrame;
	StepTran.Y = offset.Y / NumOfFrame;
}
//添加Alpha值修改动画
void UIAnima::AddAlphaChange( int alpha )
{
	HasAlphaChange = true;
	Alpha = alpha / NumOfFrame;
}
//步进缩放
void UIAnima::Scale( const vector2d<f32> &stepstr, const vector2d<s32> &scalePoint )
{
	vector2d<s32> temQuar[4];
	//切换到以拉伸中心为原点的坐标系
	for (int i = 0; i < 4; i++)
	{
		temQuar[i].X = Host->DstQuar[i].X - scalePoint.X;
		temQuar[i].Y = Host->DstQuar[i].Y - scalePoint.Y;
	}
	//拉伸
	for (int i = 0; i < 4; i++)
	{
		temQuar[i].X *= stepstr.X;
		temQuar[i].X *= stepstr.Y;
		//加回原来的坐标系
		Host->DstQuar[i].X = temQuar[i].X + scalePoint.X;
		Host->DstQuar[i].X = temQuar[i].Y + scalePoint.Y;
	}
}
//步进旋转
void UIAnima::Rotate( float stepdeg, const vector2d<s32>& rotatePoint )
{
	//正角度为逆时针
	//记录矩阵四个顶点临时坐标
	vector2d<s32> temQuar[4];
	for (int i = 0; i < 4; i++)
	{
		temQuar[i].X = Host->DstQuar[i].X - rotatePoint.X;
		temQuar[i].Y = Host->DstQuar[i].Y - rotatePoint.Y;
	}
	//得到旋转后的坐标
	for (int i = 0; i < 4; i++)
	{
		float x,y;
		x = (float)temQuar[i].X;
		y = (float)temQuar[i].Y;
		temQuar[i].X = (s32)(cos(stepdeg) * x - sin(stepdeg) * y);
		temQuar[i].Y = (s32)(sin(stepdeg) * x + cos(stepdeg) * y);
		//加回到原来的坐标系
		Host->DstQuar[i].X = temQuar[i].X + rotatePoint.X;
		Host->DstQuar[i].Y = temQuar[i].Y + rotatePoint.Y;
	}
}
//步进平移
void UIAnima::Translate( const vector2d<s32> &steptran )
{
	//平移
	for(int i = 0; i < 4; i++)
	{
		Host->DstQuar[i].X += steptran.X;
		Host->DstQuar[i].Y += steptran.Y;
	}
}
//步进Alpha值修改
void UIAnima::AlphaChange( int Alpha )
{

}
//运行动画
void UIAnima::Run()
{
	u32 now = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();

	if (HasScale)
	{
	}
	if (HasRotate)
	{
		Rotate( StepDeg, RotCen );
	}
}

//////////////////////////////////////////////////////////////////
//名称：UIObject
//描述：UI基类
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////

//构造函数
UIObject::UIObject( IVideoDriver* driver, const vector2d<s32>& pos, int width, int height )
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
	Center.X = (DstQuar[0].X + DstQuar[2].X) / 2;
	Center.Y = (DstQuar[0].Y + DstQuar[2].Y) / 2;
	Image = NULL;
	Alpha = 255;
	Animations = shared_ptr<UIAnima>( new UIAnima( this ) );
}

//装载图片
void UIObject::SetImage( char * filename )
{
	Image = Driver->getTexture( filename );
}
//以中心点为基准设置元件位置
void UIObject::SetCenter( const vector2d<s32>& pos )
{
	vector2d<s32> offset = pos - Center;
	for(int i = 0; i < 4; i++)
		DstQuar[i] += offset;
	Center = pos;
}
//获取元件中心点位置
const vector2d<s32>& UIObject::GetCenter() const
{
	return Center;
}

//////////////////////////////////////////////////////////////////
//名称：UIImage 
//描述：仅处理静态图片,继承UIObject
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////


//绘制
void UIImage::Draw()
{
	if (Image==NULL)
		return;
	int h = Image->getSize().Height;
	int w = Image->getSize().Width;
	rect<s32>r(0, 0, w, h);
	Driver->draw2DImage( Image, DstQuar, rect<s32>(0,0,w,h), 0, &SColor(Alpha,255,255,255), true );
}
