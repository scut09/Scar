#ifndef GameBag_h__
#define GameBag_h__


typedef float f32;


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
		MESSAGE_BROADCAST,
		MESSAGE_TO,
		REQUEST_ROOM,
		BROADCAST_ROOM,
		ENTER_ROOM
	};

	struct PlayerInfo
	{
		wchar_t		player_name[ 16 ];	// 32B

		// 24B
		int			player_index;		

		f32			x;
		f32			y;
		f32			z;

		f32			rot_x;
		f32			rot_y;


	};

	struct BroadcastRoomBag
	{
		wchar_t		room_name[ 32 ];		// 64 B
		int			player_number;			// 4 B
		int			max_player_number;
		char		map_name[ 64 ];
	}; 

	struct BroadcastPlayerInfo
	{
		int		player_number;

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
		int		owner_index;
		f32		x;
		f32		y;
		f32		z;
		// type
		// bullet index
		// bullet target
	};


}

#endif // GameBag_h__
