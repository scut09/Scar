#include "UIObject.h"
#include "MyIrrlichtEngine.h"


//////////////////////////////////////////////////////////////////
//���ƣ�UIAnima
//������ʵ��UI��ƽ�ƣ���ת�����ţ�Alpah�ı�ȶ���
//���ߣ������裬�����
//////////////////////////////////////////////////////////////////

//���캯��
UIAnima::UIAnima( UIObject* host, int duration, ANIMA_END_OPTION opflag, int interval )
{
	Host = host;
	SetUIAnima( duration, opflag, interval);
	LastFrameTime = MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime();
	CurrentFrame = 0;
	HasRotate = HasScale = HasTranslate = false;
}
//���ö�����Ϣ
void UIAnima::SetUIAnima( int duration, ANIMA_END_OPTION opflag, int interval)
{
	Duration = duration;
	Interval = interval;
	EndOption = opflag;
	NumOfFrame = Duration / Interval;
}
//������Ŷ���
void UIAnima::AddScale( const vector2d<f32>& stretch, const vector2d<s32>& scalePoint )
{
	HasScale = true;
	StepStr.X = stretch.X / NumOfFrame;
	StepStr.Y = stretch.Y / NumOfFrame;
	StrCen = scalePoint;
}
//�����ת����
void UIAnima::AddRotate( float degree, const vector2d<s32>& rotatePoint )
{
	HasRotate = true;
	StepDeg = degree / NumOfFrame;
	RotCen = rotatePoint;
}
//���ƽ�ƶ���
void UIAnima::AddTranslate( const vector2d<s32> &offset )
{
	HasTranslate = true;
	StepTran.X = offset.X / NumOfFrame;
	StepTran.Y = offset.Y / NumOfFrame;
}
//���Alphaֵ�޸Ķ���
void UIAnima::AddAlphaChange( int alpha )
{
	HasAlphaChange = true;
	Alpha = alpha / NumOfFrame;
}
//��������
void UIAnima::Scale( const vector2d<f32> &stepstr, const vector2d<s32> &scalePoint )
{
	vector2d<s32> temQuar[4];
	//�л�������������Ϊԭ�������ϵ
	for (int i = 0; i < 4; i++)
	{
		temQuar[i].X = Host->DstQuar[i].X - scalePoint.X;
		temQuar[i].Y = Host->DstQuar[i].Y - scalePoint.Y;
	}
	//����
	for (int i = 0; i < 4; i++)
	{
		temQuar[i].X *= stepstr.X;
		temQuar[i].X *= stepstr.Y;
		//�ӻ�ԭ��������ϵ
		Host->DstQuar[i].X = temQuar[i].X + scalePoint.X;
		Host->DstQuar[i].X = temQuar[i].Y + scalePoint.Y;
	}
}
//������ת
void UIAnima::Rotate( float stepdeg, const vector2d<s32>& rotatePoint )
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
void UIAnima::Translate( const vector2d<s32> &steptran )
{
	//ƽ��
	for(int i = 0; i < 4; i++)
	{
		Host->DstQuar[i].X += steptran.X;
		Host->DstQuar[i].Y += steptran.Y;
	}
}
//����Alphaֵ�޸�
void UIAnima::AlphaChange( int Alpha )
{

}
//���ж���
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
//���ƣ�UIObject
//������UI����
//���ߣ������裬�����
//////////////////////////////////////////////////////////////////

//���캯��
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

//װ��ͼƬ
void UIObject::SetImage( char * filename )
{
	Image = Driver->getTexture( filename );
}
//�����ĵ�Ϊ��׼����Ԫ��λ��
void UIObject::SetCenter( const vector2d<s32>& pos )
{
	vector2d<s32> offset = pos - Center;
	for(int i = 0; i < 4; i++)
		DstQuar[i] += offset;
	Center = pos;
}
//��ȡԪ�����ĵ�λ��
const vector2d<s32>& UIObject::GetCenter() const
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
	Driver->draw2DImage( Image, DstQuar, rect<s32>(0,0,w,h), 0, &SColor(Alpha,255,255,255), true );
}
