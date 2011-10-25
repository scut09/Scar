#ifndef GameBag_h__
#define GameBag_h__


#include <irrlicht.h>

using namespace irr;

namespace Network
{

	// 包类型
	enum GameCMD
	{
		HERO_MOVE,			// 移动
		HERO_ROTATE,		// 摄像机旋转
		BULLET_CREATE,		// 炮弹创建	
		BULLET_HIT,			// 炮弹命中
		HERO_INFO,			// 玩家信息
		ROOM_CREATE,
		ENTER_ROOM
	};

	struct HeroMove
	{
		int		index;
		f32		x;
		f32		y;
		f32		z;
	};

	struct HeroRotate
	{
		int		index;
		f32		x;
		f32		y;
	};

	struct BulletCreateBag
	{
		int		ownerIndex;
		f32		x;
		f32		y;
		f32		z;
		// type
		// bullet index
		// bullet target
	};


}

#endif // GameBag_h__
