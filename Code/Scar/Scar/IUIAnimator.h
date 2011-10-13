#ifndef UIAnimator_h__
#define UIAnimator_h__

#include <irrlicht.h>
using namespace irr;

class IUIObject;

class IUIAnimator : public irr::IReferenceCounted
{
public:
	virtual ~IUIAnimator() {}

	virtual bool animateUIObject( IUIObject* node, u32 timeMS ) = 0;
};

#endif // UIAnimator_h__
