#ifndef MySceneManager_h__
#define MySceneManager_h__

#include <irrlicht.h>

using namespace irr;
using scene::ISceneNode;
using scene::ISceneNodeAnimator;

class MySceneManager
{
	scene::ISceneManager*	smgr;

public:
	MySceneManager();

	ISceneNode*	add();

	ISceneNode* addFrigateSceneNode()
	{

	}

	ISceneNode* addMissleSceneNode()
	{

	}

	ISceneNode* addBulletSceneNode()
	{

	}

	ISceneNodeAnimator* createFireAnimator()
	{

	}

	ISceneNodeAnimator* createCallbackCollsionResponseAnimator()
	{

	}

	ISceneNodeAnimator* createSelfDelFlyStraightAnimator()
	{

	}

	ISceneNodeAnimator* createAutoTrackAnimator()
	{

	}

	ISceneNodeAnimator* createFollowFlameAnimator()
	{

	}

	ISceneNodeAnimator* createScaleAnimator()
	{

	}

	ISceneNodeAnimator* createShakeAnimatorAnimator()
	{

	}

	ISceneNodeAnimator* createRelateCameraMoveAnimator()
	{

	}

	ISceneNodeAnimator* createRelateCameraStayAnimator()
	{

	}

	ISceneNodeAnimator* createTheBeginMoveAnimator()
	{

	}

};

#endif // MySceneManager_h__