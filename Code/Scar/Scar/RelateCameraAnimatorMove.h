#ifndef RelateCameraAnimatorMove_h__
#define RelateCameraAnimatorMove_h__

/********************************************************************
	创建日期:	2011/10/23
	文件名: 	C:\Users\Administrator\Desktop\工作\SCAR项目组\opengl-scut\Code\Scar\Scar\RelateCameraAnimatorMove.h
	作者:		屠文翔
	
	描述:		相对镜头运动动画
				从一点运动到另一点
*********************************************************************/

#include "ICameraSceneNode.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

// 缓动类型
enum RM_MOVE_TYPE
{
	RM_MT_LINER,			// 线性
	RM_MT_LOG,				// 对数 快->慢
};

class RelateCameraAnimatorMove : public ISceneNodeAnimator
{
	u32 Begin;
	u32 Delay;
	u32 Duration;
	ICameraSceneNode* Camera;
	vector3df StartPos;
	vector3df EndPos;
	vector3df OffsetFactor;
	RM_MOVE_TYPE MoveType;
	f32 Factor;
	//bool Loop;

public:
	RelateCameraAnimatorMove( u32 delay, u32 duration, ICameraSceneNode* camera, vector3df start, vector3df end, 
		RM_MOVE_TYPE moveType = RM_MT_LINER, f32 factor = 0 );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );

};

#endif // RelateCameraAnimatorMove_h__
