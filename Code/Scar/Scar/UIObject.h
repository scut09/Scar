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
////名称：IUIObject
////描述：UI基类
////作者：屠文翔，杨成熙
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
//	//shared_ptr<UIAnima> Animations;				//动画变换
//
//
//};


//////////////////////////////////////////////////////////////////
//名称：UIImage 
//描述：静态图片或动画,继承IUIObject
//作者：屠文翔，杨成熙
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
