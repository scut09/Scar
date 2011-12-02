/********************************************************************
    ����ʱ��: 2011-11-7   12:27
    �ļ���:   Robot_Client.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     AI�������õļٵĿͻ���

*********************************************************************/

#ifndef Robot_Client_h__
#define Robot_Client_h__

#include "IClient.h"
#include "Boost_Server.h"
#include "GameBag.h"
#include <irrlicht.h>

using namespace irr;
using namespace Network;

class RobotClient : public Network::IClient
{
	int								m_index;
	boost::shared_ptr<BoostServer>	Server;

public:
	RobotClient( boost::shared_ptr<BoostServer> server ) : Server( server )
	{

	}


	virtual int GetID() const 
	{
		return m_index;
	}

	virtual void SetID( int id ) 
	{
		m_index = id;

	}
	
	// ��������ƶ�	
	virtual void SendHeroMove( int index, float x, float y, float z )
	{
		PACKAGE pack;
		pack.SetCMD( HERO_MOVE );

		HeroMove move( index, x, y, z );

		pack.SetData( (char*)&move, sizeof( HeroMove ) );

		Server->AddPacketToBuffer( pack );
		//Server->OnReceive( 0, pack );
	}	

	// ��������������ת
	virtual void SendHeroRot( int index, float x, float y , float z )
	{
		PACKAGE pack;
		pack.SetCMD( HERO_ROTATE );

		HeroRotate rot( index, x, y, z );

		pack.SetData( (char*)&rot, sizeof( HeroRotate ) );

		Server->AddPacketToBuffer( pack );
		//Server->OnReceive( 0, pack );
	}

	// �����ڵ�������Ϣ�����е��ڵ����ж����ɷ������жϣ����оͷ��͸������
	virtual void SendBulletHit( int owner_index, int target_index, int bullet_type )
	{
		BulletHittedBag bag;
		bag.owner_index = owner_index;
		bag.target_index = target_index;
		bag.bullet_type = bullet_type;

		PACKAGE p;
		p.SetCMD( BULLET_HIT );
		p.SetData( (char*)&bag, sizeof( BulletHittedBag ) );

		//Server->OnReceive( 0, p );

		Server->AddPacketToBuffer( p );
	}

	// ���ͷ����ڵ�����Ϣ
	virtual void SendBullet( int index, int bullet_type,				
		const irr::core::vector3df& start, 
		const irr::core::vector3df& end, u32 life ) 
	{
		BulletCreateBag bullet;
		bullet.owner_index = m_index;
		bullet.start_point = start;
		bullet.end_point = end;
		bullet.life = life;

		PACKAGE pack;
		pack.SetCMD( BULLET_CREATE );
		pack.SetData( (char*)&bullet, sizeof( BulletCreateBag ) );

		Server->AddPacketToBuffer( pack );
		//Server->OnReceive( 0, pack );
	}
};


#endif // Robot_Client_h__