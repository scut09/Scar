#include "MySceneNodeAnimatorCallFunc.h"

MySceneNodeAnimatorCallFunc::MySceneNodeAnimatorCallFunc( u32 delay, u32 duration )
	: Begin( 0 ), Delay( delay ), Duration( duration )
{
	Func = [](){};
}

void MySceneNodeAnimatorCallFunc::animateNode( ISceneNode* node, u32 timeMs )
{
	if( Begin == 0 )
		Begin = timeMs + Delay;
	//还未达到动画开始时间
	if( Begin > timeMs )
		return;

	//到达动画结束时间
	if ( timeMs - Begin > Duration )
	{
		//执行函数
		Func();
		//把自己删掉
		node->removeAnimator(this);
		return;
	}
}

ISceneNodeAnimator* MySceneNodeAnimatorCallFunc::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	throw std::exception("The method or operation is not implemented.");
}
