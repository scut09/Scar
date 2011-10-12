/********************************************************************
    创建时间: 2011-10-13   0:12
    文件名:   CSceneNodeAnimatorSelfDelFlyStraight.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     直线飞行的动画，飞到一定时间后删除自己

*********************************************************************/

#ifndef CSceneNodeAnimatorSelfDelFlyStraight_h__
#define CSceneNodeAnimatorSelfDelFlyStraight_h__


#include <irrlicht.h>

using namespace irr;
using namespace scene;


class CSceneNodeAnimatorSelfDelFlyStraight : public scene::ISceneNodeAnimator
{
public:
	CSceneNodeAnimatorSelfDelFlyStraight(
		const core::vector3df& startPoint,
		const core::vector3df& endPoint,
		u32 timeForWay,
		u32 now ) :
	Start(startPoint), End(endPoint), TimeFactor(0.0f), StartTime(now),
		TimeForWay(timeForWay)
	{
		Vector = End - Start;
		TimeFactor = (f32)Vector.getLength() / TimeForWay;
		Vector.normalize();
	}

	virtual void animateNode( scene::ISceneNode* node, u32 timeMs ) 
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

	virtual ISceneNodeAnimator* createClone(
		ISceneNode* node,
		ISceneManager* newManager = 0 ) 
	{
		return new CSceneNodeAnimatorSelfDelFlyStraight( Start, End, TimeForWay, StartTime );
	}

private:
	core::vector3df Start;
	core::vector3df End;
	core::vector3df Vector;
	f32 TimeFactor;
	u32 StartTime;
	u32 TimeForWay;

};


#endif // CSceneNodeAnimatorSelfDelFlyStraight_h__