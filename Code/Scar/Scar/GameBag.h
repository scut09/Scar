#ifndef GameBag_h__
#define GameBag_h__


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
		MESSAGE_BROADCAST,
		MESSAGE_TO,
		QUERY_ROOM,			// �㲥��ѯ����
		REQUEST_ENTER_ROOM,		// �������
		BROADCAST_ROOM,
		ALLOW_JOIN_ROOM
	};

	struct AllowJoinRoomBag
	{
		int		index;
		float	x;
		float	y;
		float	z;

		AllowJoinRoomBag( int i, int xx, int yy, int zz )
			: index( i ), x( xx ), y( yy ), z( zz )
		{
		}

		AllowJoinRoomBag() {}
	};

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

		HeroMove( int i, float xx, float yy, float zz )
			: index( i ), x( xx ), y( yy ), z( zz ) {}

		HeroMove() {}
	};

	struct HeroRotate
	{
		int		index;
		float		x;
		float		y;

		HeroRotate( int i, float xx, float yy ) 
			: index( i ), x( xx ), y( yy )
		{ }
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