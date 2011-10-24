#ifndef RelateCameraAnimatorMove_h__
#define RelateCameraAnimatorMove_h__

/********************************************************************
	��������:	2011/10/23
	�ļ���: 	C:\Users\Administrator\Desktop\����\SCAR��Ŀ��\opengl-scut\Code\Scar\Scar\RelateCameraAnimatorMove.h
	����:		������
	
	����:		��Ծ�ͷ�˶�����
				��һ���˶�����һ��
*********************************************************************/

#include "ICameraSceneNode.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

// ��������
enum RM_MOVE_TYPE
{
	RM_MT_LINER,			// ����
	RM_MT_LOG,				// ���� ��->��
};

class RelateCameraAnimatorMove : public ISceneNodeAnimator
{
	u32 Begin;
	u32 Delay;
	u32 Duration;
	ICameraSceneNode* Camera;
	vector3df StartPos;
	vector3df EndPos;
	vector3df OffsetFactor;
	RM_MOVE_TYPE MoveType;
	f32 Factor;
	//bool Loop;

public:
	RelateCameraAnimatorMove( u32 delay, u32 duration, ICameraSceneNode* camera, vector3df start, vector3df end, 
		RM_MOVE_TYPE moveType = RM_MT_LINER, f32 factor = 0 );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );

};

#endif // RelateCameraAnimatorMove_h__
