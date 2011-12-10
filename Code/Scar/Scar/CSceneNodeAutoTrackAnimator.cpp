#include "CSceneNodeAutoTrackAnimator.h"
#include "MyIrrlichtEngine.h"
#include <iostream>
#include <math.h>
//#include "Flame.h"



void CSceneNodeAnimatorAutoTrack::animateNode( scene::ISceneNode* node, u32 timeMs )
{
	using namespace core;

	static f32 x = 0, y = 0, z = 0;
	
	/*if (isfirsttime == 1)   //判断是否是第一次
	{
		node->setPosition(vector3df(0,0,200));
		lasttime = timeMs;
		head_firelist = amount_daodan - 1;
		for (int k = 0;k < amount_daodan;k++)
		{
			firelist[k].createFlame(
				MyIrrlichtEngine::GetEngine()->GetDevice(), 
				"../media/particle.bmp"				
				/ *,0,-1,
				vector3df(0,0,0),
				SColor(0,0,0,255),
				1000,aabbox3df(0,0,0,1,1,1),
				vector3df(0,0.03f,0),10,10,
				1000,1000,(f32)0,
				SColor(0,255,255,255),SColor(0,255,255,255),
				dimension2df(6,9),dimension2df( 6,9 ),
				speed_daodan* /
				);
			//firelist[k].modifyFlameByAccel(speed_daodan);
		//	firelist[k]->setVisible(false);	
		}	
		tail_firelist = 0;
	}*/
	isfirsttime = 0;

	vector3df pos_daodan = node->getPosition();
	f32 maxspeed;  //最快速度
	maxspeed = (f32) 0.6;
	f32 p_inertia;  //惯性权值
	p_inertia =(f32) 0.8;
	f32 max_a;  //最大加速度
	max_a = (f32) 0.3;            //对速度实际影响的权值，还将*（1-p_inertia);
	f32 max_range; //可搜索的最大范围
	max_range= (f32) 100000000;
	f32 max_yinbao; //引爆距离
	max_yinbao = (f32) 2;
	u32 max_t;  //导弹寿命
	max_t = (u32) 100000;
	u32 TimeForWay;  //帧间隔时导弹可飞行的最大时间
	TimeForWay = (u32)  30;
	f32 interval;  //粒子间距
	interval = (f32) 4;
	
	//std::cout << "pingzi: "<< pos_daodan.X << " " << pos_daodan.Y << " " << pos_daodan.Z << std::endl;

	//m_pSmgr->
	ModelManager* modelManager = MyIrrlichtEngine::GetEngine()->GetModelManager();
	const std::list< scene::ISceneNode* >& nodeList = modelManager->GetISceneNodeList();

	vector3df pos = Target->getPosition();
	//std::cout <<"飞机坐标："<< pos.X << " " << pos.Y << " " << pos.Z << std::endl;		
	vector3df vector_a;
	vector_a.X = pos.X-pos_daodan.X;
	vector_a.Y = pos.Y-pos_daodan.Y;
	vector_a.Z = pos.Z-pos_daodan.Z;

	//判断加速度的方向是否与速度方向正好相反
	vector3df a_x = vector_a;
	a_x.setLength(speed_daodan.getLength());
	if (-a_x == speed_daodan)
	{
		vector_a.Z += 1;   //这里只需让加速度的方向是否与速度方向不正好相反
	}

	if (vector_a.getLength() > max_range)  //超过最大搜索范围,加速度为0，保持原速度
		vector_a.setLength(0);

	vector_a.setLength(max_a);

	speed_daodan = speed_daodan * p_inertia + vector_a * (1 - p_inertia);	

	if (speed_daodan.getLength() > maxspeed)
	{
		speed_daodan.setLength(maxspeed);	
	}

	//设置跟踪的火焰
	/*for (int k = 0;k < 1;k++)
	{
		head_firelist++;
		firelist[head_firelist % amount_daodan].setpos(pos_daodan);
		firelist[head_firelist % amount_daodan].modifyFlameByAccel(speed_daodan);
		//firelist[head_firelist % 100]->
	}*/

	//设置弹头方向与速度方向一致   这里需要将瓶子本身的三维坐标与世界坐标对应
	//计算旋转角度 asin计算得到的是弧度，所以 * 180 / 3.1415  
	a_x.X = (f32)( asin (speed_daodan.X / speed_daodan.getLength()) * 180 / 3.1415);
	a_x.Y = (f32)( asin (speed_daodan.Y / speed_daodan.getLength()) * 180 / 3.1415);
	a_x.Z = (f32)( asin (speed_daodan.Z / speed_daodan.getLength()) *  180 / 3.1415);		
	node->setRotation(a_x + vector3df(0,-90,0));  // + vector3df(0,-90,0) 由于将瓶子本身的三维坐标与世界坐标不对应

	u32 t;
	t = timeMs - lasttime;
	lasttime = timeMs;

	if ( t > TimeForWay)
	{
		t = TimeForWay;

	}

	t_sum+=t;
	node->setPosition(pos_daodan + speed_daodan * (f32) t);

	vector3df distance;
	distance = node->getPosition() - pos;


	if (distance.getLength() < max_yinbao)
	{
		//std::cout <<"已经爆炸"<< std::endl;  //这里调用爆炸函数 然后返回	
	}

	if (t_sum > max_t)
	{
		//std::cout <<"自我爆炸"<< std::endl;  //这里调用爆炸函数  然后返回			
	}

}