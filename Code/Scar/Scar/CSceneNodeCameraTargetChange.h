#ifndef CSceneNodeCameraTargetChange_h_
#define CSceneNodeCameraTargetChange_h_

/********************************************************************
	��������:	2011/11/21
	�ļ���: 		CSceneNodeCameraTargetChange.h
	����:		�����
	����:		��������򽥱䶯��
*********************************************************************/

#include "ICameraSceneNode.h"
#include "ISceneNode.h"

using namespace irr;
using namespace irr::core;
using namespace irr::scene;

// ��������
enum AS_MOVE_TYPE
{
	AS_MT_LINER,			// ����
	AS_MT_LOG,				// ���� ��->��
	AS_MT_SQUARE,			// ƽ�� ��->��
	AS_MT_SQRT,			// ���� ��->��
	AS_MT_POW				// ָ�� ����ָ���Ե�������
};

class CSceneNodeCameraTargetChange : public ISceneNodeAnimator
{
	u32 Begin;						// ��ʼʱ��
	u32 Delay;						// �ӳ�����ʱ��
	u32 Duration;					// ����ʱ��
	vector3df OriginTatget;				// ԭʼ����
	vector3df Target;				// ��������
	vector3df ChangeFactor;			// ��������
	AS_MOVE_TYPE MoveType;				// ��������
	f32 Factor;						// ����ϵ��	

public:

	CSceneNodeCameraTargetChange( u32 delay, u32 duration, vector3df newtarget, AS_MOVE_TYPE type = AS_MT_LINER, f32 factor = 0 );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );



};
#endif // CSceneNodeCameraTargetChange_h_
