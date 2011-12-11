#include "CSceneNodeAutoTrackAnimator.h"
#include "MyIrrlichtEngine.h"
#include <iostream>
#include <math.h>
//#include "Flame.h"



void CSceneNodeAnimatorAutoTrack::animateNode( scene::ISceneNode* node, u32 timeMs )
{
	using namespace core;
	
	isfirsttime = 0;

	vector3df missle_pos = node->getPosition();
	vector3df target_pos = Target->getPosition();
	vector3df vector_a = target_pos - missle_pos;

	//�жϼ��ٶȵķ����Ƿ����ٶȷ��������෴
	vector3df a_x = vector_a;
	a_x.setLength( missle_speed.getLength() );
	vector3df N_target_pos = target_pos;
	vector3df N_missle_speed = missle_speed;
	if ( N_target_pos.normalize().dotProduct( N_missle_speed.normalize() ) == -1.f )
	{
		vector_a.Z += 1.f;   //����ֻ���ü��ٶȵķ����Ƿ����ٶȷ��������෴
	}

	if ( vector_a.getLength() > max_range )  //�������������Χ,���ٶ�Ϊ0������ԭ�ٶ�
		vector_a.setLength( 0 );

	vector_a.setLength( max_a );

	missle_speed = missle_speed * inertia + vector_a * ( 1 - inertia );	

	if ( missle_speed.getLength() > maxspeed )
	{
		missle_speed.setLength( maxspeed );	
	}

	//���õ�ͷ�������ٶȷ���һ��   ������Ҫ��ƿ�ӱ������ά���������������Ӧ
	//������ת�Ƕ� asin����õ����ǻ��ȣ����� * 180 / 3.1415  
	a_x.X = (f32)( asin ( missle_speed.X / missle_speed.getLength() ) * 180 / 3.1415);
	a_x.Y = (f32)( asin ( missle_speed.Y / missle_speed.getLength() ) * 180 / 3.1415);
	a_x.Z = (f32)( asin ( missle_speed.Z / missle_speed.getLength() ) *  180 / 3.1415);		
	node->setRotation( a_x + vector3df( 90.f, 0.f, 0.f ) );  // + vector3df(0,-90,0) ���ڽ�ƿ�ӱ������ά�������������겻��Ӧ

	u32 t;
	t = timeMs - lasttime;
	lasttime = timeMs;

	if ( t > TimeForWay)
	{
		t = TimeForWay;
	}

	t_sum += t;
	node->setPosition( missle_pos + missle_speed * (f32) t );

	vector3df distance;
	distance = node->getPosition() - target_pos;


	if ( distance.getLength() <= max_yinbao )
	{
		std::cout << "bomb !" << std::endl;
		node->setVisible( false );
	}

	if ( t_sum > max_t )
	{
	}

}

CSceneNodeAnimatorAutoTrack::CSceneNodeAnimatorAutoTrack( ISceneNode* target )
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
	max_yinbao = 5.f;
	missle_speed = core::vector3df( 1, 1, 1 );
	Target = target;
}