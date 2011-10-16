#ifndef UIOBJECT_H
#define UIOBJECT_H

#include "IUIObject.h"

using std::vector;
using namespace irr;
using namespace irr::core;
using namespace irr::video;

class IUIObject;

//////////////////////////////////////////////////////////////////
//名称：UIImage 
//描述：静态图片或动画,继承IUIObject
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////
class UIImage : public IUIObject
{
public:
	UIImage( IUIObject* parent, s32 width, s32 height, s32 order = 0, 
		const vector2d<f32>& position = vector2d<f32>( 0, 0 ),
		f32 rotdeg = 0,
		const vector2d<f32>& scale = vector2d<f32>( 1.f, 1.f ) ) 
		: IUIObject( parent, width, height, order, position, rotdeg, scale )
	{}

	void Draw();


};

#endif
