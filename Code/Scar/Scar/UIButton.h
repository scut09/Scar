#ifndef UIButton_h__
#define UIButton_h__

#include "IUIObject.h"

using std::vector;
using namespace irr;
using namespace irr::core;
using namespace irr::video;

class IUIObject;

class UIButton : public IUIObject
{
protected:
	bool IsMouseIn;

public:

	UIButton( IUIObject* parent, s32 width, s32 height, s32 order = 0, int shape = SQUARE,
		const vector2d<f32>& position = vector2d<f32>(0,0),
		f32 rotdeg = 0,
		const vector2d<f32>& scale = vector2d<f32>(1,1) );

	virtual IUIObject* Clone()
	{
		UIButton* btn = new UIButton( Parent, 0, 0 );
		btn->CloneMembersFrom( this );

		btn->IsMouseIn = IsMouseIn;

		btn->UpdateAbsolutePosition();

		return btn;
	}

	virtual void SetVisible( bool bVisible )
	{
		if ( ! bVisible )
		{
			IsMouseIn = false;
		}

		IUIObject::SetVisible( bVisible );
	}

	virtual void Draw();

	virtual void OnMouseMove( const irr::SEvent::SMouseInput& event );

	virtual void OnMouseLeftButtonUp( const irr::SEvent::SMouseInput& event );

	virtual void OnMouseLeftButtonDown( const irr::SEvent::SMouseInput& event );

	virtual void OnMouseRightButtonUp( const irr::SEvent::SMouseInput& event );

	virtual void OnMouseRightButtonDown( const irr::SEvent::SMouseInput& event );

	void OnMouseMoveIn();

	void OnMouseMoveOut();

};

#endif // UIButton_h__
