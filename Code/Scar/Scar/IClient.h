/********************************************************************
	创建时间: 2011:9:27   14:53
	文件名:   IClient.h
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     

*********************************************************************/

#ifndef _ICLIENT_H_
#define _ICLIENT_H_

#include <functional>
#include <string>
#include <list>

typedef std::function< void*( void* ) > IClientOnMsgCallbackFuncType;
typedef std::list< std::string > IPList;

/*
** 名字：IClient
** 说明：网络客户端接口
**
*/
class IClient
{
public:
	//************************************
	// 函数名:  IClient::SearchGameRoom
	// 返回值:  IPList
	// 函数修饰:
	// 描述：   查找当前局域网的服务器，我们先暂定端口号为 54321
	//************************************
	virtual IPList SearchGameRoom() = 0;

	//************************************
	// 函数名:  IClient::EnterGameRoom
	// 返回值:  void
	// 参数:    const std::string & ip
	// 函数修饰:
	// 描述：   加入服务器
	//************************************
	virtual void EnterGameRoom( const std::string& ip ) = 0;


	//************************************
	// 函数名:  IClient::SetOnMsgCallbackFunc
	// 返回值:  void
	// 参数:    IClientOnMsgCallbackFuncType func
	// 函数修饰:
	// 描述：   设置消息到达时的回调处理函数
	//************************************
	virtual void SetOnMsgCallbackFunc( IClientOnMsgCallbackFuncType func ) = 0;
};

#endif