#include "TimelagUIAnimator.h"
#include "IUIObject.h"

TimelagUIAnimator::TimelagUIAnimator( u32 begin, u32 duration, std::string moduleName, std::string funName, bool loop ) : 
Begin( begin ), Duration( duration ), Loop( loop ), ModuleName(moduleName), FunctionName( funName )
{

}

bool TimelagUIAnimator::animateUIObject( IUIObject* node, u32 timeMS ) 
{
	//��δ�ﵽ������ʼʱ��
	if ( Begin > timeMS )
		return false;

	u32 t = timeMS - Begin;
	if( t > Duration )
	{
		//Ҫִ�еĺ���д����
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

	//���ﶯ������ʱ��
	if ( timeMS - Begin > Duration )
	{
		//ѭ��
		if ( Loop )
		{
			Begin = timeMS;
		} 
		//��ѭ��
		else
		{
			//���Լ�ɾ��
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