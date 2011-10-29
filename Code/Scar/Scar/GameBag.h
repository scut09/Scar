/********************************************************************
    创建时间: 2011-10-27   18:26
    文件名:   GameBag.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     游戏中发送的数据包的类型和各种数据包

*********************************************************************/


#ifndef GameBag_h__
#define GameBag_h__

#include <irrlicht.h>

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
		QUERY_ROOM,			// 玩家广播查询房间
		REQUEST_ENTER_ROOM,	// 请求加入
		BROADCAST_ROOM,		// 服务端广播自己创建了房间
		ALLOW_JOIN_ROOM,	// 服务端允许玩家加入
		NEW_PLAYER_JOIN		// 广播新玩家加入

	};

	// 由服务端发回的允许加入的数据包
	// 内容包括自己被分配的在游戏中的id，和初始坐标
	struct AllowJoinRoomBag
	{
		int		index;
		float	x;
		float	y;
		float	z;

		AllowJoinRoomBag( int i = 0, float xx = 0, float yy = 0, float zz = 0 )
			: index( i ), x( xx ), y( yy ), z( zz )
		{
		}
	};

	// 一个玩家信息 56B
	struct OnePlayerInfoBag
	{
		wchar_t		player_name[ 16 ];	// 32B

		// 24B
		int			player_index;		

		float		x;
		float		y;
		float		z;

		float		rot_x;
		float		rot_y;
	};

	// 广播用的所有玩家信息
	struct PlayerInfoBag
	{
		int					number;
		OnePlayerInfoBag	players[ 10 ];

		PlayerInfoBag() : number( 0 ) {}

		int GetLength() const
		{
			return sizeof( int ) + sizeof( OnePlayerInfoBag ) * number;
		}
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

		HeroMove( int i = 0, float xx = 0, float yy = 0, float zz = 0 )
			: index( i ), x( xx ), y( yy ), z( zz ) {}
	};

	// 玩家视角旋转的数据包
	struct HeroRotate
	{
		int		index;
		float		x;
		float		y;
		float		z;

		HeroRotate( int i = 0, float xx = 0, float yy = 0, float zz = 0 ) 
			: index( i ), x( xx ), y( yy ), z( zz )
		{ }
	};

	// 发射炮弹的数据包
	struct BulletCreateBag
	{
		int						owner_index;		// 发射玩家的id
		int						type;				// 炮弹类型
		int						bullet_index;		// 炮弹的id
		irr::core::vector3df	start_point;		// 起点
		irr::core::vector3df	end_point;			// 终点
		unsigned int			life;				// 生命
		//u32				start_time;
		// type
		// bullet index
		// bullet target
	};

	struct PlayerDeath
	{
		int			index;

	};

	// 炮弹命中，由炮弹的主人发送到服务端，服务端再发送下来
	struct BulletHittedBag
	{
		int				owner_index;			// 炮弹发射人的id
		int				target_index;			// 被命中人的id

		int				bullet_type;			// 炮弹类型
	};

	 

}

#endif // GameBag_h__
