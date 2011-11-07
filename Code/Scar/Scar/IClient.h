/********************************************************************
创建时间: 2011:9:27   14:53
文件名:   IClient.h
作者:     华亮 Cedric Porter [ Stupid ET ]	
说明:     客户端接口。客户端端应该继承IClient并实现IClient的接口，
		系统其他部分针对IClient接口编程  

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
	** 名字：IClient
	** 说明：网络客户端接口
	**
	*/
	class IClient
	{
	public:
		virtual ~IClient() {}

		virtual int GetID() const = 0;
		virtual void SetID( int id ) = 0;

		// 广播查询房间	
		virtual void QueryRoom() {}		
		// 加入房间	
		virtual void EnterRoom( const std::string& ip ) {}		
		// 发送玩家移动	
		virtual void SendHeroMove( int index, float x, float y, float z )	{}	
		// 发送玩家摄像机旋转
		virtual void SendHeroRot( int index, float x, float y , float z )	{}
		// 发送消息给一个人	
		virtual void SendMessageTo( int index, int target_index, const wchar_t* msg ) {}
		// 群发发送消息
		virtual void BroadcastMessage( int index, const wchar_t* msg ) {}

		// 发送炮弹命中消息，所有的炮弹命中都是由发射人判断，命中就发送给服务端
		virtual void SendBulletHit( int owner_index, int target_index, int bullet_type ) {}
		// 发送发射炮弹的消息
		virtual void SendBullet( int index, int bullet_type,				
			const irr::core::vector3df& start, 
			const irr::core::vector3df& end, irr::u32 life ) {}

	};

}


#endif