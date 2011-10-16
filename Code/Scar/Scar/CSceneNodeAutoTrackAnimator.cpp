#include "CSceneNodeAutoTrackAnimator.h"
#include "MyIrrlichtEngine.h"
#include <iostream>
#include <math.h>
#include "Flame.h"

int isfirsttime = 1;
u32 lasttime,t_sum = 0;
core::vector3df speed_daodan = core::vector3df(1,1,1);
//vector3df speed_daodan = vector3df(100,100,100);

CFlame flame;
std::list< scene::ISceneNode* > liziList;
//auto fire = flame.createFlame(
//	MyIrrlichtEngine::GetEngine()->GetDevice(), 
//	"../media/particle.bmp"
//	);

//auto fire;
//CFlame fire[100];

void CSceneNodeAnimatorAutoTrack::animateNode( scene::ISceneNode* node, u32 timeMs )
{
	using namespace core;

	static f32 x = 0, y = 0, z = 0;

	//for (int i = 0;i < 24;i++)
	//{
	//	CFlame flame;
	//	auto fire = flame.createFlame(
	//		MyIrrlichtEngine::GetEngine()->GetDevice(), 
	//		"../media/particle.bmp"
	//		);
	//	//	fire->setVisible(false);   //初始不可见
	//	node->addChild( fire );
	//}

	
	if (isfirsttime == 1)   //判断是否是第一次
	{
		node->setPosition(vector3df(0,0,200));
		lasttime = timeMs;
		
	}
	isfirsttime = 0;

	//scene::IParticleSystemSceneNode *ee = (scene::IParticleSystemSceneNode*)*(node->getChildren().begin());
	//ee->setVisible(true);
	
//	scene::IParticleSystemSceneNode *ee = (scene::IParticleSystemSceneNode*)*(node->getChildren().begin());
	//auto fireIter = node->getChildren().begin();
	//++fireIter;
	//for ( /*auto fireIter = node->getChildren().begin()*/; fireIter != node->getChildren().end(); ++fireIter )
	//{
	//	scene::IParticleSystemSceneNode *ee = (scene::IParticleSystemSceneNode*)*fireIter;
	//}

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

	for ( auto iter = nodeList.begin(); iter != nodeList.end(); ++iter )
	{
		auto pos = (*iter)->getPosition();
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

//		//std::cout <<"加速度向量："<< vector_a.X << " " << vector_a.Y << " " << vector_a.Z << std::endl;
		if (vector_a.getLength() > max_range)  //超过最大搜索范围,加速度为0，保持原速度
			vector_a.setLength(0);
		//std::cout <<"加速度向量："<< vector_a.X << " " << vector_a.Y << " " << vector_a.Z << std::endl;
		vector_a.setLength(max_a);

	//	//std::cout <<"旧速度向量："<< speed_daodan.X << " " << speed_daodan.Y << " " << speed_daodan.Z << std::endl;
		speed_daodan = speed_daodan * p_inertia + vector_a * (1 - p_inertia);

		//std::cout <<"速度向量："<< speed_daodan.X << " " << speed_daodan.Y << " " << speed_daodan.Z << std::endl;

		if (speed_daodan.getLength() > maxspeed)
		{
			speed_daodan.setLength(maxspeed);
		//	system("pause");
			//std::cout <<"实际速度："<<speed_daodan.getLength()<< std::endl;
		}

		//设置弹头方向与速度方向一致   这里需要将瓶子本身的三维坐标与世界坐标对应
		//计算旋转角度 asin计算得到的是弧度，所以 * 180 / 3.1415  
		a_x.X = (f32)( asin (speed_daodan.X / speed_daodan.getLength()) * 180 / 3.1415);
		a_x.Y = (f32)( asin (speed_daodan.Y / speed_daodan.getLength()) * 180 / 3.1415);
		a_x.Z = (f32)( asin (speed_daodan.Z / speed_daodan.getLength()) *  180 / 3.1415);	
		////std::cout <<"模型旋转："<< speed_daodan.X / speed_daodan.getLength() << " " << speed_daodan.Y / speed_daodan.getLength() << " " << speed_daodan.Z / speed_daodan.getLength() << std::endl;
		//std::cout <<"模型旋转角度："<< a_x.X << " " << a_x.Y << " " << a_x.Z << std::endl;
		node->setRotation(a_x + vector3df(0,-90,0));  // + vector3df(0,-90,0) 由于将瓶子本身的三维坐标与世界坐标不对应

		u32 t;
		t = timeMs - lasttime;
		lasttime = timeMs;

	//	core::vector3df pos;

		if ( t > TimeForWay)
		{
			t = TimeForWay;
			
		}
		//else  //这个需要根据实际速度来添加
		//{
		//	f32 phase = fmodf( (f32) t, (f32) TimeForWay );
		//	core::vector3df rel = Vector * phase * TimeFactor;

		//	pos += Start + rel;
		//	node->setPosition(pos);
		//}

		//std::cout <<"time:"<<t<< std::endl;
		t_sum+=t;
		node->setPosition(pos_daodan + speed_daodan * (f32) t);
	//	node->setPosition(pos_daodan + speed_daodan);
		vector3df distance;
		distance = node->getPosition() - pos;


		//for ( /*auto fireIter = node->getChildren().begin()*/int i = -10; fireIter != node->getChildren().end(); ++fireIter , i++)
		//{
		//	scene::IParticleSystemSceneNode *ee = (scene::IParticleSystemSceneNode*)*fireIter;
		//	ee->setPosition(pos_daodan+vector3df(/*interval * i,interval * i,*/0,interval * i,0));
		//	vector3df pos_lizi = ee->getPosition();
		////	//std::cout <<"粒子位置："<< pos_lizi.X << " " << pos_lizi.Y << " " << pos_lizi.Z << std::endl;
		//	//fireIter->setPosition(pos_daodan+vector3df(/*interval * i,interval * i,*/0,interval * i,0));
		//}

		//测试导弹与粒子的位置关系
		//++fireIter;
		//scene::IParticleSystemSceneNode *ee = (scene::IParticleSystemSceneNode*)*fireIter;
		//ee->setPosition(/*pos_daodan+*/vector3df(10,10,10)); 


	//		for (int i = 10;i < 11;i++)   //手工设置点位置
	//	{
	//		/*++fireIter;*/
	//		scene::IParticleSystemSceneNode *ee = (scene::IParticleSystemSceneNode*)*fireIter;
	//		ee->setPosition(vector3df(i,i,i));   //+,+,+
	//		++fireIter;
	//		ee = (scene::IParticleSystemSceneNode*)*fireIter;
	//		ee->setPosition(vector3df(i,i,-i));   //+,+,+
	//		++fireIter;
	//		ee = (scene::IParticleSystemSceneNode*)*fireIter;
	//		ee->setPosition(vector3df(i,-i,i));   //+,+,+
	//		++fireIter;
	//		ee = (scene::IParticleSystemSceneNode*)*fireIter;
	//		ee->setPosition(vector3df(i,-i,-i));   //+,+,+
	//		++fireIter;
	//		ee = (scene::IParticleSystemSceneNode*)*fireIter;
	//		ee->setPosition(vector3df(-i,i,i));   //+,+,+
	//		++fireIter;
	//		ee = (scene::IParticleSystemSceneNode*)*fireIter;
	//		ee->setPosition(vector3df(-i,i,-i));   //+,+,+
	//		++fireIter;
	//		ee = (scene::IParticleSystemSceneNode*)*fireIter;
	//		ee->setPosition(vector3df(-i,-i,i));   //+,+,+
	//		++fireIter;
	//		ee = (scene::IParticleSystemSceneNode*)*fireIter;
	//		ee->setPosition(vector3df(-i,-i,-i));   //+,+,+
	//	}


	

		//int i=10;
		//while (i<=30)
		//{
		//	
		//	scene::IParticleSystemSceneNode *ee = (scene::IParticleSystemSceneNode*)*fireIter;
		//	ee->setPosition(/*pos_daodan+*/vector3df(cos(a_x.X) * i,cos(a_x.Y) * i,cos(a_x.Z) * i));   //+,+,+
		//	++fireIter;
		//	ee = (scene::IParticleSystemSceneNode*)*fireIter;
		//	ee->setPosition(/*pos_daodan+*/vector3df(cos(a_x.X) * i,cos(a_x.Y) * i,-cos(a_x.Z) * i));   //+,+,-
		//	++fireIter;
		//	ee = (scene::IParticleSystemSceneNode*)*fireIter;
		//	ee->setPosition(/*pos_daodan+*/vector3df(cos(a_x.X) * i,-cos(a_x.Y) * i,cos(a_x.Z) * i));   //+,-,+
		//	++fireIter;
		//	ee = (scene::IParticleSystemSceneNode*)*fireIter;
		//	ee->setPosition(/*pos_daodan+*/vector3df(cos(a_x.X) * i,-cos(a_x.Y) * i,-cos(a_x.Z) * i));   //+,-,-
		//	++fireIter;
		//	ee = (scene::IParticleSystemSceneNode*)*fireIter;
		//	ee->setPosition(/*pos_daodan+*/vector3df(-cos(a_x.X) * i,cos(a_x.Y) * i,cos(a_x.Z) * i));   //-,+,+
		//	++fireIter;
		//	ee = (scene::IParticleSystemSceneNode*)*fireIter;
		//	ee->setPosition(/*pos_daodan+*/vector3df(-cos(a_x.X) * i,cos(a_x.Y) * i,-cos(a_x.Z) * i));   //-,+,-
		//	++fireIter;
		//	ee = (scene::IParticleSystemSceneNode*)*fireIter;
		//	ee->setPosition(/*pos_daodan+*/vector3df(-cos(a_x.X) * i,-cos(a_x.Y) * i,cos(a_x.Z) * i));   //-,-,+
		//	++fireIter;
		//	ee = (scene::IParticleSystemSceneNode*)*fireIter;
		//	ee->setPosition(/*pos_daodan+*/vector3df(-cos(a_x.X) * i,-cos(a_x.Y) * i,-cos(a_x.Z) * i));   //-,-,-

		//	i+=10;
		//}

	//	node->drop();

	//	std::list< CFlame* >& nodeList;  //记录所有已绘的点	

		
		
		int i=10;
	//	while (i<=10)	
		{			
			auto ee1 = flame.createFlame(
				MyIrrlichtEngine::GetEngine()->GetDevice(), 
				"../media/particle.bmp",0,-1,
				vector3df(0,0,0),
				SColor(0,0,0,255),
				1000,aabbox3df(0,0,0,1,1,1),
				vector3df(0,0.03f,0),10,10,
				1000,1000,(f32)0,
				SColor(0,255,255,255),SColor(0,255,255,255),
				dimension2df(6,9),dimension2df( 6,9 ),
				speed_daodan
				);			
			//ee1->setPosition(pos_daodan+vector3df(cos(a_x.X) * i,cos(a_x.Y) * i,cos(a_x.Z) * i));   //+,+,+
			ee1->setPosition(pos_daodan/*+vector3df( i, i, i)*/);   //+,+,+
			liziList.push_back(ee1);
			//auto ee2 = flame.createFlame(
			//	MyIrrlichtEngine::GetEngine()->GetDevice(), 
			//	"../media/particle.bmp",0,-1,
			//	vector3df(0,0,0),
			//	SColor(0,0,0,255),
			//	1000,aabbox3df(0,0,0,1,1,1),
			//	vector3df(0,0.03,0),10,10,
			//	1000,1000,0,
			//	SColor(0,255,255,255),SColor(0,255,255,255),
			//	dimension2df(6,9),dimension2df( 6,9 ),
			//	speed_daodan
			//	);
			////ee2->drop();
			//ee2->setPosition(pos_daodan+vector3df(cos(a_x.X) * i,cos(a_x.Y) * i,-cos(a_x.Z) * i));   //+,+,-
			//liziList.push_back(ee2);
			//auto ee3 = flame.createFlame(
			//	MyIrrlichtEngine::GetEngine()->GetDevice(), 
			//	"../media/particle.bmp",0,-1,
			//	vector3df(0,0,0),
			//	SColor(0,0,0,255),
			//	1000,aabbox3df(0,0,0,1,1,1),
			//	vector3df(0,0.03,0),10,10,
			//	1000,1000,0,
			//	SColor(0,255,255,255),SColor(0,255,255,255),
			//	dimension2df(6,9),dimension2df( 6,9 ),
			//	speed_daodan
			//	);
			//ee3->setPosition(pos_daodan+vector3df(cos(a_x.X) * i,-cos(a_x.Y) * i,cos(a_x.Z) * i));   //+,-,+
			//liziList.push_back(ee3);
			//auto ee4 = flame.createFlame(
			//	MyIrrlichtEngine::GetEngine()->GetDevice(), 
			//	"../media/particle.bmp",0,-1,
			//	vector3df(0,0,0),
			//	SColor(0,0,0,255),
			//	1000,aabbox3df(0,0,0,1,1,1),
			//	vector3df(0,0.03,0),10,10,
			//	1000,1000,0,
			//	SColor(0,255,255,255),SColor(0,255,255,255),
			//	dimension2df(6,9),dimension2df( 6,9 ),
			//	speed_daodan
			//	);
			//ee4->setPosition(pos_daodan+vector3df(cos(a_x.X) * i,-cos(a_x.Y) * i,-cos(a_x.Z) * i));   //+,-,-
			//liziList.push_back(ee4);
			//auto ee5 = flame.createFlame(
			//	MyIrrlichtEngine::GetEngine()->GetDevice(), 
			//	"../media/particle.bmp",0,-1,
			//	vector3df(0,0,0),
			//	SColor(0,0,0,255),
			//	1000,aabbox3df(0,0,0,1,1,1),
			//	vector3df(0,0.03,0),10,10,
			//	1000,1000,0,
			//	SColor(0,255,255,255),SColor(0,255,255,255),
			//	dimension2df(6,9),dimension2df( 6,9 ),
			//	speed_daodan
			//	);
			//ee5->setPosition(pos_daodan+vector3df(-cos(a_x.X) * i,cos(a_x.Y) * i,cos(a_x.Z) * i));   //-,+,+
			//liziList.push_back(ee5);
			//auto ee6 = flame.createFlame(
			//	MyIrrlichtEngine::GetEngine()->GetDevice(), 
			//	"../media/particle.bmp",0,-1,
			//	vector3df(0,0,0),
			//	SColor(0,0,0,255),
			//	1000,aabbox3df(0,0,0,1,1,1),
			//	vector3df(0,0.03,0),10,10,
			//	1000,1000,0,
			//	SColor(0,255,255,255),SColor(0,255,255,255),
			//	dimension2df(6,9),dimension2df( 6,9 ),
			//	speed_daodan
			//	);
			//ee6->setPosition(pos_daodan+vector3df(-cos(a_x.X) * i,cos(a_x.Y) * i,-cos(a_x.Z) * i));   //-,+,-
			//liziList.push_back(ee6);
			//auto ee7 = flame.createFlame(
			//	MyIrrlichtEngine::GetEngine()->GetDevice(), 
			//	"../media/particle.bmp",0,-1,
			//	vector3df(0,0,0),
			//	SColor(0,0,0,255),
			//	1000,aabbox3df(0,0,0,1,1,1),
			//	vector3df(0,0.03,0),10,10,
			//	1000,1000,0,
			//	SColor(0,255,255,255),SColor(0,255,255,255),
			//	dimension2df(6,9),dimension2df( 6,9 ),
			//	speed_daodan
			//	);
			//ee7->setPosition(pos_daodan+vector3df(-cos(a_x.X) * i,-cos(a_x.Y) * i,cos(a_x.Z) * i));   //-,-,+
			//liziList.push_back(ee7);
			//auto ee8 = flame.createFlame(
			//	MyIrrlichtEngine::GetEngine()->GetDevice(), 
			//	"../media/particle.bmp",0,-1,
			//	vector3df(0,0,0),
			//	SColor(0,0,0,255),
			//	1000,aabbox3df(0,0,0,1,1,1),
			//	vector3df(0,0.03,0),10,10,
			//	1000,1000,0,
			//	SColor(0,255,255,255),SColor(0,255,255,255),
			//	dimension2df(6,9),dimension2df( 6,9 ),
			//	speed_daodan
			//	);
			//ee8->setPosition(pos_daodan+vector3df(-cos(a_x.X) * i,-cos(a_x.Y) * i,-cos(a_x.Z) * i));   //-,-,-
			//liziList.push_back(ee8);
			i+=15;
		}

		//for (int i = 0;i < 10;i++)
	//	{
	//	int i = 1;

		/* ********************************************
		auto fire = flame.createFlame(
			MyIrrlichtEngine::GetEngine()->GetDevice(), 
			"../media/particle.bmp",0,-1,
			vector3df(0,0,0),
			SColor(0,0,0,255),
			1000,aabbox3df(0,0,0,1,1,1),
			vector3df(0,0.03,0),10,10,
			1000,1000,0,
			SColor(0,255,255,255),SColor(0,255,255,255),
			dimension2df(6,9),dimension2df( 6,9 ),
			speed_daodan
			);
		fire->setPosition(pos_daodan/*+vector3df(interval * i,interval * i,interval * i)*///);
           /***********************************************/
		
	

	//	fire->remove();


		if (distance.getLength() < max_yinbao)
		{
			//std::cout <<"已经爆炸"<< std::endl;  //这里调用爆炸函数
	/*		for (int i = 0;i < 20;i++)
			{			
				fire->setPosition(node->getPosition()+vector3df(i*interval,i*interval,i*interval));
				fire->setPosition(pos_daodan+vector3df(i*interval,i*interval,i*interval));
				fire->modifyFlameByAccel(speed_daodan);
			}*/
			/*node->setVisible(false);
			ee->setVisible(true);*/
		//	ee->
			break;
		}

		if (t_sum > max_t)
		{
			//std::cout <<"自我爆炸"<< std::endl;  //这里调用爆炸函数
			break;
		}

		if (t_sum > 2000)
		{
			for (int i = 0;i < 2 && liziList.size();i++)
			{
				(liziList.front())->remove();
				//(liziList.front())->drop();
				liziList.pop_front();
			}
			
			//for ( auto iter = liziList.begin(); iter != liziList)
		}

	
		break;
	}

}