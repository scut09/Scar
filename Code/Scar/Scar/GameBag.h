/********************************************************************
    创建时间: 2011-10-27   18:26
    文件名:   GameBag.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     游戏中发送的数据包的类型和各种数据包

*********************************************************************/


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
		REQUEST_ENTER_ROOM,		// 请求加入
		BROADCAST_ROOM,
		ALLOW_JOIN_ROOM
	};

	// 由服务端发回的允许加入的数据包
	// 内容包括自己被分配的在游戏中的id，和初始坐标
	struct AllowJoinRoomBag
	{
		int		index;
		float	x;
		float	y;
		float	z;

		AllowJoinRoomBag( int i, float xx, float yy, float zz )
			: index( i ), x( xx ), y( yy ), z( zz )
		{
		}

		AllowJoinRoomBag() {}
	};

	// 玩家信息
	struct PlayerInfoBag
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

	// 由服务端广播发送的自己创建的房间的信息
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

	// 玩家移动的数据包
	struct HeroMove
	{
		int		index;
		float		x;
		float		y;
		float		z;

		HeroMove( int i, float xx, float yy, float zz )
			: index( i ), x( xx ), y( yy ), z( zz ) {}

		HeroMove() {}
	};

	// 玩家视角旋转的数据包
	struct HeroRotate
	{
		int		index;
		float		x;
		float		y;

		HeroRotate( int i, float xx, float yy ) 
			: index( i ), x( xx ), y( yy )
		{ }
	};

	// 发射炮弹的数据包
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
