#ifndef FireAnimator_h__
#define FireAnimator_h__

/********************************************************************
	��������:	2011/10/27
	�ļ���: 	C:\Users\Administrator\Desktop\����\SCAR��Ŀ��\opengl-scut\Code\Scar\Scar\FireAnimator.h
	����:		������
	
	����:		���Ʒɴ�����
*********************************************************************/

#include "ISceneNode.h"
#include <vector>
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class FireAnimator : public ISceneNodeAnimator
{
	bool IsFire;
	bool Initialized;
	std::vector<u32> LastTimes;
	ICameraSceneNode* Camera;

public:
	FireAnimator( ICameraSceneNode* camera );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );

	virtual bool OnEvent( const SEvent& event );

	static void AddBulletToScene( IWeapon* bullet, const vector3df& startPoint, const vector3df& endPoint, u32 timeMs );

};

#endif // FireAnimator_h__
