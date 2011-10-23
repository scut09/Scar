#include "MySceneNodeAnimatorSetVisible.h"

MySceneNodeAnimatorSetVisible::MySceneNodeAnimatorSetVisible( u32 delay, u32 duration, bool isVisible )
	: Begin( 0 ), Delay( delay ), IsVisible( isVisible ), Duration( duration )
{

}

void MySceneNodeAnimatorSetVisible::animateNode( ISceneNode* node, u32 timeMs )
{
	if( Begin == 0 )
		Begin = timeMs + Delay;
	//��δ�ﵽ������ʼʱ��
	if( Begin > timeMs )
		return;

	//���ﶯ������ʱ��
	if ( timeMs - Begin > Duration )
	{
		//���ýڵ��visibleֵ
		node->setVisible( IsVisible );
		//���Լ�ɾ��
		node->removeAnimator(this);
		return;
	}
}

ISceneNodeAnimator* MySceneNodeAnimatorSetVisible::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	return new MySceneNodeAnimatorSetVisible( Delay, Duration, IsVisible );
}
