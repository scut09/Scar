/********************************************************************
	创建时间: 2011-9-27   15:00
	文件名:   IServer.h
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     

*********************************************************************/

#ifndef _ISERVER_H
#define _ISERVER_H


/*
** 名字：IServer
** 说明：服务器接口
**
*/
class IServer
{
public:

	virtual int CreateGameRoom( 
		int maxPlayerNumber, 
		const std::string& gameRoomName 
		) = 0;

	//************************************
	// 函数名:  IServer::Start
	// 返回值:  int
	// 函数修饰:
	// 描述：   
	//************************************
	virtual int Start() = 0;

	//************************************
	// 函数名:  IServer::Stop
	// 返回值:  int
	// 函数修饰:
	// 描述：   
	//************************************
	virtual int Stop() = 0;

};



#endif