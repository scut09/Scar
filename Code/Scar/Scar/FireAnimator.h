#ifndef FireAnimator_h__
#define FireAnimator_h__

/********************************************************************
	��������:	2011/10/27
	�ļ���: 	C:\Users\Administrator\Desktop\����\SCAR��Ŀ��\opengl-scut\Code\Scar\Scar\FireAnimator.h
	����:		������
	
	����:		���Ʒɴ�����
*********************************************************************/

#include "ISceneNode.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class FireAnimator : public ISceneNodeAnimator
{
public:
	FireAnimator()
	{

	}

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );

};

#endif // FireAnimator_h__
