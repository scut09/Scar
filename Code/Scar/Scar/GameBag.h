#ifndef GameBag_h__
#define GameBag_h__


#include <irrlicht.h>

using namespace irr;

namespace Network
{

	// ������
	enum GameCMD
	{
		HERO_MOVE,			// �ƶ�
		HERO_ROTATE,		// �������ת
		BULLET_CREATE,		// �ڵ�����	
		BULLET_HIT,			// �ڵ�����
		HERO_INFO,			// �����Ϣ
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
