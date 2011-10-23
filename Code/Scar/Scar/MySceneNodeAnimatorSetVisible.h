#ifndef MySceneNodeAnimatorSetVisible_h__
#define MySceneNodeAnimatorSetVisible_h__

/********************************************************************
	创建日期:	2011/10/22
	文件名: 	C:\Users\Administrator\Desktop\工作\SCAR项目组\opengl-scut\Code\Scar\Scar\MySceneNodeAnimatorSetVisible.h
	作者:		屠文翔
	
	描述:		延时设置Visible属性动画
				一段时间后改变目标Visible的属性
*********************************************************************/

#include "ISceneNode.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class MySceneNodeAnimatorSetVisible : public ISceneNodeAnimator
{
	u32 Begin;
	u32 Delay;
	u32 Duration;
	bool IsVisible;
	
public:
	MySceneNodeAnimatorSetVisible( u32 delay, u32 duration, bool isVisible );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );

};

#endif // MySceneNodeAnimatorSetVisible_h__
