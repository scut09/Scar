#include "UIObject.h"
#include "MyIrrlichtEngine.h"


//////////////////////////////////////////////////////////////////
//名称：UIAnima
//描述：实现UI的平移，旋转，缩放，Alpah改变等动画
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////
//
////构造函数
//UIAnima::UIAnima( UIObject* host, u32 duration, u32 loop, ANIMA_END_OPTION opflag, u32 interval )
//{
//	Host = host;
//	SetUIAnima( duration, loop, opflag, interval);
//	LastFrameTime = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
//	CurrentFrame = 1;
//	CurrentLoop = 1;
//	HasRotate = HasScale = HasTranslate = false;
//}
////设置动画信息
//void UIAnima::SetUIAnima( u32 duration, u32 loop, ANIMA_END_OPTION opflag, u32 interval)
//{
//	Duration = duration;
//	Loop = loop;
//	Interval = interval;
//	EndOption = opflag;
//	NumOfFrame = Duration / Interval;
//}
////添加缩放动画
//void UIAnima::AddScale( const vector2d<f32>& stretch, const vector2d<f32>& scalePoint )
//{
//	HasScale = true;
//	StepStr.X = stretch.X / NumOfFrame;
//	StepStr.Y = stretch.Y / NumOfFrame;
//	StrCen = scalePoint;
//}
////添加旋转动画
//void UIAnima::AddRotate( float degree, const vector2d<f32>& rotatePoint )
//{
//	HasRotate = true;
//	StepDeg = degree / NumOfFrame;
//	RotCen = rotatePoint;
//}
////添加平移动画
//void AddTranslate( vector2d<f32> offset );
////步进缩放
//void Scale( vector2d<f32> stepstr, vector2d<f32> scalePoint );
////步进旋转
//void UIAnima::Rotate( float stepdeg, const vector2d<f32>& rotatePoint )
//{
//	float steprad = stepdeg / 180 * PI;
//	//正角度为逆时针
//	//记录矩阵四个顶点临时坐标
//	vector2d<f32> temQuar[4];
//	//得到旋转后的坐标
//	for (int i = 0; i < 4; i++)
//	{
//		temQuar[i] = Host->DstQuar[i] - rotatePoint;
//		float x,y;
//		x = (float)temQuar[i].X;
//		y = (float)temQuar[i].Y;
//		temQuar[i].X = cos(steprad) * x - sin(steprad) * y;
//		temQuar[i].Y = sin(steprad) * x + cos(steprad) * y;
//		//加回到原来的坐标系
//		Host->DstQuar[i] = temQuar[i] + rotatePoint;
//	}
//}
////步进平移
//void Translate( vector2d<f32> steptran );
////运行动画
//void UIAnima::Run()
//{
//	//控制帧频
//	u32 now = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
//	if(now - LastFrameTime < Interval )
//		return;
//	LastFrameTime = now;
//
//	//应用变换
//	if (HasScale)
//	{
//	}
//	if (HasRotate)
//	{
//		Rotate( StepDeg, RotCen );
//	}
//
//	//控制帧数
//	if(HasRotate || HasScale || HasTranslate)
//	{
//		CurrentFrame++;
//		if(CurrentFrame > NumOfFrame)
//		{
//			if(Loop == 0)
//			{
//				CurrentFrame = 1;
//			}
//			else
//			{
//				CurrentLoop++;
//				if(CurrentLoop > Loop)
//				{
//					if(EndOption == STAY)
//						HasTranslate = HasScale = HasRotate = false;
//				}
//			}
//		}
//	}
//}

//////////////////////////////////////////////////////////////////
//名称：UIObject
//描述：UI基类
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////

//构造函数
UIObject::UIObject( IVideoDriver* driver, const vector2d<f32>& pos, int width, int height )
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
//	Animations = shared_ptr<UIAnima>( new UIAnima( this ) );
}

//装载图片
void UIObject::SetImage( char * filename )
{
	Image = Driver->getTexture( filename );
}
//以中心点为基准设置元件位置
void UIObject::SetCenter( const vector2d<f32>& pos )
{
	vector2d<f32> offset = pos - Center;
	for(int i = 0; i < 4; i++)
		DstQuar[i] += offset;
	Center = pos;
}
//获取元件中心点位置
const vector2d<f32>& UIObject::GetCenter() const
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
	vector2d<s32> intDstQuar[4];
	for( int i=0; i<4; i++)
		intDstQuar[i].set( (s32)DstQuar[i].X, (s32)DstQuar[i].Y );
	SColor colors[4];
	for (int i=0; i<4; i++)
	{
		colors[i] = SColor(Alpha,255,255,255);
	}
	Driver->draw2DImage( Image, intDstQuar, rect<s32>(0,0,w,h), 0, colors/*&SColor(Alpha,255,255,255)*/, true );
	//Driver->draw2DImage( Image, vector2d<s32>(0,0));
}
