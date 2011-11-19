#ifndef MySceneManager_h__
#define MySceneManager_h__

#include <irrlicht.h>
#include "IUIAnimator.h"
#include <string>
#include "IShip.h"
#include "RelateCameraAnimatorMove.h"
#include "MySceneNodeAnimatorScale.h"

using namespace irr;
using scene::ISceneNode;
using scene::ISceneNodeAnimator;
using scene::IAnimatedMesh;

class MySceneManager
{
	scene::ISceneManager*	smgr;
	video::IVideoDriver*	driver;
	ITimer*					timer;

public:
	MySceneManager();

	/************************************************************************/
	/* 常用工具函数                                                          */
	/************************************************************************/
	ISceneNode* getSceneNodeFromId(s32 id, ISceneNode* start=0);

	ISceneNode* getSceneNodeFromName(const c8* name, ISceneNode* start=0);

	IAnimatedMesh* getMesh(const std::wstring& filename);

	ISceneNode* getRootSceneNode();

	ITexture* getTexture( const std::wstring& filename );

	/************************************************************************/
	/* 添加场景节点函数群                                                     */
	/************************************************************************/
	// 添加护卫舰
	IShip* addFrigateSceneNode( const std::wstring& meshFileName, int id = -1 );

	// 添加炮弹节点
	IWeapon* addBulletSceneNode( const std::wstring& textureFileName, int velocity = 1000, u32 interval = 100 );

	// 添加粒子发射器
	IParticleSystemSceneNode* addParticleSystemSceneNode(
		bool withDefaultEmitter=true, ISceneNode* parent=0, s32 id=-1,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f));

	// 布告板Billboard
	IBillboardSceneNode* addBillboardSceneNode(ISceneNode* parent = 0,
		const core::dimension2d<f32>& size = core::dimension2d<f32>(10.0f, 10.0f),
		const core::vector3df& position = core::vector3df(0,0,0), s32 id=-1,
		video::SColor colorTop = 0xFFFFFFFF, video::SColor colorBottom = 0xFFFFFFFF);

	// 天空盒
	ISceneNode* addSkyBoxSceneNode(video::ITexture* top, video::ITexture* bottom,
		video::ITexture* left, video::ITexture* right, video::ITexture* front,
		video::ITexture* back, ISceneNode* parent = 0, s32 id=-1);

	// 起飞跑道
	ISceneNode* addRunWaySceneNode( const core::vector3df& position = core::vector3df( 0 ),
		f32 interval = 200, f32 width = 300,
		const core::vector3df& colorFrom = core::vector3df( 0, 63, 255 ), const core::vector3df& colorTo = core::vector3df( 255, 255, 0 ),
		s32 numOfArrows = 15 );

	// 球体
	ISceneNode* addSphereSceneNode(f32 radius=5.0f, s32 polyCount=16,
		ISceneNode* parent=0, s32 id=-1,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f));

	// 加载Mesh节点
	IMeshSceneNode* addMeshSceneNode(IMesh* mesh, ISceneNode* parent=0, s32 id=-1,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f),
		bool alsoAddIfMeshPointerZero=false);

	// 加载AnimatedMesh节点
	IAnimatedMeshSceneNode* addAnimatedMeshSceneNode(IAnimatedMesh* mesh,
		ISceneNode* parent=0, s32 id=-1,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f),
		bool alsoAddIfMeshPointerZero=false);

	/************************************************************************/
	/* 动画Animator                                                         */
	/************************************************************************/

	// 旋转动画
	ISceneNodeAnimator* createRotationAnimator(const core::vector3df& rotationSpeed);

	// 绕远飞行动画
	ISceneNodeAnimator* createFlyCircleAnimator(
		const core::vector3df& center=core::vector3df(0.f,0.f,0.f),
		f32 radius=100.f, f32 speed=0.001f,
		const core::vector3df& direction=core::vector3df(0.f, 1.f, 0.f),
		f32 startPosition = 0.f,
		f32 radiusEllipsoid = 0.f);

	// 直线飞行动画
	ISceneNodeAnimator* createFlyStraightAnimator(const core::vector3df& startPoint,
		const core::vector3df& endPoint, u32 timeForWay, bool loop=false, bool pingpong = false);

	// 材质改变动画
	ISceneNodeAnimator* createTextureAnimator(const core::array<video::ITexture*>& textures,
		s32 timePerFrame, bool loop=true);

	// 延迟移除节点动画
	ISceneNodeAnimator* createDeleteAnimator(u32 timeMs);

	// 碰撞反应动画
	ISceneNodeAnimatorCollisionResponse* createCollisionResponseAnimator(
		ITriangleSelector* world, ISceneNode* sceneNode,
		const core::vector3df& ellipsoidRadius = core::vector3df(30,60,30),
		const core::vector3df& gravityPerSecond = core::vector3df(0,-10.0f,0),
		const core::vector3df& ellipsoidTranslation = core::vector3df(0,0,0),
		f32 slidingValue = 0.0005f);

	// 沿线飞行动画
	ISceneNodeAnimator* createFollowSplineAnimator(s32 startTime,
		const core::array< core::vector3df >& points,
		f32 speed = 1.0f, f32 tightness = 0.5f, bool loop=true, bool pingpong=false);

	// 直线飞行动画，做完后将自己从节点中移除
	ISceneNodeAnimator* createSelfDelFlyStraightAnimator( const core::vector3df& startPoint,
		const core::vector3df& endPoint, u32 timeForWay );

	// 自动跟踪动画
	ISceneNodeAnimator* createAutoTrackAnimator( ISceneNode* target );

	// 尾焰动画
	ISceneNodeAnimator* createFollowFlameAnimator()
	{
		ISceneNodeAnimator* animator = 0;//= new Chuoyanshuxing( smgr );
		return animator;
	}

	// 缩放动画
	ISceneNodeAnimator* createScaleAnimator( u32 delay, u32 duration, vector3df scale, 
		AS_MOVE_TYPE type = AS_MT_LINER, f32 factor = 0 );

	// 晃动动画
	ISceneNodeAnimator* createShakeAnimatorAnimator( u32 delay, u32 duration, f32 ampFrom, f32 ampTo = 0 );
	// 相对摄像机移动动画
	ISceneNodeAnimator* createRelateCameraMoveAnimator( u32 delay, u32 duration, ICameraSceneNode* camera, 
		vector3df start, vector3df end, RM_MOVE_TYPE moveType = RM_MT_LINER, f32 factor = 0 )
	{
		ISceneNodeAnimator* animator = 0;// = new RelateCameraAnimatorMove( delay, duration, camera, start, end, moveType, factor );
		return animator;
	}

	// 相对摄像机静止，不知啥意思
	ISceneNodeAnimator* createRelateCameraStayAnimator( u32 delay, u32 duration, ICameraSceneNode* camera, vector3df position, bool loop = true );

	// 游戏开始时的环绕动画
	ISceneNodeAnimator* createTheBeginMoveAnimator( vector3df thebeginpoint, vector3df theendpoint,
		u32 delay, u32 duration, int circle_n );

};

#endif // MySceneManager_h__
