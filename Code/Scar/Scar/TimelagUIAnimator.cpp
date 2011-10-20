#include "TimelagUIAnimator.h"
#include "IUIObject.h"

TimelagUIAnimator::TimelagUIAnimator( u32 begin, u32 duration, std::string moduleName, std::string funName, bool loop ) : 
Begin( begin ), Duration( duration ), Loop( loop ), ModuleName(moduleName), FunctionName( funName )
{

}

bool TimelagUIAnimator::animateUIObject( IUIObject* node, u32 timeMS ) 
{
	//还未达到动画开始时间
	if ( Begin > timeMS )
		return false;

	u32 t = timeMS - Begin;
	if( t > Duration )
	{
		//要执行的函数写这里
		try
		{	
			using namespace boost::python;
			object module = import( ModuleName.c_str() );
			object fun = module.attr( FunctionName.c_str() );
			fun();
			node->RemoveAnimator(this);
			return false;

		}
		catch ( ... )
		{
			PyErr_Print();
		}
	}

	//到达动画结束时间
	if ( timeMS - Begin > Duration )
	{
		//循环
		if ( Loop )
		{
			Begin = timeMS;
		} 
		//不循环
		else
		{
			//把自己删掉
			node->RemoveAnimator(this);
			return false;
		}
	}

	return true;
}

TimelagUIAnimator* TimelagUIAnimator::Clone() 
{
	return new TimelagUIAnimator( Begin, Duration, ModuleName, FunctionName, Loop );
}