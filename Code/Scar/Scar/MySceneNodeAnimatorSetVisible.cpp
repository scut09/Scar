#include "MySceneNodeAnimatorSetVisible.h"

MySceneNodeAnimatorSetVisible::MySceneNodeAnimatorSetVisible( u32 delay, u32 duration, bool isVisible )
	: Begin( 0 ), Delay( delay ), IsVisible( isVisible ), Duration( duration )
{

}

void MySceneNodeAnimatorSetVisible::animateNode( ISceneNode* node, u32 timeMs )
{
	if( Begin == 0 )
		Begin = timeMs + Delay;
	//还未达到动画开始时间
	if( Begin > timeMs )
		return;

	//到达动画结束时间
	if ( timeMs - Begin > Duration )
	{
		//设置节点的visible值
		node->setVisible( IsVisible );
		//把自己删掉
		node->removeAnimator(this);
		return;
	}
}

ISceneNodeAnimator* MySceneNodeAnimatorSetVisible::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	return new MySceneNodeAnimatorSetVisible( Delay, Duration, IsVisible );
}
