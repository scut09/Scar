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
		u32 now );

	virtual void animateNode( scene::ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone(
		ISceneNode* node,
		ISceneManager* newManager = 0 );

private:
	core::vector3df Start;
	core::vector3df End;
	core::vector3df Vector;
	f32 TimeFactor;
	u32 StartTime;
	u32 TimeForWay;

};


#endif // CSceneNodeAnimatorSelfDelFlyStraight_h__