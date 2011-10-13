#include "DeletionUIAnimator.h"
#include "MyIrrlichtEngine.h"

DeletionAnimator::DeletionAnimator( u32 now, u32 time )
	: Time( time ), 
	Start( now ), bHasDone( false )
{

}

bool DeletionAnimator::animateUIObject( IUIObject* node, u32 timeMS )
{
	if ( ! bHasDone && Start + Time < timeMS )
	{
		bHasDone = true;
		MyIrrlichtEngine::GetEngine()->AddToDeletionQueue( node );
	}

	return true;
}