#ifndef MySceneNodeAnimatorSetVisible_h__
#define MySceneNodeAnimatorSetVisible_h__

/********************************************************************
	��������:	2011/10/22
	�ļ���: 	C:\Users\Administrator\Desktop\����\SCAR��Ŀ��\opengl-scut\Code\Scar\Scar\MySceneNodeAnimatorSetVisible.h
	����:		������
	
	����:		��ʱ����Visible���Զ���
				һ��ʱ���ı�Ŀ��Visible������
*********************************************************************/

#include "ISceneNode.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class MySceneNodeAnimatorSetVisible : public ISceneNodeAnimator
{
	u32 Begin;
	u32 Delay;
	u32 Duration;
	bool IsVisible;
	
public:
	MySceneNodeAnimatorSetVisible( u32 delay, u32 duration, bool isVisible );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );

};

#endif // MySceneNodeAnimatorSetVisible_h__
