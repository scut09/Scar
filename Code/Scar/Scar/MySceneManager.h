#ifndef MySceneManager_h__
#define MySceneManager_h__

#include <irrlicht.h>
#include "AllAnimators.h"
#include "Frigate.h"
#include "BulletNode.h"

using namespace irr;
using scene::ISceneNode;
using scene::ISceneNodeAnimator;

class MySceneManager
{
	scene::ISceneManager*	smgr;
	video::IVideoDriver*	driver;
	ITimer*					timer;

public:
	MySceneManager();

	ISceneNode* addFrigateSceneNode( wchar_t* meshFileName, int id = -1 )
	{
		ISceneNode* node = new CFrigate( smgr->getMesh( meshFileName ), 0, smgr, id );
		return node;
	}

	IWeapon* addBulletSceneNode( wchar_t* textureFileName, int velocity = 1000, u32 interval = 100 )
	{
		IWeapon* bullet = new BulletNode( smgr );
		bullet->setMaterialTexture( 0, driver->getTexture( textureFileName ) );
		bullet->SetVelocity( (f32)velocity );
		bullet->SetInterval( interval ); 

		return bullet;
	}

	ISceneNodeAnimator* createFireAnimator()
	{
		ISceneNodeAnimator* animator = new FireAnimator( smgr->getActiveCamera() );
		return animator;
	}

	// 内部使用，不导出
	//ISceneNodeAnimator* createCallbackCollsionResponseAnimator()
	//{
	//}

	ISceneNodeAnimator* createSelfDelFlyStraightAnimator( const core::vector3df& startPoint,
		const core::vector3df& endPoint, u32 timeForWay )
	{
		
		ISceneNodeAnimator* animator = new CSceneNodeAnimatorSelfDelFlyStraight( 
			startPoint, endPoint, timeForWay, timer->getTime() );
		return animator;
	}

	ISceneNodeAnimator* createAutoTrackAnimator()
	{
		ISceneNodeAnimator* animator = new CSceneNodeAnimatorAutoTrack( smgr );
		return animator;
	}

	ISceneNodeAnimator* createFollowFlameAnimator()
	{
		ISceneNodeAnimator* animator = new Chuoyanshuxing( smgr );
		return animator;
	}

	ISceneNodeAnimator* createScaleAnimator( u32 delay, u32 duration, vector3df scale, 
		AS_MOVE_TYPE type = AS_MT_LINER, f32 factor = 0 )
	{
		ISceneNodeAnimator* animator = new MySceneNodeAnimatorScale( delay, duration, scale, type, factor );
		return animator;
	}

	ISceneNodeAnimator* createShakeAnimatorAnimator( u32 delay, u32 duration, f32 ampFrom, f32 ampTo = 0 )
	{
		ISceneNodeAnimator* animator = new MySceneNodeAnimatorShake( delay, duration, ampFrom, ampTo );
		return animator;
	}

	ISceneNodeAnimator* createRelateCameraMoveAnimator( u32 delay, u32 duration, ICameraSceneNode* camera, 
		vector3df start, vector3df end, RM_MOVE_TYPE moveType = RM_MT_LINER, f32 factor = 0 )
	{
		ISceneNodeAnimator* animator = new RelateCameraAnimatorMove( delay, duration, camera, start, end, moveType, factor );
		return animator;
	}

	ISceneNodeAnimator* createRelateCameraStayAnimator( u32 delay, u32 duration, ICameraSceneNode* camera, vector3df position, bool loop = true )
	{
		ISceneNodeAnimator* animator = new RelateCameraAnimatorStay( delay, duration, camera, position, loop );
		return animator;
	}

	ISceneNodeAnimator* createTheBeginMoveAnimator( vector3df thebeginpoint, vector3df theendpoint,
		u32 delay, u32 duration, int circle_n )
	{
		ISceneNodeAnimator* animator = new TheBeginMove( thebeginpoint, theendpoint, delay, duration, circle_n );
		return animator;
	}

};

#endif // MySceneManager_h__