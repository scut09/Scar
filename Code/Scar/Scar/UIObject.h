#ifndef UIOBJECT_H
#define UIOBJECT_H

#include "def.h"
#include <math.h>
#include "IUIObject.h"

using std::vector;
using namespace irr;
using namespace irr::core;
using namespace irr::video;

class UIObject;
class UIAnima;

//////////////////////////////////////////////////////////////////
//���ƣ�UIObject
//������UI����
//���ߣ������裬�����
//////////////////////////////////////////////////////////////////
class UIObject : public IUIObject
{
	
	public:
	vector2d<f32> DstQuar[4];					//��ʾ�������
	vector2d<f32> Center;						//���ε����ĵ�
	ITexture * Image;							//Ӧ����UI�ϵ�ͼƬ
	IVideoDriver * Driver;						//Driverָ��
	f32 Alpha;									//Ԫ��͸����
	s32 Order;									//Ԫ��������ͬһ��ʱ�İڷ�˳��
	
public:
	UIObject();
	UIObject( IVideoDriver * driver, const vector2d<f32>& pos, s32 width, s32 height, s32 Order = 0 );
	virtual ~UIObject() {}

	//shared_ptr<UIAnima> Animations;				//�����任

	//����UIͼƬ
	void SetImage( char * );
	//�����ĵ�Ϊ��׼����Ԫ��λ��
	void SetCenter( const vector2d<f32>& pos );
	//��ȡԪ�����ĵ�λ��
	const vector2d<f32>& GetCenter() const;
	//���Alphaֵ
	f32 GetAlpha();
	//����Alphaֵ
	void SetAlpha( f32 alpha );
};


//////////////////////////////////////////////////////////////////
//���ƣ�UIImage 
//��������̬ͼƬ�򶯻�,�̳�UIObject
//���ߣ������裬�����
//////////////////////////////////////////////////////////////////
class UIImage : public UIObject
{
public:
	UIImage( IVideoDriver * driver, const vector2d<f32>& pos, s32 width, s32 height, s32 order = 0 ) 
		: UIObject( driver, pos, width, height, order )
	{}
	void Draw();
};

#endif