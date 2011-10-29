#ifndef MySceneNodeAnimatorShake_h__
#define MySceneNodeAnimatorShake_h__

/********************************************************************
	创建日期:	2011/10/23
	文件名: 	C:\Users\Administrator\Desktop\工作\SCAR项目组\opengl-scut\Code\Scar\Scar\MySceneNodeAnimatorShake.h
	作者:		屠文翔
	
	描述:		以屏幕中点为中心画面抖动动画
				可设置平滑抖动
*********************************************************************/

#include "ISceneNode.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class MySceneNodeAnimatorShake : public ISceneNodeAnimator
{
	u32 Begin;
	u32 Delay;
	u32 Duration;
	vector3df Origin;			// 摄像机原始角度
	vector3df LastOffset;		// 上次抖动改变角度
	f32 AmpFrom;				// 振幅 角度
	f32 AmpTo;					// 振幅 角度
	f32 AmpFactor;				
	
	
public:
	MySceneNodeAnimatorShake( u32 delay, u32 duration, f32 ampFrom, f32 ampTo = 0 );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager/*=0*/ );

};


#endif // MySceneNodeAnimatorShake_h__
