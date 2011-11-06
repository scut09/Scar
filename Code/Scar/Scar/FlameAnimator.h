#ifndef FlameAnimator_h__
#define FlameAnimator_h__

/********************************************************************
	创建时间:	2011/11/06
	文件名称: 	K:\Users\Kid_shusang\Desktop\SCAR SVN\Code\Scar\Scar\FlameAnimator.h
	作者:		$屠文翔$
	
	描述:		飞船尾焰大小会随着飞船速度变化而变化
				仅供SpriteFlame类使用
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
