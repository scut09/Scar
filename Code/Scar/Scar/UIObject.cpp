#include "UIObject.h"
#include "MyIrrlichtEngine.h"


//////////////////////////////////////////////////////////////////
//���ƣ�UIAnima
//������ʵ��UI��ƽ�ƣ���ת�����ţ�Alpah�ı�ȶ���
//���ߣ������裬�����
//////////////////////////////////////////////////////////////////
//
////���캯��
//UIAnima::UIAnima( UIObject* host, u32 duration, u32 loop, ANIMA_END_OPTION opflag, u32 interval )
//{
//	Host = host;
//	SetUIAnima( duration, loop, opflag, interval);
//	LastFrameTime = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
//	CurrentFrame = 1;
//	CurrentLoop = 1;
//	HasRotate = HasScale = HasTranslate = false;
//}
////���ö�����Ϣ
//void UIAnima::SetUIAnima( u32 duration, u32 loop, ANIMA_END_OPTION opflag, u32 interval)
//{
//	Duration = duration;
//	Loop = loop;
//	Interval = interval;
//	EndOption = opflag;
//	NumOfFrame = Duration / Interval;
//}
////������Ŷ���
//void UIAnima::AddScale( const vector2d<f32>& stretch, const vector2d<f32>& scalePoint )
//{
//	HasScale = true;
//	StepStr.X = stretch.X / NumOfFrame;
//	StepStr.Y = stretch.Y / NumOfFrame;
//	StrCen = scalePoint;
//}
////�����ת����
//void UIAnima::AddRotate( float degree, const vector2d<f32>& rotatePoint )
//{
//	HasRotate = true;
//	StepDeg = degree / NumOfFrame;
//	RotCen = rotatePoint;
//}
////���ƽ�ƶ���
//void AddTranslate( vector2d<f32> offset );
////��������
//void Scale( vector2d<f32> stepstr, vector2d<f32> scalePoint );
////������ת
//void UIAnima::Rotate( float stepdeg, const vector2d<f32>& rotatePoint )
//{
//	float steprad = stepdeg / 180 * PI;
//	//���Ƕ�Ϊ��ʱ��
//	//��¼�����ĸ�������ʱ����
//	vector2d<f32> temQuar[4];
//	//�õ���ת�������
//	for (int i = 0; i < 4; i++)
//	{
//		temQuar[i] = Host->DstQuar[i] - rotatePoint;
//		float x,y;
//		x = (float)temQuar[i].X;
//		y = (float)temQuar[i].Y;
//		temQuar[i].X = cos(steprad) * x - sin(steprad) * y;
//		temQuar[i].Y = sin(steprad) * x + cos(steprad) * y;
//		//�ӻص�ԭ��������ϵ
//		Host->DstQuar[i] = temQuar[i] + rotatePoint;
//	}
//}
////����ƽ��
//void Translate( vector2d<f32> steptran );
////���ж���
//void UIAnima::Run()
//{
//	//����֡Ƶ
//	u32 now = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
//	if(now - LastFrameTime < Interval )
//		return;
//	LastFrameTime = now;
//
//	//Ӧ�ñ任
//	if (HasScale)
//	{
//	}
//	if (HasRotate)
//	{
//		Rotate( StepDeg, RotCen );
//	}
//
//	//����֡��
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
//���ƣ�UIObject
//������UI����
//���ߣ������裬�����
//////////////////////////////////////////////////////////////////

//���캯��
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

//װ��ͼƬ
void UIObject::SetImage( char * filename )
{
	Image = Driver->getTexture( filename );
}
//�����ĵ�Ϊ��׼����Ԫ��λ��
void UIObject::SetCenter( const vector2d<f32>& pos )
{
	vector2d<f32> offset = pos - Center;
	for(int i = 0; i < 4; i++)
		DstQuar[i] += offset;
	Center = pos;
}
//��ȡԪ�����ĵ�λ��
const vector2d<f32>& UIObject::GetCenter() const
{
	return Center;
}

//////////////////////////////////////////////////////////////////
//���ƣ�UIImage 
//������������̬ͼƬ,�̳�UIObject
//���ߣ������裬�����
//////////////////////////////////////////////////////////////////


//����
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
