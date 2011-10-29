/********************************************************************
    ����ʱ��: 2011-10-27   18:26
    �ļ���:   GameBag.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     ��Ϸ�з��͵����ݰ������ͺ͸������ݰ�

*********************************************************************/


#ifndef GameBag_h__
#define GameBag_h__

#include <irrlicht.h>

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
		QUERY_ROOM,			// ��ҹ㲥��ѯ����
		REQUEST_ENTER_ROOM,	// �������
		BROADCAST_ROOM,		// ����˹㲥�Լ������˷���
		ALLOW_JOIN_ROOM,	// �����������Ҽ���
		NEW_PLAYER_JOIN		// �㲥����Ҽ���

	};

	// �ɷ���˷��ص������������ݰ�
	// ���ݰ����Լ������������Ϸ�е�id���ͳ�ʼ����
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

	// һ�������Ϣ 56B
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

	// �㲥�õ����������Ϣ
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


	// �ɷ���˹㲥���͵��Լ������ķ������Ϣ
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

	// ����ƶ������ݰ�
	struct HeroMove
	{
		int		index;
		float		x;
		float		y;
		float		z;

		HeroMove( int i = 0, float xx = 0, float yy = 0, float zz = 0 )
			: index( i ), x( xx ), y( yy ), z( zz ) {}
	};

	// ����ӽ���ת�����ݰ�
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

	// �����ڵ������ݰ�
	struct BulletCreateBag
	{
		int						owner_index;		// ������ҵ�id
		int						type;				// �ڵ�����
		int						bullet_index;		// �ڵ���id
		irr::core::vector3df	start_point;		// ���
		irr::core::vector3df	end_point;			// �յ�
		unsigned int			life;				// ����
		//u32				start_time;
		// type
		// bullet index
		// bullet target
	};

	struct PlayerDeath
	{
		int			index;

	};

	// �ڵ����У����ڵ������˷��͵�����ˣ�������ٷ�������
	struct BulletHittedBag
	{
		int				owner_index;			// �ڵ������˵�id
		int				target_index;			// �������˵�id

		int				bullet_type;			// �ڵ�����
	};

	 

}

#endif // GameBag_h__
