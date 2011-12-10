#ifndef MissleFireAnimator_h__
#define MissleFireAnimator_h__

#include <boost/smart_ptr.hpp>
#include "ISceneNode.h"
#include "CSceneNodeAnimatorCollisionResponse.h"
#include <vector>
#include "IClient.h"
#include "IShip.h"
#include "MissleNode.h"

using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class MissleFireAnimator : public ISceneNodeAnimator
{
	bool IsFire;
	bool Initialized;
	std::vector<u32>		LastTimes;
	boost::shared_ptr<Network::IClient>		Client;

public:
	MissleFireAnimator( boost::shared_ptr<Network::IClient> client );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual bool isEventReceiverEnabled() const
	{
		return true;
	}

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );

	virtual bool OnEvent( const SEvent& event );

	void AddMissleToScene( MissleNode* missle );

};
#endif // MissleFireAnimator_h__
