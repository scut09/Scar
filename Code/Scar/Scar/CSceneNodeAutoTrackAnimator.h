
#ifndef CSceneNodeAnimatorAutoTrack_h__
#define CSceneNodeAnimatorAutoTrack_h__


#include <irrlicht.h>
#include "Flame.h"

using namespace irr;
using namespace scene;



class CSceneNodeAnimatorAutoTrack : public scene::ISceneNodeAnimator
{
public:
	CSceneNodeAnimatorAutoTrack( ISceneNode* target )
	{
		isfirsttime = 1;
		lasttime = 0;
		t_sum = 0;
		maxspeed = 0.6f;
		inertia = 0.8f;
		max_a = 0.3f;
		max_range = 10000000.f;
		max_t = 10000;
		TimeForWay = 30;
		missle_speed = core::vector3df( 1, 1, 1 );
		Target = target;
	}

	virtual void animateNode( scene::ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager = 0 )
	{
		return NULL;
	}

private:
	ISceneManager*	m_pSmgr;
	ISceneNode*		Target;
	u32 isfirsttime;
	u32 lasttime;
	u32	t_sum;
 	core::vector3df missle_speed;	//�����ٶ�
	f32 maxspeed;					//����ٶ�
	f32 inertia;					//����Ȩֵ
	f32 max_a;						//�����ٶ�
	f32 max_range;					//�����������Χ
	f32 max_yinbao;					//��������
	u32 max_t;						//��������
	u32 TimeForWay;					//֡���ʱ�����ɷ��е����ʱ��
};


#endif // CSceneNodeAnimatorSelfDelFlyStraight_h__