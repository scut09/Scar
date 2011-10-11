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
private:

	vector2d<s32> DstQuar[4];		//��ʾ�������
	//int Width, Height;			
	//float RotDegree;
	vector2d<s32> RotCenter;		//��ת����
	vector< shared_ptr<UIObject> > Children;	//�Ӷ���
	shared_ptr<UIObject> Parent;				//������
	shared_ptr<ITexture> Image;					//Ӧ����UI�ϵ�ͼƬ

public:

	UIObject( vector2d<s32> pos, int width, int height );

	//����UIͼƬ
	ITexture * SetImage( irr::io::path &filename );
	
	//�����麯��
	virtual void Draw() = 0;
	
};


#endif