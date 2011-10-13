
#ifndef CSceneNodeAnimatorAutoTrack_h__
#define CSceneNodeAnimatorAutoTrack_h__


#include <irrlicht.h>

using namespace irr;
using namespace scene;



class CSceneNodeAnimatorAutoTrack : public scene::ISceneNodeAnimator
{
public:
	CSceneNodeAnimatorAutoTrack( ISceneManager* man ) : m_pSmgr( man )
	{}

	virtual void animateNode( scene::ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone(
		ISceneNode* node,
		ISceneManager* newManager = 0 )
	{
		return NULL;
	}

private:
	ISceneManager*		m_pSmgr;

//private:
//	core::vector3df Start;
//	core::vector3df End;
//	core::vector3df Vector;
//	f32 TimeFactor;
//	u32 StartTime;
//	u32 TimeForWay;
//
};


#endif // CSceneNodeAnimatorSelfDelFlyStraight_h__