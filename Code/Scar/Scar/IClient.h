/********************************************************************
����ʱ��: 2011:9:27   14:53
�ļ���:   IClient.h
����:     ���� Cedric Porter [ Stupid ET ]	
˵��:     �ͻ��˽ӿڡ��ͻ��˶�Ӧ�ü̳�IClient��ʵ��IClient�Ľӿڣ�
		ϵͳ�����������IClient�ӿڱ��  

*********************************************************************/

#ifndef _ICLIENT_H_
#define _ICLIENT_H_

#include <functional>
#include <string>
#include <list>
#include <irrlicht.h>

namespace Network
{
	

	/*
	** ���֣�IClient
	** ˵��������ͻ��˽ӿ�
	**
	*/
	class IClient
	{
	public:
		virtual ~IClient() {}

		virtual int GetID() const = 0;
		virtual void SetID( int id ) = 0;

		// �㲥��ѯ����	
		virtual void QueryRoom() {}		
		// ���뷿��	
		virtual void EnterRoom( const std::string& ip ) {}		
		// ��������ƶ�	
		virtual void SendHeroMove( int index, float x, float y, float z )	{}	
		// ��������������ת
		virtual void SendHeroRot( int index, float x, float y , float z )	{}
		// ������Ϣ��һ����	
		virtual void SendMessageTo( int index, int target_index, const wchar_t* msg ) {}
		// Ⱥ��������Ϣ
		virtual void BroadcastMessage( int index, const wchar_t* msg ) {}

		// �����ڵ�������Ϣ�����е��ڵ����ж����ɷ������жϣ����оͷ��͸������
		virtual void SendBulletHit( int owner_index, int target_index, int bullet_type ) {}
		// ���ͷ����ڵ�����Ϣ
		virtual void SendBullet( int index, int bullet_type,				
			const irr::core::vector3df& start, 
			const irr::core::vector3df& end, irr::u32 life ) {}

	};

}


#endif