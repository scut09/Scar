#ifndef FlameAnimator_h__
#define FlameAnimator_h__

/********************************************************************
	����ʱ��:	2011/11/06
	�ļ�����: 	K:\Users\Kid_shusang\Desktop\SCAR SVN\Code\Scar\Scar\FlameAnimator.h
	����:		$������$
	
	����:		�ɴ�β���С�����ŷɴ��ٶȱ仯���仯
				����SpriteFlame��ʹ��
*********************************************************************/

#include "ISceneNode.h"
#include "IShip.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class FlameAnimator : public ISceneNodeAnimator
{
	IShip* Ship;
	vector3df Offset;

public:
	FlameAnimator( IShip* ship, vector3df offset );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );

};

#endif // FlameAnimator_h__
