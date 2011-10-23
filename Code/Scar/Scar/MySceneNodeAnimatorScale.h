#ifndef MySceneNodeAnimatorScale_h__
#define MySceneNodeAnimatorScale_h__

/********************************************************************
	��������:	2011/10/22
	�ļ���: 	C:\Users\Administrator\Desktop\����\SCAR��Ŀ��\opengl-scut\Code\Scar\Scar\MySceneNodeAnimatorScale.h
	����:		������
	
	����:		ͨ�������Ŷ���
				ʹ�ñ�־λ�����ֻ�������
*********************************************************************/

#include "ISceneNode.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

// ��������
enum MOVE_TYPE
{
	MT_LINER,			// ����
	MT_LOG,				// ���� ��->��
	MT_SQUARE,			// ƽ�� ��->��
	MT_SQRT,			// ���� ��->��
	MT_POW				// ָ�� ����ָ���Ե�������
};

class MySceneNodeAnimatorScale : public ISceneNodeAnimator
{
	u32 Begin;						// ��ʼʱ��
	u32 Delay;						// �ӳ�����ʱ��
	u32 Duration;					// ����ʱ��
	vector3df Origin;				// ԭʼ����
	vector3df Scale;				// ��������
	vector3df ScaleFactor;			// ��������
	MOVE_TYPE MoveType;				// ��������
	f32 Factor;						// ����ϵ��	

public:

	MySceneNodeAnimatorScale( u32 delay, u32 duration, vector3df scale, MOVE_TYPE type = MT_LINER, f32 factor = 0 );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );



};
#endif // MySceneNodeAnimatorScale_h__
