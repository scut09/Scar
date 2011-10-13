#ifndef SelfDeletionUIAnimator_h__
#define SelfDeletionUIAnimator_h__

#include "IUIAnimator.h"

class IUIObject;

class DeletionAnimator : public IUIAnimator
{
public:
	DeletionAnimator( u32 now, u32 time );

	virtual bool animateUIObject( IUIObject* node, u32 timeMS );

	virtual IUIAnimator* Clone()
	{
		return new DeletionAnimator( Start, Time );
	}

private:
	u32 Time;
	u32 Start;
	bool bHasDone;
};


#endif // SelfDeletionUIAnimator_h__
