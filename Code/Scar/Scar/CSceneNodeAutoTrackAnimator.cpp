#include "CSceneNodeAutoTrackAnimator.h"
#include "MyIrrlichtEngine.h"
#include <iostream>
#include <math.h>
//#include "Flame.h"



void CSceneNodeAnimatorAutoTrack::animateNode( scene::ISceneNode* node, u32 timeMs )
{
	using namespace core;
	
	isfirsttime = 0;

	if (!node || !Target)
		return;

	vector3df missle_pos = node->getPosition();
	vector3df target_pos = Target->getPosition();
	vector3df vector_a = target_pos - missle_pos;

	//判断加速度的方向是否与速度方向正好相反
	vector3df a_x = vector_a;
	a_x.setLength( missle_speed.getLength() );
	vector3df N_target_pos = target_pos;
	vector3df N_missle_speed = missle_speed;
	if ( N_target_pos.normalize().dotProduct( N_missle_speed.normalize() ) == -1.f )
	{
		vector_a.Z += 1.f;   //这里只需让加速度的方向是否与速度方向不正好相反
	}

	if ( vector_a.getLength() > max_range )  //超过最大搜索范围,加速度为0，保持原速度
		vector_a.setLength( 0 );

	vector_a.setLength( max_a );

	missle_speed = missle_speed * inertia + vector_a * ( 1 - inertia );	

	if ( missle_speed.getLength() > maxspeed )
	{
		missle_speed.setLength( maxspeed );	
	}

	vector3df RotAngle = Target->getAbsolutePosition() - node->getAbsolutePosition();
	RotAngle.normalize();
	node->setRotation( RotAngle.getHorizontalAngle() + vector3df( -90.f, 0.f, 0.f ) );

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

}

CSceneNodeAnimatorAutoTrack::CSceneNodeAnimatorAutoTrack( ISceneNode* target )
{
	isfirsttime = 1;
	lasttime = 0;
	t_sum = 0;
	maxspeed = 1.5f;
	inertia = 0.8f;
	max_a = 0.3f;
	max_range = 10000000.f;
	max_t = 10000;
	TimeForWay = 30;
	max_yinbao = 5.f;
	missle_speed = core::vector3df( 1, 1, 1 );
	Target = target;
}