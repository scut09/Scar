#ifndef UIOBJECT_H
#define UIOBJECT_H

#include "def.h"
#include <math.h>
#include <vector>

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
class UIAnima
{
	//�������Ž�����Ĳ���
	enum ANIMA_END_OPTION
	{
		STAY ,			//ͣ��
		DESTROY			//��������
	};

private:
	UIObject* Host;	//����
	int Interval;		//ÿ��֡�����ļ��������
	int Duration;		//�����ܹ��ĳ���ʱ��
	int NumOfFrame;		//�ܳ���֡��
	int CurrentFrame;	//��ǰ֡��
	ANIMA_END_OPTION EndOption;	//������������
	bool HasScale;				//�Ƿ�������Ŷ���
	bool HasRotate;				//�Ƿ������ת����
	bool HasTranslate;			//�Ƿ����ƽ�ƶ���
	vector2d<s32> RotCen;		//��ת���ĵ�
	vector2d<s32> StrCen;		//�������ĵ�
	float StepDeg;				//��ת�ǶȲ���ֵ
	vector2d<f32> StepStr;		//���ű�������ֵ
	vector2d<s32> StepTran;		//ƽ�Ʋ���ֵ	
public:
	UIAnima( UIObject* host, int duration = 30, ANIMA_END_OPTION opflag = STAY, int interval=30);
	//���ö�����Ϣ
	void SetUIAnima( int duration, ANIMA_END_OPTION opflag = STAY, int interval=30);
	//������Ŷ���
	void AddScale( vector2d<f32> stretch, vector2d<s32> scalePoint );
	//�����ת����
	void AddRotate( float degree, vector2d<s32> rotatePoint );
	//���ƽ�ƶ���
	void AddTranslate( vector2d<s32> offset );
	//��������
	void Scale( vector2d<f32> stepstr, vector2d<s32> scalePoint );
	//������ת
	void Rotate( float stepdeg, vector2d<s32> rotatePoint );
	//����ƽ��
	void Translate( vector2d<s32> steptran );
	//���ж���
	void Run();

};

//////////////////////////////////////////////////////////////////
//���ƣ�UIObject
//������UI����
//���ߣ������裬�����
//////////////////////////////////////////////////////////////////
class UIObject
{
	friend class UIAnima;	//������ΪUI�����Ԫ��

protected:
	vector2d<s32> DstQuar[4];					//��ʾ�������
	vector2d<s32> Center;						//���ε����ĵ�
	vector< shared_ptr<UIObject> > Children;	//�Ӷ���
	shared_ptr<UIObject> Parent;				//������
	ITexture * Image;							//Ӧ����UI�ϵ�ͼƬ
	IVideoDriver * Driver;						//Driverָ��
	shared_ptr<UIAnima> Animations;				//�����任
	
public:
	UIObject();
	UIObject( IVideoDriver * driver, vector2d<s32> pos, int width, int height );

	virtual ~UIObject() {}

	//����UIͼƬ
	void SetImage( char * );
	
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
	UIImage( IVideoDriver * driver, vector2d<s32> pos, int width, int height ) 
		: UIObject( driver, pos, width, height )
	{}
	void Draw();
};

#endif