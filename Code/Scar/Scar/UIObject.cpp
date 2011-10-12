#include "UIObject.h"
#include <iostream>


//////////////////////////////////////////////////////////////////
//���ƣ�UIAnima
//������ʵ��UI��ƽ�ƣ���ת�����ţ�Alpah�ı�ȶ���
//���ߣ������裬�����
//////////////////////////////////////////////////////////////////

//���캯��
UIAnima::UIAnima( UIObject* host, int duration, ANIMA_END_OPTION opflag, int interval )
{
	SetUIAnima( duration, opflag, interval);
	NumOfFrame = Duration / Interval;
	CurrentFrame = 0;
	HasRotate = HasScale = HasTranslate = false;
}
//���ö�����Ϣ
void UIAnima::SetUIAnima( int duration, ANIMA_END_OPTION opflag, int interval)
{
	Duration = duration;
	Interval = interval;
	EndOption = opflag;
}
//������Ŷ���
void UIAnima::AddScale( vector2d<f32> stretch, vector2d<s32> scalePoint )
{
	HasScale = true;
	StepStr.X = stretch.X / NumOfFrame;
	StepStr.Y = stretch.Y / NumOfFrame;
	StrCen = scalePoint;
}
//�����ת����
void UIAnima::AddRotate( float degree, vector2d<s32> rotatePoint )
{
	HasRotate = true;
	StepDeg = degree / NumOfFrame;
	RotCen = rotatePoint;
}
//���ƽ�ƶ���
void AddTranslate( vector2d<s32> offset );
//��������
void Scale( vector2d<f32> stepstr, vector2d<s32> scalePoint );
//������ת
void UIAnima::Rotate( float stepdeg, vector2d<s32> rotatePoint )
{
	//���Ƕ�Ϊ��ʱ��
	//��¼�����ĸ�������ʱ����
	vector2d<s32> temQuar[4];
	for (int i = 0; i < 4; i++)
	{
		temQuar[i].X = Host->DstQuar[i].X - rotatePoint.X;
		temQuar[i].Y = Host->DstQuar[i].Y - rotatePoint.Y;
	}
	//�õ���ת�������
	for (int i = 0; i < 4; i++)
	{
		float x,y;
		x = (float)temQuar[i].X;
		y = (float)temQuar[i].Y;
		temQuar[i].X = (s32)(cos(stepdeg) * x - sin(stepdeg) * y);
		temQuar[i].Y = (s32)(sin(stepdeg) * x + cos(stepdeg) * y);
		//�ӻص�ԭ��������ϵ
		Host->DstQuar[i].X = temQuar[i].X + rotatePoint.X;
		Host->DstQuar[i].Y = temQuar[i].Y + rotatePoint.Y;
	}
}
//����ƽ��
void Translate( vector2d<s32> steptran );
//���ж���
void UIAnima::Run()
{
	if (HasScale)
	{
	}
	if (HasRotate)
	{
		Rotate( StepDeg, RotCen );
	}
}

//////////////////////////////////////////////////////////////////
//���ƣ�UIObject
//������UI����
//���ߣ������裬�����
//////////////////////////////////////////////////////////////////

//���캯��
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
	Center.X = (DstQuar[0].X + DstQuar[2].X) / 2;
	Center.Y = (DstQuar[0].Y + DstQuar[2].Y) / 2;
	Image = NULL;

	Animations = shared_ptr<UIAnima>( new UIAnima( this ) );
}

//װ��ͼƬ
void UIObject::SetImage( char * filename )
{
	Image = Driver->getTexture( filename );
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
	Driver->draw2DImage( Image, DstQuar, rect<s32>(0,0,w,h), 0, 0, true );
}
