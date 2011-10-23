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
	//��δ�ﵽ������ʼʱ��
	if( Begin > timeMs )
		return;

	//���ﶯ������ʱ��
	if ( timeMs - Begin > Duration )
	{
		//ִ�к���
		Func();
		//���Լ�ɾ��
		node->removeAnimator(this);
		return;
	}
}

ISceneNodeAnimator* MySceneNodeAnimatorCallFunc::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	throw std::exception("The method or operation is not implemented.");
}
