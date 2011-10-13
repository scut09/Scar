#include "CSceneNodeAutoTrackAnimator.h"
#include "MyIrrlichtEngine.h"
#include <iostream>


void CSceneNodeAnimatorAutoTrack::animateNode( scene::ISceneNode* node, u32 timeMs )
{
	using namespace core;

	static f32 x = 0, y = 0, z = 0;

	vector3df pos_daodan = node->getPosition();
	vector3df speed_daodan;
	speed_daodan = vector3df(1,1,1);
	f32 maxspeed;  //
	maxspeed = 15;
	f32 p_inertia;  //惯性权值
	p_inertia = 0.7;
	f32 max_a;  //最大加速度
	max_a = 15;
	f32 max_range; //可搜索的最大范围
	max_range=100000;
	f32 max_yinbao; //引爆距离
	max_yinbao = 2;
	u32 max_t;  //导弹寿命
	max_t = 100000;
	//pingzisudu=2;

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
//		std::cout <<"加速度向量："<< vector_a.X << " " << vector_a.Y << " " << vector_a.Z << std::endl;
		if (vector_a.getLength() > max_range)  //超过最大搜索范围,加速度为0，保持原速度
			vector_a.setLength(0);
		std::cout <<"加速度向量："<< vector_a.X << " " << vector_a.Y << " " << vector_a.Z << std::endl;
		vector_a.setLength(max_a);
		speed_daodan = speed_daodan * p_inertia + vector_a * (1 - p_inertia);

		std::cout <<"速度向量："<< speed_daodan.X << " " << speed_daodan.Y << " " << speed_daodan.Z << std::endl;

		if (speed_daodan.getLength() > maxspeed)
		{
			speed_daodan.setLength(maxspeed);
			system("pause");
			std::cout <<"xxxxxxxxxxxxxxx"<< std::endl;
		}
		u32 lasttime = timeMs;
		
		u32 t,t_sum = 0;

		t = timeMs - lasttime;

		lasttime = timeMs;

		std::cout <<"time:"<<t<< std::endl;
		t_sum+=t;
	//	node->setPosition(pos_daodan + speed_daodan * t);
		node->setPosition(pos_daodan + speed_daodan);
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


 		



	/*	if (vector.getLength()>pingzisudu)
			vector.setLength(pingzisudu);
		else
			vector.setLength(vector.getLength());
		
		std::cout <<"向量新："<< vector.X << " " << vector.Y << " " << vector.Z << std::endl;
		
		node->setPosition(pingzipos+vector);*/
		
		break;
	}




//	node->setRotation( vector3df( x++, y++, z++ ) );


//	node->setPosition( pos );
}