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
		NEW_PLAYER_JOIN,		// 广播新玩家加入
		SCORE_ARRIVAL,			// 分数到达
		SCORE_BOARD			// 分数板
	};

	/************************************************************************/
	/* 分数板                                                                     */
	/************************************************************************/
	// 12Byte
	struct ScoreArrivalBag
	{
		unsigned int ip;
		int		KillCount;	// 杀人数
		int		DeathCount;	// 死亡数
	};

	// 12 * 16 + 4 = 196Byte
	struct ScoreBoardBag
	{
		int count;
		ScoreArrivalBag bag[ 16 ];

		ScoreBoardBag() : count( 0 ) {}

		int GetLength() const
		{
			return sizeof( int ) + count * sizeof( ScoreArrivalBag );
		}

		void InsertScore( const ScoreArrivalBag& bag )
		{
			this->bag[ count++ ] = bag;
		}


	};

	/************************************************************************/
	/* 房间信息                                                              */
	/************************************************************************/

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

	// 由服务端广播发送的自己创建的房间的信息
	struct BroadcastRoomBag
	{
		wchar_t		room_name[ 32 ];		// 64 B
		int			player_number;			// 4 B
		int			max_player_number;
		char		map_name[ 64 ];
	};


	/************************************************************************/
	/* 聊天信息                                                              */
	/************************************************************************/

	const int BROADCAST_MESSAGE_SIZE = 1024;											// 最大信息长度
	const int BROADCAST_MESSAGE_INIT_LENGTH = sizeof( int ) * 2 + sizeof( wchar_t );	// 初始包长度


	// 广播信息
	struct BroadcastMessageBag
	{
	public:
		int			index;				// 发送人的id
		int			target_index;		// 目标的id，如果目标id为-1，则认为为群发

	private:
		wchar_t		m_msg[ BROADCAST_MESSAGE_SIZE ];	// 信息
		int			m_len;									// 信息长度，这个变量不会被发送，只是用于发送时计算数据包的有效长度

	public:
		BroadcastMessageBag( int idx = -1, int targetindex = -1 )
			: index( idx ), target_index( targetindex )
		{
			m_len = BROADCAST_MESSAGE_INIT_LENGTH;
			m_msg[ 0 ] = 0;
		}

		int GetLength() const
		{
			return m_len;
		}

		void SetMsg( const wchar_t* msg )
		{
			int i = 0;
			while ( msg[ i ] && i < BROADCAST_MESSAGE_SIZE )
			{
				m_msg[ i ] = msg[ i ];
				i++;
			}
			m_msg[ i ] = 0;
			m_len = BROADCAST_MESSAGE_INIT_LENGTH + i * sizeof( wchar_t );
		}

		const wchar_t* GetMsg() const
		{
			return m_msg;
		}
	};
	

	/************************************************************************/
	/* 玩家信息                                                              */
	/************************************************************************/

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

	struct BroadcastPlayerInfo
	{
		int		player_number;

	};

	struct PlayerDeath
	{
		int			index;

	};



	/************************************************************************/
	/* 实时玩家数据                                                          */
	/************************************************************************/

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



	/************************************************************************/
	/* 炮弹数据包                                                            */
	/************************************************************************/

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

	// 炮弹命中，由炮弹的主人发送到服务端，服务端再发送下来
	struct BulletHittedBag
	{
		int				owner_index;			// 炮弹发射人的id
		int				target_index;			// 被命中人的id

		int				bullet_type;			// 炮弹类型
	};





	 

}

#endif // GameBag_h__
