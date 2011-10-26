#ifndef GameBag_h__
#define GameBag_h__


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
		QUERY_ROOM,			// 广播查询房间
		REQUEST_ROOM,		// 请求加入
		BROADCAST_ROOM,
		ENTER_ROOM
	};

	struct PlayerInfo
	{
		wchar_t		player_name[ 16 ];	// 32B

		// 24B
		int			player_index;		

		float			x;
		float			y;
		float			z;

		float			rot_x;
		float			rot_y;


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
		float		x;
		float		y;
		float		z;
	};

	struct HeroRotate
	{
		int		index;
		float		x;
		float		y;
	};

	struct BulletCreateBag
	{
		int		owner_index;
		float		x;
		float		y;
		float		z;
		// type
		// bullet index
		// bullet target
	};


}

#endif // GameBag_h__
