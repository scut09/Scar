#ifndef TimelagUIAnimator_h__
#define TimelagUIAnimator_h__

/************************************************************************/
/* 延迟一段时间后执行指定的函数                                         */
/************************************************************************/

#include "IUIAnimator.h"
#include <string>
#include "def.h"

using namespace irr::core;

class TimelagUIAnimator;

class TimelagUIAnimator : public IUIAnimator
{
private:
	u32 Begin;
	u32 Duration;
	bool Loop;
	std::string FunctionName;
	std::string ModuleName;

public:
	TimelagUIAnimator( u32 begin, u32 duration, std::string moduleName, std::string funName, bool loop = false );

	virtual bool animateUIObject( IUIObject* node, u32 timeMS );

	virtual TimelagUIAnimator* Clone();
};

#endif // TimelagUIAnimator_h__
