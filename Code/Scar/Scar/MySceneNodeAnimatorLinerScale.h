#ifndef MySceneNodeAnimatorLinerScale_h__
#define MySceneNodeAnimatorLinerScale_h__

#include "ISceneNode.h"
using namespace irr;
using namespace irr::scene;

class MySceneNodeAnimatorLinerScale : public ISceneNodeAnimator
{
	

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );

};

#endif // MySceneNodeAnimatorLinerScale_h__
