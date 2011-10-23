#ifndef RelateCameraAnimatorStay_h__
#define RelateCameraAnimatorStay_h__

/********************************************************************
	��������:	2011/10/23
	�ļ���: 	C:\Users\Administrator\Desktop\����\SCAR��Ŀ��\opengl-scut\Code\Scar\Scar\RelateCameraAnimatorStay.h
	����:		������
	
	����:		������Ծ�ͷ��ֹ
*********************************************************************/

#include "ICameraSceneNode.h"

using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class RelateCameraAnimatorStay : public ISceneNodeAnimator
{
	u32 Begin;
	u32 Delay;
	u32 Duration;
	ICameraSceneNode* Camera;
	vector3df Position;
	bool Loop;

public:
	RelateCameraAnimatorStay( u32 delay, u32 duration, ICameraSceneNode* camera, vector3df position, bool loop = true );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );


};

#endif // RelateCameraAnimatorStay_h__
