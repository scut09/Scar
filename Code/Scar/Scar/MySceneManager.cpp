#include "MySceneManager.h"
#include "MyIrrlichtEngine.h"
#include "Frigate.h"
#include "BulletNode.h"	
#include "AllAnimators.h"
#include "RunWay.h"

MySceneManager::MySceneManager()
{
	auto pEngine = MyIrrlichtEngine::GetEngine();
	smgr	= pEngine->GetSceneManager();
	driver	= pEngine->GetVideoDriver();
	timer	= pEngine->GetDevice()->getTimer();
}

ISceneNode* MySceneManager::getSceneNodeFromId( s32 id, ISceneNode* start/*=0*/ )
{
	return smgr->getSceneNodeFromId( id, start );
}

ISceneNode* MySceneManager::getSceneNodeFromName( const c8* name, ISceneNode* start/*=0*/ )
{
	return smgr->getSceneNodeFromName( name, start );
}

IAnimatedMesh* MySceneManager::getMesh( const std::wstring& filename )
{
	return smgr->getMesh( filename.c_str() );
}

ISceneNode* MySceneManager::getRootSceneNode()
{
	return smgr->getRootSceneNode();
}

IShip* MySceneManager::addFrigateSceneNode( const std::wstring& meshFileName, int id /*= -1 */ )
{
	IShip* ship = new CFrigate( smgr->getMesh( meshFileName.c_str() ), 0, smgr, id );
	return ship;
}

IWeapon* MySceneManager::addBulletSceneNode( const std::wstring& textureFileName, int velocity /*= 1000*/, u32 interval /*= 100 */ )
{
	IWeapon* bullet = new BulletNode( smgr );
	bullet->setMaterialTexture( 0, driver->getTexture( textureFileName.c_str() ) );
	bullet->SetVelocity( (f32)velocity );
	bullet->SetInterval( interval ); 

	return bullet;
}

IParticleSystemSceneNode* MySceneManager::addParticleSystemSceneNode( bool withDefaultEmitter/*=true*/, ISceneNode* parent/*=0*/, s32 id/*=-1*/, const core::vector3df& position /*= core::vector3df(0,0,0)*/, const core::vector3df& rotation /*= core::vector3df(0,0,0)*/, const core::vector3df& scale /*= core::vector3df(1.0f, 1.0f, 1.0f)*/ )
{
	return smgr->addParticleSystemSceneNode( withDefaultEmitter, parent, id, position, rotation, scale );
}

IBillboardSceneNode* MySceneManager::addBillboardSceneNode( ISceneNode* parent /*= 0*/, const core::dimension2d<f32>& size /*= core::dimension2d<f32>(10.0f, 10.0f)*/, const core::vector3df& position /*= core::vector3df(0,0,0)*/, s32 id/*=-1*/, video::SColor colorTop /*= 0xFFFFFFFF*/, video::SColor colorBottom /*= 0xFFFFFFFF*/ )
{
	return smgr->addBillboardSceneNode( parent, size, position, id, colorTop, colorBottom );
}

ISceneNode* MySceneManager::addSkyBoxSceneNode( video::ITexture* top, video::ITexture* bottom, video::ITexture* left, video::ITexture* right, video::ITexture* front, video::ITexture* back, ISceneNode* parent /*= 0*/, s32 id/*=-1*/ )
{
	return smgr->addSkyBoxSceneNode( top, bottom, left, right, front, back, parent, id );
}

ISceneNodeAnimator* MySceneManager::createRotationAnimator( const core::vector3df& rotationSpeed )
{
	return smgr->createRotationAnimator( rotationSpeed );
}

ISceneNodeAnimator* MySceneManager::createFlyStraightAnimator( const core::vector3df& startPoint, const core::vector3df& endPoint, u32 timeForWay, bool loop/*=false*/, bool pingpong /*= false*/ )
{
	return smgr->createFlyStraightAnimator( startPoint, endPoint, timeForWay, loop, pingpong );
}

ISceneNodeAnimator* MySceneManager::createTextureAnimator( const core::array<video::ITexture*>& textures, s32 timePerFrame, bool loop/*=true*/ )
{
	return smgr->createTextureAnimator( textures, timePerFrame, loop );
}

ISceneNodeAnimator* MySceneManager::createFlyCircleAnimator( const core::vector3df& center/*=core::vector3df(0.f,0.f,0.f)*/, f32 radius/*=100.f*/, f32 speed/*=0.001f*/, const core::vector3df& direction/*=core::vector3df(0.f, 1.f, 0.f)*/, f32 startPosition /*= 0.f*/, f32 radiusEllipsoid /*= 0.f*/ )
{
	return smgr->createFlyCircleAnimator( center, radius, speed, direction, startPosition, radiusEllipsoid );
}

ISceneNodeAnimator* MySceneManager::createDeleteAnimator( u32 timeMs )
{
	return smgr->createDeleteAnimator( timeMs );
}

ISceneNodeAnimatorCollisionResponse* MySceneManager::createCollisionResponseAnimator( ITriangleSelector* world, ISceneNode* sceneNode, const core::vector3df& ellipsoidRadius /*= core::vector3df(30,60,30)*/, const core::vector3df& gravityPerSecond /*= core::vector3df(0,-10.0f,0)*/, const core::vector3df& ellipsoidTranslation /*= core::vector3df(0,0,0)*/, f32 slidingValue /*= 0.0005f*/ )
{
	return smgr->createCollisionResponseAnimator( world, sceneNode, ellipsoidRadius, gravityPerSecond, ellipsoidTranslation, slidingValue );
}

ISceneNodeAnimator* MySceneManager::createFollowSplineAnimator( s32 startTime, const core::array< core::vector3df >& points, f32 speed /*= 1.0f*/, f32 tightness /*= 0.5f*/, bool loop/*=true*/, bool pingpong/*=false*/ )
{
	return smgr->createFollowSplineAnimator( startTime, points, speed, tightness, loop, pingpong );
}

ISceneNodeAnimator* MySceneManager::createSelfDelFlyStraightAnimator( const core::vector3df& startPoint, const core::vector3df& endPoint, u32 timeForWay )
{
	ISceneNodeAnimator* animator = new CSceneNodeAnimatorSelfDelFlyStraight( 
		startPoint, endPoint, timeForWay, timer->getTime() );
	return animator;
}

ISceneNodeAnimator* MySceneManager::createAutoTrackAnimator( ISceneNode* target )
{
	ISceneNodeAnimator* animator = new CSceneNodeAnimatorAutoTrack( smgr );
	return animator;
}

ISceneNodeAnimator* MySceneManager::createScaleAnimator( u32 delay, u32 duration, vector3df scale, AS_MOVE_TYPE type /*= AS_MT_LINER*/, f32 factor /*= 0 */ )
{
	ISceneNodeAnimator* animator = new MySceneNodeAnimatorScale( delay, duration, scale, type, factor );
	return animator;
}

ISceneNodeAnimator* MySceneManager::createShakeAnimatorAnimator( u32 delay, u32 duration, f32 ampFrom, f32 ampTo /*= 0 */ )
{
	ISceneNodeAnimator* animator = new MySceneNodeAnimatorShake( delay, duration, ampFrom, ampTo );
	return animator;
}

ISceneNodeAnimator* MySceneManager::createRelateCameraStayAnimator( u32 delay, u32 duration, ICameraSceneNode* camera, vector3df position, bool loop /*= true */ )
{
	ISceneNodeAnimator* animator = new RelateCameraAnimatorStay( delay, duration, camera, position, loop );
	return animator;
}

ISceneNodeAnimator* MySceneManager::createTheBeginMoveAnimator( vector3df thebeginpoint, vector3df theendpoint, u32 delay, u32 duration, int circle_n )
{
	ISceneNodeAnimator* animator = new TheBeginMove( thebeginpoint, theendpoint, delay, duration, circle_n );
	return animator;
}

ITexture* MySceneManager::getTexture( const std::wstring& filename )
{
	return driver->getTexture( filename	.c_str() );
}

ISceneNode* MySceneManager::addRunWaySceneNode( const core::vector3df& position /*= core::vector3df( 0 )*/,
	f32 interval /*= 200*/, f32 width /*= 300*/,
	const core::vector3df& colorFrom /*= core::vector3df( 0, 63, 255 )*/, const core::vector3df& colorTo /*= core::vector3df( 255, 255, 0 )*/,
	s32 numOfArrows /*= 15 */ )
{
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	ISceneManager* smgr = pEngine->GetSceneManager();
	IVideoDriver* driver = pEngine->GetVideoDriver();
	u32 TimeMs = pEngine->GetDevice()->getTimer()->getTime();
	f32 delay = 100;

	// 跑道根节点
	ISceneNode* runWay = smgr->addEmptySceneNode();
	runWay->setPosition( position );
	// 供复制的节点
	ISceneNode* node = smgr->addMeshSceneNode( smgr->getMesh( "../media/UnitModel/UnitPlane.obj" ), runWay );
	node->setScale( vector3df( 90, 176, 1 ) );
	node->setRotation( vector3df( 0, 45, 0 ) );
	node->setMaterialTexture( 0, driver->getTexture( "../media/UIResource/Game/arrow.png" ) );
	node->setMaterialFlag( EMF_BACK_FACE_CULLING, false );
	// 节点临时变量
	ISceneNode* copy;
	// Shader
	SceneNodeShader shader;
	// 色彩偏移量
	vector3df colorOffset = ( colorTo - colorFrom ) / (f32)numOfArrows;
	// 右跑道
	for( int i=0; i<numOfArrows; i++ )
	{
		copy = node->clone();
		copy->setPosition( vector3df( width / 2.f, 0, interval * i ) );
		RunWayBlink* ani = new RunWayBlink( (u32)(delay * i), (f32)i, colorFrom, colorOffset );
		copy->addAnimator( ani );
		ani->drop();
	}
	node->setRotation( vector3df( 0, 45, 180 ) );
	// 左跑道
	for( int i=0; i<numOfArrows; i++ )
	{
		copy = node->clone();
		copy->setPosition( vector3df( -width / 2.f, 0, interval * i ) );
		RunWayBlink* ani = new RunWayBlink( (u32)(delay * i), (f32)i, colorFrom, colorOffset );
		copy->addAnimator( ani );
		ani->drop();
	}
	node->setVisible( false );

	return runWay;
	//return CreateRunWay( position, interval, width, colorFrom, colorTo, numOfArrows );
}

ISceneNode* MySceneManager::addSphereSceneNode( f32 radius/*=5.0f*/, s32 polyCount/*=16*/, ISceneNode* parent/*=0*/, s32 id/*=-1*/, const core::vector3df& position /*= core::vector3df(0,0,0)*/, const core::vector3df& rotation /*= core::vector3df(0,0,0)*/, const core::vector3df& scale /*= core::vector3df(1.0f, 1.0f, 1.0f)*/ )
{
	return smgr->addSphereSceneNode( radius, polyCount, parent, id, position, rotation, scale );
}

IMeshSceneNode* MySceneManager::addMeshSceneNode( IMesh* mesh, ISceneNode* parent/*=0*/, s32 id/*=-1*/, const core::vector3df& position /*= core::vector3df(0,0,0)*/, const core::vector3df& rotation /*= core::vector3df(0,0,0)*/, const core::vector3df& scale /*= core::vector3df(1.0f, 1.0f, 1.0f)*/, bool alsoAddIfMeshPointerZero/*=false*/ )
{
	return smgr->addMeshSceneNode( mesh, parent, id, position, rotation, scale, alsoAddIfMeshPointerZero );
}

IAnimatedMeshSceneNode* MySceneManager::addAnimatedMeshSceneNode( IAnimatedMesh* mesh, ISceneNode* parent/*=0*/, s32 id/*=-1*/, const core::vector3df& position /*= core::vector3df(0,0,0)*/, const core::vector3df& rotation /*= core::vector3df(0,0,0)*/, const core::vector3df& scale /*= core::vector3df(1.0f, 1.0f, 1.0f)*/, bool alsoAddIfMeshPointerZero/*=false*/ )
{
	return smgr->addAnimatedMeshSceneNode( mesh, parent, id, position, rotation, scale, alsoAddIfMeshPointerZero );
}
