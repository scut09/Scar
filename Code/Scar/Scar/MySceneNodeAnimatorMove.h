#ifndef MySceneNodeAnimatorMove_h__
#define MySceneNodeAnimatorMove_h__

/********************************************************************
	����ʱ��:	2011/10/24
	�ļ�����: 	K:\Users\Kid_shusang\Desktop\SCAR SVN\Code\Scar\Scar\MySceneNodeAnimatorMove.h
	����:		$������$
	
	����:		����������ֱ�ɶ���
*********************************************************************/
#include "ISceneNode.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

// ��������
enum AM_MOVE_TYPE
{
	AM_MT_LINER,			// ����
	AM_MT_LOG,				// ���� ��->��
};

class MySceneNodeAnimatorMove : public ISceneNodeAnimator
{
	u32 Begin;
	u32 Delay;
	u32 Duration;
	vector3df StartPos;
	vector3df EndPos;
	vector3df OffsetFactor;
	AM_MOVE_TYPE MoveType;
	f32 Factor;
	
public:
	MySceneNodeAnimatorMove( u32 delay, u32 duration, vector3df start, vector3df end, 
		AM_MOVE_TYPE moveType = AM_MT_LINER, f32 factor = 0 );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );

};

#endif // MySceneNodeAnimatorMove_h__
