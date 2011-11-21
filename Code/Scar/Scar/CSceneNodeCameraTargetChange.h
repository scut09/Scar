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

class CSceneNodeCameraTargetChange : public ISceneNodeAnimator
{
	u32 Begin;						// 起始时间
	u32 Delay;						// 延迟启动时间
	u32 Duration;					// 持续时间
	vector3df OriginTarget;			// 原始Target
	vector3df NewTarget;			// 新Target
	vector3df ChangeFactor;			// 缩放因子
	bool IsFirst;						// 是否已经初始化

public:

	CSceneNodeCameraTargetChange( u32 delay, u32 duration, vector3df newtarget );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );



};
#endif // CSceneNodeCameraTargetChange_h_
