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

class CSceneNodeCameraTargetChange : public ISceneNodeAnimator
{
	u32 Begin;						// ��ʼʱ��
	u32 Delay;						// �ӳ�����ʱ��
	u32 Duration;					// ����ʱ��
	vector3df OriginTarget;			// ԭʼTarget
	vector3df NewTarget;			// ��Target
	vector3df ChangeFactor;			// ��������
	bool IsFirst;						// �Ƿ��Ѿ���ʼ��

public:

	CSceneNodeCameraTargetChange( u32 delay, u32 duration, vector3df newtarget );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );



};
#endif // CSceneNodeCameraTargetChange_h_
