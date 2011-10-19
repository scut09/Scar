
#ifndef huoyanshuxing_h__
#define huoyanshuxing_h__


#include <irrlicht.h>
#include "Flame.h"

using namespace irr;
using namespace scene;



class Chuoyanshuxing : public scene::ISceneNodeAnimator
{
public:
	Chuoyanshuxing( ISceneManager* man ) : m_pSmgr( man )
	{
		isfirsttime = 1;
		lasttime,t_sum = 0;
		speed_daodan = core::vector3df(1,1,1);
		amount_daodan = 5;   //导弹火焰的粒子数量
		//	CFlame firelist[amount_daodan];
		//	amount_daodan = 10;

	}

	virtual void animateNode( scene::ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone(
		ISceneNode* node,
		ISceneManager* newManager = 0 )
	{
		return NULL;
	}

private:
	ISceneManager*		m_pSmgr;

private:
	int isfirsttime ;
	u32 lasttime,t_sum ;
	core::vector3df speed_daodan;
	int amount_daodan;   //导弹火焰的粒子数量
	CFlame firelist[5];          //这个数应该与amount_daodan的值相同
	int head_firelist,tail_firelist;
	vector3df lastpos;

	//	core::vector3df Start;
	//	core::vector3df End;
	//	core::vector3df Vector;
	//	f32 TimeFactor;
	//	u32 StartTime;
	//	u32 TimeForWay;
	//
};


#endif // huoyanshuxing_h__