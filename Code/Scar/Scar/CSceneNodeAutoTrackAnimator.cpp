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
	
	if (isfirsttime == 1)   //�ж��Ƿ��ǵ�һ��
	{
		node->setPosition(vector3df(0,0,200));
		lasttime = timeMs;
		
	}
	isfirsttime = 0;
	
	

	vector3df pos_daodan = node->getPosition();
	f32 maxspeed;  //
	maxspeed = 0.6;
	f32 p_inertia;  //����Ȩֵ
	p_inertia = 0.8;
	f32 max_a;  //�����ٶ�
	max_a = 0.3;            //���ٶ�ʵ��Ӱ���Ȩֵ������*��1-p_inertia);
	f32 max_range; //�����������Χ
	max_range=100000000;
	f32 max_yinbao; //��������
	max_yinbao = 2;
	u32 max_t;  //��������
	max_t = 100000;
	u32 TimeForWay;  //֡���ʱ�����ɷ��е����ʱ��
	TimeForWay = 30;
	std::cout << "pingzi: "<< pos_daodan.X << " " << pos_daodan.Y << " " << pos_daodan.Z << std::endl;

	//m_pSmgr->
	ModelManager* modelManager = MyIrrlichtEngine::GetEngine()->GetModelManager();
	const std::list< scene::ISceneNode* >& nodeList = modelManager->GetISceneNodeList();

	for ( auto iter = nodeList.begin(); iter != nodeList.end(); ++iter )
	{
		auto pos = (*iter)->getPosition();
		std::cout <<"�ɻ����꣺"<< pos.X << " " << pos.Y << " " << pos.Z << std::endl;
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

//		std::cout <<"���ٶ�������"<< vector_a.X << " " << vector_a.Y << " " << vector_a.Z << std::endl;
		if (vector_a.getLength() > max_range)  //�������������Χ,���ٶ�Ϊ0������ԭ�ٶ�
			vector_a.setLength(0);
		std::cout <<"���ٶ�������"<< vector_a.X << " " << vector_a.Y << " " << vector_a.Z << std::endl;
		vector_a.setLength(max_a);

	//	std::cout <<"���ٶ�������"<< speed_daodan.X << " " << speed_daodan.Y << " " << speed_daodan.Z << std::endl;
		speed_daodan = speed_daodan * p_inertia + vector_a * (1 - p_inertia);

		std::cout <<"�ٶ�������"<< speed_daodan.X << " " << speed_daodan.Y << " " << speed_daodan.Z << std::endl;

		if (speed_daodan.getLength() > maxspeed)
		{
			speed_daodan.setLength(maxspeed);
		//	system("pause");
			std::cout <<"ʵ���ٶȣ�"<<speed_daodan.getLength()<< std::endl;
		}

		//���õ�ͷ�������ٶȷ���һ��   ������Ҫ��ƿ�ӱ������ά���������������Ӧ
//		a_x = speed_daodan;
		//a_x.X = speed_daodan.X;
		//a_x.Y = speed_daodan.Z;
		//a_x.Z = speed_daodan.Y;
		//a_x.setLength(623);  //���ֵ���ܻ�Ҫ������
		//node->setRotation(a_x + vector3df(0,-90,0));
//����ط�������ĥ��
		a_x = node->getRotation();
		std::cout <<"ģ�ͱ�������ϵ��"<< a_x.X << " " << a_x.Y << " " << a_x.Z << std::endl;
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
			std::cout <<"�Ѿ���ը"<< std::endl;  //������ñ�ը����
			break;
		}

		if (t_sum > max_t)
		{
			std::cout <<"���ұ�ը"<< std::endl;  //������ñ�ը����
			break;
		}
	
		break;
	}




//	node->setRotation( vector3df( x++, y++, z++ ) );


//	node->setPosition( pos );
}