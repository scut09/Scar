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
		REQUEST_ROOM,		// �������
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
