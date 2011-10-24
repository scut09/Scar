#ifndef MySceneNodeAnimatorMove_h__
#define MySceneNodeAnimatorMove_h__

/********************************************************************
	创建时间:	2011/10/24
	文件名称: 	K:\Users\Kid_shusang\Desktop\SCAR SVN\Code\Scar\Scar\MySceneNodeAnimatorMove.h
	作者:		$屠文翔$
	
	描述:		创建两点间的直飞动画
*********************************************************************/
#include "ISceneNode.h"
using namespace irr;
using namespace irr::core;
using namespace irr::scene;

// 缓动类型
enum AM_MOVE_TYPE
{
	AM_MT_LINER,			// 线性
	AM_MT_LOG,				// 对数 快->慢
};

class MySceneNodeAnimatorMove : public ISceneNodeAnimator
{
	u32 Begin;
	u32 Delay;
	u32 Duration;
	vector3df StartPos;
	vector3df EndPos;
	vector3df OffsetFactor;
	AM_MOVE_TYPE MoveType;
	f32 Factor;
	
public:
	MySceneNodeAnimatorMove( u32 delay, u32 duration, vector3df start, vector3df end, 
		AM_MOVE_TYPE moveType = AM_MT_LINER, f32 factor = 0 );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );

};

#endif // MySceneNodeAnimatorMove_h__
