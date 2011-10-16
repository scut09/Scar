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

	virtual void Draw()
	{

	}

	virtual void OnMouseLeftButtonDown( const irr::SEvent::SMouseInput& event ) 
	{
		throw std::exception("The method or operation is not implemented.");
	}

	virtual void OnKeyDown( const irr::SEvent::SKeyInput& event ) 
	{
		std::cout<< event.Key << std::endl;
	}


	std::function<void()> MouseMove;
	std::function<void()> MouseLeftButtonDown;
	std::function<void()> MouseRightButtonDown;
	

};

#endif // UIButton_h__
