#include "CSceneNodeAutoTrackAnimator.h"
#include "MyIrrlichtEngine.h"
#include <iostream>

int isfirsttime = 1;
u32 lasttime,t_sum = 0;
core::vector3df speed_daodan = core::vector3df(1,1,1);
//vector3df speed_daodan = vector3df(100,100,100);


void CSceneNodeAnimatorAutoTrack::animateNode( scene::ISceneNode* node, u32 timeMs )
{
	using namespace core;

	static f32 x = 0, y = 0, z = 0;
	
	if (isfirsttime == 1)   //判断是否是第一次
	{
		node->setPosition(vector3df(0,0,200));
		lasttime = timeMs;
		
	}
	isfirsttime = 0;
	
	

	vector3df pos_daodan = node->getPosition();
	f32 maxspeed;  //
	maxspeed = 0.6;
	f32 p_inertia;  //惯性权值
	p_inertia = 0.8;
	f32 max_a;  //最大加速度
	max_a = 0.3;            //对速度实际影响的权值，还将*（1-p_inertia);
	f32 max_range; //可搜索的最大范围
	max_range=100000000;
	f32 max_yinbao; //引爆距离
	max_yinbao = 2;
	u32 max_t;  //导弹寿命
	max_t = 100000;
	u32 TimeForWay;  //帧间隔时导弹可飞行的最大时间
	TimeForWay = 30;
	std::cout << "pingzi: "<< pos_daodan.X << " " << pos_daodan.Y << " " << pos_daodan.Z << std::endl;

	//m_pSmgr->
	ModelManager* modelManager = MyIrrlichtEngine::GetEngine()->GetModelManager();
	const std::list< scene::ISceneNode* >& nodeList = modelManager->GetISceneNodeList();

	for ( auto iter = nodeList.begin(); iter != nodeList.end(); ++iter )
	{
		auto pos = (*iter)->getPosition();
		std::cout <<"飞机坐标："<< pos.X << " " << pos.Y << " " << pos.Z << std::endl;
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

//		std::cout <<"加速度向量："<< vector_a.X << " " << vector_a.Y << " " << vector_a.Z << std::endl;
		if (vector_a.getLength() > max_range)  //超过最大搜索范围,加速度为0，保持原速度
			vector_a.setLength(0);
		std::cout <<"加速度向量："<< vector_a.X << " " << vector_a.Y << " " << vector_a.Z << std::endl;
		vector_a.setLength(max_a);

	//	std::cout <<"旧速度向量："<< speed_daodan.X << " " << speed_daodan.Y << " " << speed_daodan.Z << std::endl;
		speed_daodan = speed_daodan * p_inertia + vector_a * (1 - p_inertia);

		std::cout <<"速度向量："<< speed_daodan.X << " " << speed_daodan.Y << " " << speed_daodan.Z << std::endl;

		if (speed_daodan.getLength() > maxspeed)
		{
			speed_daodan.setLength(maxspeed);
		//	system("pause");
			std::cout <<"实际速度："<<speed_daodan.getLength()<< std::endl;
		}

		//设置弹头方向与速度方向一致   这里需要将瓶子本身的三维坐标与世界坐标对应
//		a_x = speed_daodan;
		//a_x.X = speed_daodan.X;
		//a_x.Y = speed_daodan.Z;
		//a_x.Z = speed_daodan.Y;
		//a_x.setLength(623);  //这个值可能还要调整？
		//node->setRotation(a_x + vector3df(0,-90,0));
//这个地方还得琢磨，
		a_x = node->getRotation();
		std::cout <<"模型本身坐标系："<< a_x.X << " " << a_x.Y << " " << a_x.Z << std::endl;
		node->setRotation(vector3df(0,-90,0));

		u32 t;

		t = timeMs - lasttime;

		lasttime = timeMs;

	//	core::vector3df pos;

		if ( t > TimeForWay)
		{
			t = TimeForWay;
			/*pos = End;
			node->setPosition(pos);
			node->removeAnimator( this );*/
		}
		//else
		//{
		//	f32 phase = fmodf( (f32) t, (f32) TimeForWay );
		//	core::vector3df rel = Vector * phase * TimeFactor;

		//	pos += Start + rel;
		//	node->setPosition(pos);
		//}

		std::cout <<"time:"<<t<< std::endl;
		t_sum+=t;
		node->setPosition(pos_daodan + speed_daodan * t);
	//	node->setPosition(pos_daodan + speed_daodan);
		vector3df distance;
		distance = node->getPosition() - pos;

		if (distance.getLength() < max_yinbao)
		{
			std::cout <<"已经爆炸"<< std::endl;  //这里调用爆炸函数
			break;
		}

		if (t_sum > max_t)
		{
			std::cout <<"自我爆炸"<< std::endl;  //这里调用爆炸函数
			break;
		}
	
		break;
	}




//	node->setRotation( vector3df( x++, y++, z++ ) );


//	node->setPosition( pos );
}