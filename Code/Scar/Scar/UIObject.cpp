#include "UIObject.h"
#include "MyIrrlichtEngine.h"


//////////////////////////////////////////////////////////////////
//���ƣ�UIObject
//������UI����
//���ߣ������裬�����
//////////////////////////////////////////////////////////////////

//���캯��
UIObject::UIObject( IVideoDriver* driver, const vector2d<f32>& pos, s32 width, s32 height, s32 order )
{
	Driver = driver;

	Center = pos;
	DstQuar[0].X = pos.X - width / 2;
	DstQuar[0].Y = pos.Y - height / 2;
	DstQuar[1].X = DstQuar[0].X + width;
	DstQuar[1].Y = DstQuar[0].Y;
	DstQuar[2].X = DstQuar[0].X + width;
	DstQuar[2].Y = DstQuar[0].Y + height;
	DstQuar[3].X = DstQuar[0].X;
	DstQuar[3].Y = DstQuar[0].Y + height;
	
	Image = NULL;
	Alpha = 255;
	Order = order;
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

f32 UIObject::GetAlpha()
{
	return Alpha;
}

void UIObject::SetAlpha( f32 alpha )
{
	Alpha = alpha;
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
		colors[i] = SColor((u32)Alpha,255,255,255);
	}
	Driver->draw2DImage( Image, intDstQuar, rect<s32>(0,0,w,h), 0, colors/*&SColor(Alpha,255,255,255)*/, true );
	//Driver->draw2DImage( Image, vector2d<s32>(0,0));
}
