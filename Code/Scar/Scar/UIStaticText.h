#ifndef UIStaticText_h__
#define UIStaticText_h__

#include "IUIObject.h"
#include "CGUITTFont.h"

using std::vector;
using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace irr::gui;

class IUIObject;

class UIStaticText : public IUIObject
{
public:
	UIStaticText( IUIObject* parent, s32 width, s32 hegit,
		stringw text,
		SColor color,
		u32 fontsize = 14,
		bool hcenter = false,
		bool vcenter = false,
		s32 order = 0, int shape = SQUARE,
		const vector2d<f32>& position = vector2d<f32>(0,0),
		f32 rotdeg = 0,
		const vector2d<f32>& scale = vector2d<f32>(1,1),
		bool Isvisible = true);
	virtual void Draw();
private:
	stringw Text;
	bool HorizontalCenter,VerticalCenter;
	SColor Color;
	u32 FontSize;
	IGUIEnvironment* Guienv;
	IGUIFont* Font;
};

#endif // UIStaticText_h__
