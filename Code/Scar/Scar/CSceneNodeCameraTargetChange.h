#ifndef CSceneNodeCameraTargetChange_h_
#define CSceneNodeCameraTargetChange_h_

/********************************************************************
	创建日期:	2011/11/21
	文件名: 		CSceneNodeCameraTargetChange.h
	作者:		杨旭瑜
	描述:		摄像机朝向渐变动画
*********************************************************************/

#include "ICameraSceneNode.h"
#include "ISceneNode.h"

using namespace irr;
using namespace irr::core;
using namespace irr::scene;

// 缓动类型
enum AS_MOVE_TYPE
{
	AS_MT_LINER,			// 线性
	AS_MT_LOG,				// 对数 快->慢
	AS_MT_SQUARE,			// 平方 慢->快
	AS_MT_SQRT,			// 开方 快->慢
	AS_MT_POW				// 指数 设置指数以调整曲线
};

class CSceneNodeCameraTargetChange : public ISceneNodeAnimator
{
	u32 Begin;						// 起始时间
	u32 Delay;						// 延迟启动时间
	u32 Duration;					// 持续时间
	vector3df OriginTatget;				// 原始缩放
	vector3df Target;				// 缩放增量
	vector3df ChangeFactor;			// 缩放因子
	AS_MOVE_TYPE MoveType;				// 缓动类型
	f32 Factor;						// 缓动系数	

public:

	CSceneNodeCameraTargetChange( u32 delay, u32 duration, vector3df newtarget, AS_MOVE_TYPE type = AS_MT_LINER, f32 factor = 0 );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );



};
#endif // CSceneNodeCameraTargetChange_h_
