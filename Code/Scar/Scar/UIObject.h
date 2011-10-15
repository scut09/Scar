#ifndef UIOBJECT_H
#define UIOBJECT_H

//#include "def.h"
#include <math.h>
#include "IUIObject.h"
#include <vector>

using std::vector;
using namespace irr;
using namespace irr::core;
using namespace irr::video;

class IUIObject;
class UIAnima;

////////////////////////////////////////////////////////////////////
////���ƣ�IUIObject
////������UI����
////���ߣ������裬�����
////////////////////////////////////////////////////////////////////
//class IUIObject : public IUIObject
//{
//	
//
//	
//public:
//	IUIObject();
//	IUIObject( IVideoDriver * driver, const vector2d<f32>& pos, s32 width, s32 height, s32 Order = 0 );
//	virtual ~IUIObject() {}
//
//	//shared_ptr<UIAnima> Animations;				//�����任
//
//
//};


//////////////////////////////////////////////////////////////////
//���ƣ�UIImage 
//��������̬ͼƬ�򶯻�,�̳�IUIObject
//���ߣ������裬�����
//////////////////////////////////////////////////////////////////
class UIImage : public IUIObject
{
public:
	UIImage( IVideoDriver * driver, const vector2d<f32>& pos, s32 width, s32 height, s32 order = 0 ) 
		: IUIObject( driver, pos, width, height, order )
	{}
	void Draw();
};

#endif
