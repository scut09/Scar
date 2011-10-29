#ifndef MySceneNodeAnimatorShake_h__
#define MySceneNodeAnimatorShake_h__

/********************************************************************
	��������:	2011/10/23
	�ļ���: 	C:\Users\Administrator\Desktop\����\SCAR��Ŀ��\opengl-scut\Code\Scar\Scar\MySceneNodeAnimatorShake.h
	����:		������
	
	����:		����Ļ�е�Ϊ���Ļ��涶������
				������ƽ������
*********************************************************************/

#include "ISceneNode.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class MySceneNodeAnimatorShake : public ISceneNodeAnimator
{
	u32 Begin;
	u32 Delay;
	u32 Duration;
	vector3df Origin;			// �����ԭʼ�Ƕ�
	vector3df LastOffset;		// �ϴζ����ı�Ƕ�
	f32 AmpFrom;				// ��� �Ƕ�
	f32 AmpTo;					// ��� �Ƕ�
	f32 AmpFactor;				
	
	
public:
	MySceneNodeAnimatorShake( u32 delay, u32 duration, f32 ampFrom, f32 ampTo = 0 );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager/*=0*/ );

};


#endif // MySceneNodeAnimatorShake_h__
