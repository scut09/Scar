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
		NEW_PLAYER_JOIN,		// �㲥����Ҽ���
		SCORE_ARRIVAL,			// ��������
		SCORE_BOARD			// ������
	};

	/************************************************************************/
	/* ������                                                                     */
	/************************************************************************/
	// 12Byte
	struct ScoreArrivalBag
	{
		unsigned int ip;
		int		KillCount;	// ɱ����
		int		DeathCount;	// ������
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
	/* ������Ϣ                                                              */
	/************************************************************************/

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

	// �ɷ���˹㲥���͵��Լ������ķ������Ϣ
	struct BroadcastRoomBag
	{
		wchar_t		room_name[ 32 ];		// 64 B
		int			player_number;			// 4 B
		int			max_player_number;
		char		map_name[ 64 ];
	};


	/************************************************************************/
	/* ������Ϣ                                                              */
	/************************************************************************/

	const int BROADCAST_MESSAGE_SIZE = 1024;											// �����Ϣ����
	const int BROADCAST_MESSAGE_INIT_LENGTH = sizeof( int ) * 2 + sizeof( wchar_t );	// ��ʼ������


	// �㲥��Ϣ
	struct BroadcastMessageBag
	{
	public:
		int			index;				// �����˵�id
		int			target_index;		// Ŀ���id�����Ŀ��idΪ-1������ΪΪȺ��

	private:
		wchar_t		m_msg[ BROADCAST_MESSAGE_SIZE ];	// ��Ϣ
		int			m_len;									// ��Ϣ���ȣ�����������ᱻ���ͣ�ֻ�����ڷ���ʱ�������ݰ�����Ч����

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
	/* �����Ϣ                                                              */
	/************************************************************************/

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

	struct BroadcastPlayerInfo
	{
		int		player_number;

	};

	struct PlayerDeath
	{
		int			index;

	};



	/************************************************************************/
	/* ʵʱ�������                                                          */
	/************************************************************************/

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



	/************************************************************************/
	/* �ڵ����ݰ�                                                            */
	/************************************************************************/

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

	// �ڵ����У����ڵ������˷��͵�����ˣ�������ٷ�������
	struct BulletHittedBag
	{
		int				owner_index;			// �ڵ������˵�id
		int				target_index;			// �������˵�id

		int				bullet_type;			// �ڵ�����
	};





	 

}

#endif // GameBag_h__
