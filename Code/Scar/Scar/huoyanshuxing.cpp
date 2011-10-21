#include "huoyanshuxing.h"
#include "MyIrrlichtEngine.h"
#include <iostream>
#include <math.h>
//#include "Flame.h"

void Chuoyanshuxing::animateNode( scene::ISceneNode* node, u32 timeMs )
{
	using namespace core;

	static f32 x = 0, y = 0, z = 0;

	if (isfirsttime == 1)   //判断是否是第一次
	{
		node->setPosition(vector3df(0,0,200));
		lasttime = timeMs;
		head_firelist = amount_daodan - 1;
		for (int k = 0;k < amount_daodan;k++)
		{
			firelist[k].createFlame(
				MyIrrlichtEngine::GetEngine()->GetDevice(), 
				"../media/particle.bmp"
				);
		}	
		tail_firelist = 0;
	}
	isfirsttime = 0;

	vector3df pos_daodan = node->getPosition();
	speed_daodan = pos_daodan - lastpos;
	lastpos = pos_daodan;
	//设置跟踪的火焰
	for (int k = 0;k < 1;k++)
	{
		head_firelist++;
		firelist[head_firelist % amount_daodan].setpos(pos_daodan);
		firelist[head_firelist % amount_daodan].modifyFlameByAccel(speed_daodan);	
	}
}

Chuoyanshuxing::Chuoyanshuxing( ISceneManager* man ) : m_pSmgr( man )
{
	isfirsttime = 1;
	lasttime,t_sum = 0;
	speed_daodan = core::vector3df(1,1,1);
	amount_daodan = 1;   //导弹火焰的粒子数量
	//	CFlame firelist[amount_daodan];
	//	amount_daodan = 10;
}

ISceneNodeAnimator* Chuoyanshuxing::createClone( ISceneNode* node, ISceneManager* newManager /*= 0 */ )
{
	return NULL;
}

