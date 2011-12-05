#ifndef FireAnimator_h__
#define FireAnimator_h__

/********************************************************************
	��������:	2011/10/27
	�ļ���: 	C:\Users\Administrator\Desktop\����\SCAR��Ŀ��\opengl-scut\Code\Scar\Scar\FireAnimator.h
	����:		������
	
	����:		���Ʒɴ�����
*********************************************************************/

#include <boost/smart_ptr.hpp>
#include "ISceneNode.h"
#include "CSceneNodeAnimatorCollisionResponse.h"
#include <vector>
#include "IClient.h"
#include "IShip.h"

using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class ShipFireAnimator : public ISceneNodeAnimator
{
	bool IsFire;
	bool Initialized;
	IBillboardSceneNode*	BulletHit;				//�ӵ�����ʱ�Ļ�⶯��
	std::vector<u32>		LastTimes;
	boost::shared_ptr<Network::IClient>		Client;

public:
	ShipFireAnimator( boost::shared_ptr<Network::IClient> client );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual bool isEventReceiverEnabled() const
	{
		return true;
	}

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );

	virtual bool OnEvent( const SEvent& event );

	void AddBulletToScene( IWeapon* bullet, const vector3df& startPoint, const vector3df& endPoint, u32 timeMs );

};

#endif // FireAnimator_h__
