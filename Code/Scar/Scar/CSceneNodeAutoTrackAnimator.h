
#ifndef CSceneNodeAnimatorAutoTrack_h__
#define CSceneNodeAnimatorAutoTrack_h__


#include <irrlicht.h>
#include "Flame.h"

using namespace irr;
using namespace scene;



class CSceneNodeAnimatorAutoTrack : public scene::ISceneNodeAnimator
{
public:
	CSceneNodeAnimatorAutoTrack( ISceneNode* target )
	{
		isfirsttime = 1;
		lasttime = 0;
		t_sum = 0;
		maxspeed = 0.6f;
		inertia = 0.8f;
		max_a = 0.3f;
		max_range = 10000000.f;
		max_t = 10000;
		TimeForWay = 30;
		missle_speed = core::vector3df( 1, 1, 1 );
		Target = target;
	}

	virtual void animateNode( scene::ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager = 0 )
	{
		return NULL;
	}

private:
	ISceneManager*	m_pSmgr;
	ISceneNode*		Target;
	u32 isfirsttime;
	u32 lasttime;
	u32	t_sum;
 	core::vector3df missle_speed;	//导弹速度
	f32 maxspeed;					//最快速度
	f32 inertia;					//惯性权值
	f32 max_a;						//最大加速度
	f32 max_range;					//可搜索的最大范围
	f32 max_yinbao;					//引爆距离
	u32 max_t;						//导弹寿命
	u32 TimeForWay;					//帧间隔时导弹可飞行的最大时间
};


#endif // CSceneNodeAnimatorSelfDelFlyStraight_h__