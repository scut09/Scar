/********************************************************************
    创建时间: 2011-10-13   0:13
    文件名:   CSceneNodeAnimatorSelfDelFlyStraight.cpp
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     

*********************************************************************/

#include "CSceneNodeAnimatorSelfDelFlyStraight.h"


CSceneNodeAnimatorSelfDelFlyStraight::CSceneNodeAnimatorSelfDelFlyStraight( const core::vector3df& startPoint, const core::vector3df& endPoint, u32 timeForWay, u32 now ) :
Start(startPoint), End(endPoint), TimeFactor(0.0f), StartTime(now),
	TimeForWay(timeForWay)
{
	Vector = End - Start;
	TimeFactor = (f32)Vector.getLength() / TimeForWay;
	Vector.normalize();
}

void CSceneNodeAnimatorSelfDelFlyStraight::animateNode( scene::ISceneNode* node, u32 timeMs )
{
	if ( ! node )
		return;

	u32 t = timeMs - StartTime;

	core::vector3df pos;

	if ( t >= TimeForWay)
	{
		pos = End;
		node->setPosition(pos);
		node->removeAnimator( this );
	}
	else
	{
		f32 phase = fmodf( (f32) t, (f32) TimeForWay );
		core::vector3df rel = Vector * phase * TimeFactor;

		pos += Start + rel;
		node->setPosition(pos);
	}
}

ISceneNodeAnimator* CSceneNodeAnimatorSelfDelFlyStraight::createClone( ISceneNode* node, ISceneManager* newManager /*= 0 */ )
{
	return new CSceneNodeAnimatorSelfDelFlyStraight( Start, End, TimeForWay, StartTime );
}
