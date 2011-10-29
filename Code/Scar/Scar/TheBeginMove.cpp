#include "TheBeginMove.h"
#include "ICameraSceneNode.h"

TheBeginMove::TheBeginMove( vector3df thebeginpoint, vector3df theendpoint, u32 delay, u32 duration, int circle_n ):
TheBeginPoint( thebeginpoint ),TheEndPoint( theendpoint ),Duration( Duration ), Circle_N( circle_n ),Delay( delay ),
Begin( 0 )
{
	M_y =( TheEndPoint.Y - TheBeginPoint.Y ) / Duration;
	Distance = sqrt ( ( TheEndPoint.X - TheBeginPoint.X ) * ( TheEndPoint.X - TheBeginPoint.X ) + ( TheEndPoint.Z - TheBeginPoint.Z ) * ( TheEndPoint.Z - TheBeginPoint.Z ) );
	M_Distance = Distance / Duration;
	radian = 2 * PI * Circle_N / Duration;
	Center = TheEndPoint;
	Center.Y = TheBeginPoint.Y;
}

void TheBeginMove::animateNode( ISceneNode* node, u32 timeMs )
{
	if( Begin == 0 )
		Begin = timeMs + Delay;
	//��δ�ﵽ������ʼʱ��
	if( Begin > timeMs )
		return;

	u32 t;
	t = timeMs - Begin;	
	
	ICameraSceneNode* camera = static_cast<ICameraSceneNode*>(node);
	
	//���ﶯ������ʱ��
	if ( t > Duration )
	{
		//���Լ�ɾ��
		camera->removeAnimator(this);
		return;
	}
	camera -> setPosition( vector3df
		( Center.X + Distance - M_Distance * t * sin( radian ) , 
		Center.Y + M_y * t , 
		Center.Z + Distance - M_Distance * t * sin( radian ) ));
	camera ->setTarget(TheEndPoint);
}