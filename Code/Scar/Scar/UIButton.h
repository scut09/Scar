#ifndef UIButton_h__
#define UIButton_h__

#include "IUIObject.h"
#include <functional>

using std::vector;
using namespace irr;
using namespace irr::core;
using namespace irr::video;

class IUIObject;

class UIButton : public IUIObject
{
public:

UIButton( IUIObject* parent, s32 width, s32 height, s32 order = 0,
			   const vector2d<f32>& position = vector2d<f32>(0,0),
			   f32 rotdeg = 0,
			   const vector2d<f32>& scale = vector2d<f32>(1,1) );

	virtual void Draw();

	std::function<void()> MouseMove;
	std::function<void()> MouseLeftButtonDown;
	std::function<void()> MouseRightButtonDown;
	

};

#endif // UIButton_h__
