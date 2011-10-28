#ifndef SceneNodeAnimatorFollow_h__
#define SceneNodeAnimatorFollow_h__

/********************************************************************
	创建日期:	2011/10/27
	文件名: 	C:\Users\Administrator\Desktop\工作\SCAR项目组\opengl-scut\Code\Scar\Scar\SceneNodeAnimatorFollow.h
	作者:		屠文翔
	
	描述:		在一个确定的距离上跟随制定目标运动
*********************************************************************/

#include "ISceneNode.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class SceneNodeAnimatorFollow : public ISceneNodeAnimator
{
	ISceneNode* Target;		// 跟随的目标
	f32 Distance;			// 保持的距离

public:
	SceneNodeAnimatorFollow( ISceneNode* tar, f32 distance = 0 );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );

};

#endif // SceneNodeAnimatorFollow_h__
