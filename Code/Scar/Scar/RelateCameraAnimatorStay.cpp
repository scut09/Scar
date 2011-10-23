#include "RelateCameraAnimatorStay.h"


RelateCameraAnimatorStay::RelateCameraAnimatorStay( u32 delay, u32 duration, ICameraSceneNode* camera, vector3df position, bool loop )
	: Begin( 0 ), Delay( delay ), Duration( duration ), Camera( camera ), Position( position ), Loop( loop )
{

}

void RelateCameraAnimatorStay::animateNode( ISceneNode* node, u32 timeMs )
{
	if( Begin == 0 )
		Begin = timeMs + Delay;
	//��δ�ﵽ������ʼʱ��
	if( Begin > timeMs )
		return;

	node->setPosition( Camera->getPosition() + Position );

	//���ﶯ������ʱ��
	if ( timeMs - Begin > Duration )
	{
		if( Loop )
		{
			Begin = timeMs;
		}
		else
		{
			//���Լ�ɾ��
			node->removeAnimator(this);
		}
	}
}

ISceneNodeAnimator* RelateCameraAnimatorStay::createClone( ISceneNode* node, ISceneManager* newManager/*=0 */ )
{
	throw std::exception("The method or operation is not implemented.");
}
