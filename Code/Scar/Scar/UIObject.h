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

//////////////////////////////////////////////////////////////////
//���ƣ�UIObject
//������UI����
//���ߣ������裬�����
//////////////////////////////////////////////////////////////////
class UIObject
{
protected:

	vector2d<s32> DstQuar[4];		//��ʾ�������
	//int Width, Height;			
	//float RotDegree;
	vector2d<s32> RotCenter;		//��ת����
	vector< shared_ptr<UIObject> > Children;	//�Ӷ���
	shared_ptr<UIObject> Parent;				//������
	ITexture * Image;					//Ӧ����UI�ϵ�ͼƬ
	IVideoDriver * Driver;						//Driverָ��

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