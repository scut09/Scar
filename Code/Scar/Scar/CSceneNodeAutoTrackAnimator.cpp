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
	a_x.X = (f32)( asin ( missle_speed.X / missle_speed.getLength() ) * 180 / 3.1415);
	a_x.Y = (f32)( asin ( missle_speed.Y / missle_speed.getLength() ) * 180 / 3.1415);
	a_x.Z = (f32)( asin ( missle_speed.Z / missle_speed.getLength() ) *  180 / 3.1415);		
	node->setRotation( a_x + vector3df( 90.f, 0.f, 0.f ) );  // + vector3df(0,-90,0) 由于将瓶子本身的三维坐标与世界坐标不对应

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


	if ( distance.getLength() < max_yinbao )
	{
		std::cout << "bomb !" << std::endl;
		node->setVisible( false );
	}

	if ( t_sum > max_t )
	{
	}

}