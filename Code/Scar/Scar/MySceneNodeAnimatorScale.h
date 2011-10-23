#ifndef MySceneNodeAnimatorScale_h__
#define MySceneNodeAnimatorScale_h__

/********************************************************************
	创建日期:	2011/10/22
	文件名: 	C:\Users\Administrator\Desktop\工作\SCAR项目组\opengl-scut\Code\Scar\Scar\MySceneNodeAnimatorScale.h
	作者:		屠文翔
	
	描述:		通用型缩放动画
				使用标志位来区分缓动类型
*********************************************************************/

#include "ISceneNode.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

// 缓动类型
enum MOVE_TYPE
{
	MT_LINER,			// 线性
	MT_LOG,				// 对数 快->慢
	MT_SQUARE,			// 平方 慢->快
	MT_SQRT,			// 开方 快->慢
	MT_POW				// 指数 设置指数以调整曲线
};

class MySceneNodeAnimatorScale : public ISceneNodeAnimator
{
	u32 Begin;						// 起始时间
	u32 Delay;						// 延迟启动时间
	u32 Duration;					// 持续时间
	vector3df Origin;				// 原始缩放
	vector3df Scale;				// 缩放增量
	vector3df ScaleFactor;			// 缩放因子
	MOVE_TYPE MoveType;				// 缓动类型
	f32 Factor;						// 缓动系数	

public:

	MySceneNodeAnimatorScale( u32 delay, u32 duration, vector3df scale, MOVE_TYPE type = MT_LINER, f32 factor = 0 );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );



};
#endif // MySceneNodeAnimatorScale_h__
