#ifndef TheBeginMove_h__
#define TheBeginMove_h__

//################################################################

// 文件名 : G:\图形大作业同步文件夹\Code\Scar\Scar\TheBeginMove.h

// 创建时间 : 2011/10/29 19:58

// 作者 : 林剑飞

// 函数功能 : 启动界面的动画

// 函数参数 : 

// 函数返回值 : 

//################################################################

#include "ISceneNode.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

#define PI 3.1415926 

class TheBeginMove : public ISceneNodeAnimator
{
	u32 Begin;
	u32 Delay;
	u32 Duration;
	f32 radian;
	int Circle_N;
	f32 Distance;
	f32 M_y;
	f32 M_Distance;
	vector3df TheBeginPoint;
	vector3df TheEndPoint;
	vector3df Center;

public:

	TheBeginMove( vector3df thebeginpoint, vector3df theendpoint, u32 delay, u32 duration, int circle_n );

	virtual void animateNode( ISceneNode* node, u32 timeMs );
};

#endif // TheBeginMove_h__
