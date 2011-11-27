#include "TheBeginMove.h"
#include <iostream>
#include "ICameraSceneNode.h"
#include <iostream>

TheBeginMove::TheBeginMove( vector3df thebeginpoint, vector3df theendpoint, u32 delay, u32 duration, int circle_n ):
TheBeginPoint( thebeginpoint ),TheEndPoint( theendpoint ),Duration( duration ), Circle_N( circle_n ),Delay( delay ),
Begin( 0 ), IsFirst( true )
{
	M_y =( TheEndPoint.Y - TheBeginPoint.Y ) / Duration;
	Distance = sqrt ( pow( ( TheEndPoint.X - TheBeginPoint.X ), 2 ) + pow( ( TheEndPoint.Z - TheBeginPoint.Z ), 2 ) );
	M_Distance = Distance / Duration;
	radian = 2 * (f32)PI * Circle_N / (f32)Duration;
	Center = TheEndPoint;
	Center.Y = TheBeginPoint.Y;
}

void TheBeginMove::animateNode( ISceneNode* node, u32 timeMs )
{
	ICameraSceneNode* camera = static_cast<ICameraSceneNode*>(node);
	//��ʼ��
	if ( IsFirst )
	{
		IsFirst = false;
		Begin = timeMs + Delay;
		vector2df direction = vector2df( ( camera->getTarget().X - camera->getPosition().X ), ( camera->getTarget().Z - camera->getPosition().Z ) );
		lastRad = (f32)direction.getAngle() - 90;
		lastRad *= DEGTORAD;
		std::cout<< direction.X << " , " << direction.Y << std::endl;
		std::cout<< lastRad << std::endl;
	}
	//��δ�ﵽ������ʼʱ��
	if( Begin > timeMs )
		return;

	u32 t;
	t = timeMs - Begin;	
	
	//���ﶯ������ʱ��
	if ( t > Duration )
	{
		//���Լ�ɾ��
		camera->removeAnimator(this);
		return;
	}
	camera -> setPosition( vector3df
		( Center.X + (Distance - M_Distance * t) * sin( radian * t + lastRad ) , 
		Center.Y + M_y * t , 
		Center.Z + (Distance - M_Distance * t)  * cos( radian * t + lastRad ) ));	
	camera ->setTarget(TheEndPoint);
}

ISceneNodeAnimator* TheBeginMove::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	return new TheBeginMove( TheBeginPoint,  TheEndPoint,  Delay,  Duration,  Circle_N );
}