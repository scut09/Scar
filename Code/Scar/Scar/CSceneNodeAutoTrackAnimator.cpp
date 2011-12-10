#include "CSceneNodeAutoTrackAnimator.h"
#include "MyIrrlichtEngine.h"
#include <iostream>
#include <math.h>
//#include "Flame.h"



void CSceneNodeAnimatorAutoTrack::animateNode( scene::ISceneNode* node, u32 timeMs )
{
	using namespace core;

	static f32 x = 0, y = 0, z = 0;
	
	/*if (isfirsttime == 1)   //�ж��Ƿ��ǵ�һ��
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
	f32 maxspeed;  //����ٶ�
	maxspeed = (f32) 0.6;
	f32 p_inertia;  //����Ȩֵ
	p_inertia =(f32) 0.8;
	f32 max_a;  //�����ٶ�
	max_a = (f32) 0.3;            //���ٶ�ʵ��Ӱ���Ȩֵ������*��1-p_inertia);
	f32 max_range; //�����������Χ
	max_range= (f32) 100000000;
	f32 max_yinbao; //��������
	max_yinbao = (f32) 2;
	u32 max_t;  //��������
	max_t = (u32) 100000;
	u32 TimeForWay;  //֡���ʱ�����ɷ��е����ʱ��
	TimeForWay = (u32)  30;
	f32 interval;  //���Ӽ��
	interval = (f32) 4;
	
	//std::cout << "pingzi: "<< pos_daodan.X << " " << pos_daodan.Y << " " << pos_daodan.Z << std::endl;

	//m_pSmgr->
	ModelManager* modelManager = MyIrrlichtEngine::GetEngine()->GetModelManager();
	const std::list< scene::ISceneNode* >& nodeList = modelManager->GetISceneNodeList();

	vector3df pos = Target->getPosition();
	//std::cout <<"�ɻ����꣺"<< pos.X << " " << pos.Y << " " << pos.Z << std::endl;		
	vector3df vector_a;
	vector_a.X = pos.X-pos_daodan.X;
	vector_a.Y = pos.Y-pos_daodan.Y;
	vector_a.Z = pos.Z-pos_daodan.Z;

	//�жϼ��ٶȵķ����Ƿ����ٶȷ��������෴
	vector3df a_x = vector_a;
	a_x.setLength(speed_daodan.getLength());
	if (-a_x == speed_daodan)
	{
		vector_a.Z += 1;   //����ֻ���ü��ٶȵķ����Ƿ����ٶȷ��������෴
	}

	if (vector_a.getLength() > max_range)  //�������������Χ,���ٶ�Ϊ0������ԭ�ٶ�
		vector_a.setLength(0);

	vector_a.setLength(max_a);

	speed_daodan = speed_daodan * p_inertia + vector_a * (1 - p_inertia);	

	if (speed_daodan.getLength() > maxspeed)
	{
		speed_daodan.setLength(maxspeed);	
	}

	//���ø��ٵĻ���
	/*for (int k = 0;k < 1;k++)
	{
		head_firelist++;
		firelist[head_firelist % amount_daodan].setpos(pos_daodan);
		firelist[head_firelist % amount_daodan].modifyFlameByAccel(speed_daodan);
		//firelist[head_firelist % 100]->
	}*/

	//���õ�ͷ�������ٶȷ���һ��   ������Ҫ��ƿ�ӱ������ά���������������Ӧ
	//������ת�Ƕ� asin����õ����ǻ��ȣ����� * 180 / 3.1415  
	a_x.X = (f32)( asin (speed_daodan.X / speed_daodan.getLength()) * 180 / 3.1415);
	a_x.Y = (f32)( asin (speed_daodan.Y / speed_daodan.getLength()) * 180 / 3.1415);
	a_x.Z = (f32)( asin (speed_daodan.Z / speed_daodan.getLength()) *  180 / 3.1415);		
	node->setRotation(a_x + vector3df(0,-90,0));  // + vector3df(0,-90,0) ���ڽ�ƿ�ӱ������ά�������������겻��Ӧ

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
		//std::cout <<"�Ѿ���ը"<< std::endl;  //������ñ�ը���� Ȼ�󷵻�	
	}

	if (t_sum > max_t)
	{
		//std::cout <<"���ұ�ը"<< std::endl;  //������ñ�ը����  Ȼ�󷵻�			
	}

}