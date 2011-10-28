#ifndef SceneNodeAnimatorFollow_h__
#define SceneNodeAnimatorFollow_h__

/********************************************************************
	��������:	2011/10/27
	�ļ���: 	C:\Users\Administrator\Desktop\����\SCAR��Ŀ��\opengl-scut\Code\Scar\Scar\SceneNodeAnimatorFollow.h
	����:		������
	
	����:		��һ��ȷ���ľ����ϸ����ƶ�Ŀ���˶�
*********************************************************************/

#include "ISceneNode.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class SceneNodeAnimatorFollow : public ISceneNodeAnimator
{
	ISceneNode* Target;		// �����Ŀ��
	f32 Distance;			// ���ֵľ���

public:
	SceneNodeAnimatorFollow( ISceneNode* tar, f32 distance = 0 );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );

};

#endif // SceneNodeAnimatorFollow_h__
