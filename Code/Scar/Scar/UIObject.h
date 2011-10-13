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
//���ƣ�UIAnima
//������ʵ��UI��ƽ�ƣ���ת�����ţ�Alpah�ı�ȶ���
//���ߣ������裬�����
//////////////////////////////////////////////////////////////////
//class UIAnima
//{
//public:
//	//�������Ž�����Ĳ���
//	enum ANIMA_END_OPTION
//	{
//		STAY ,			//ͣ��
//		DESTROY			//��������
//	};
//
//private:
//	UIObject* Host;	//����
//
//	u32 Interval;		//ÿ��֡�����ļ��������
//	u32 Duration;		//�����ܹ��ĳ���ʱ��
//	u32 LastFrameTime;	//������һ֡ʱ��ʱ��
//	u32 NumOfFrame;		//�ܳ���֡��
//	u32 CurrentFrame;	//��ǰ֡��
//	u32 Loop;			//��ѭ��������0Ϊ����ѭ����
//	u32 CurrentLoop;	//��ǰѭ������
//	
//	ANIMA_END_OPTION EndOption;	//������������
//
//	bool HasScale;				//�Ƿ�������Ŷ���
//	bool HasRotate;				//�Ƿ������ת����
//	bool HasTranslate;			//�Ƿ����ƽ�ƶ���
//	vector2d<f32> RotCen;		//��ת���ĵ�
//	vector2d<f32> StrCen;		//�������ĵ�
//	float StepDeg;				//��ת�ǶȲ���ֵ
//	vector2d<f32> StepStr;		//���ű�������ֵ
//	vector2d<f32> StepTran;		//ƽ�Ʋ���ֵ	
//
//public:
//	UIAnima( UIObject* host, u32 duration = 30, u32 loop = 1,  ANIMA_END_OPTION opflag = STAY, u32 interval=30);
//	//���ö�����Ϣ
//	void SetUIAnima( u32 duration, u32 loop = 1, ANIMA_END_OPTION opflag = STAY, u32 interval=30);
//	//������Ŷ���
//	void AddScale( const vector2d<f32>& stretch, const vector2d<f32>& scalePoint );
//	//�����ת����
//	void AddRotate( float degree, const vector2d<f32>& rotatePoint );
//	//���ƽ�ƶ���
//	void AddTranslate( const vector2d<f32>& offset );
//	//��������
//	void Scale( const vector2d<f32>& stepstr, const vector2d<f32>& scalePoint );
//	//������ת
//	void Rotate( float stepdeg, const vector2d<f32>& rotatePoint );
//	//����ƽ��
//	void Translate( const vector2d<f32>& steptran );
//	//���ж���
//	void Run();
//
//};

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
	//vector< shared_ptr<UIObject> > Children;	//�Ӷ���
	//shared_ptr<UIObject> Parent;				//������
	ITexture * Image;							//Ӧ����UI�ϵ�ͼƬ
	IVideoDriver * Driver;						//Driverָ��
	int Alpha;									//Ԫ��͸����
	
public:
	UIObject();
	UIObject( IVideoDriver * driver, const vector2d<f32>& pos, int width, int height );
	virtual ~UIObject() {}

	//shared_ptr<UIAnima> Animations;				//�����任

	//����UIͼƬ
	void SetImage( char * );
	//�����ĵ�Ϊ��׼����Ԫ��λ��
	void SetCenter( const vector2d<f32>& pos );
	//��ȡԪ�����ĵ�λ��
	const vector2d<f32>& GetCenter() const;
	
	//�����麯��
	virtual void Draw() = 0;	
};


//////////////////////////////////////////////////////////////////
//���ƣ�UIImage 
//������������̬ͼƬ,�̳�UIObject
//���ߣ������裬�����
//////////////////////////////////////////////////////////////////
class UIImage : public UIObject
{
public:
	UIImage( IVideoDriver * driver, const vector2d<f32>& pos, int width, int height ) 
		: UIObject( driver, pos, width, height )
	{}
	void Draw();
};

#endif