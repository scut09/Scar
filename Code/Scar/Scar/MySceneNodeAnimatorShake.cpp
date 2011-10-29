#include "MySceneNodeAnimatorShake.h"
#include <iostream>
#include "ICameraSceneNode.h"

MySceneNodeAnimatorShake::MySceneNodeAnimatorShake( u32 delay, u32 duration, f32 ampFrom, f32 ampTo )
	: Begin( 0 ), Delay( delay ), Duration( duration ), AmpFrom( ampFrom), AmpTo( ampTo )
{
	AmpFactor = ( AmpTo - AmpFrom ) / (f32)duration;
}

void MySceneNodeAnimatorShake::animateNode( ISceneNode* node, u32 timeMs )
{
	if( Begin == 0 )
		Begin = timeMs + Delay;
	//还未达到动画开始时间
	if( Begin > timeMs )
		return;

	ICameraSceneNode* camera = static_cast<ICameraSceneNode*>(node);

	u32 t = timeMs - Begin;

	srand( timeMs );
	f32 Amplitude = AmpFrom + AmpFactor * t;
	s32 mul100 = (s32)(Amplitude * 100);
	if ( mul100 == 0 )
	{
		//把自己删掉
		camera->removeAnimator(this);
		return;
	}
	f32 half = Amplitude / 2.0f;
	f32 sX = ( rand() % mul100 ) / 100.0f - half;
	f32 sY = ( rand() % mul100 ) / 100.0f - half;
	if( sX >100 ) sX = 0;	// 为了解决莫名其妙的超大数
	if( sY >100 ) sY = 0;
	sX /= 100;
	sY /= 100;
	vector3df shake = vector3df( sX, sY, 0 );
	camera -> setTarget( camera -> getTarget() + shake );

	//到达动画结束时间
	if ( timeMs - Begin > Duration )
	{
		//把自己删掉
		camera->removeAnimator(this);
		return;
	}
}

ISceneNodeAnimator* MySceneNodeAnimatorShake::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	return new MySceneNodeAnimatorShake(Delay, Duration, AmpFrom, AmpTo);
}

