/********************************************************************
	创建时间: 2011-9-27   16:21
	文件名:   main.cpp
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     主逻辑

*********************************************************************/


#include "MyIrrlichtEngine.h"
#include "EventListener.h"
#include <iostream>

int main()
{
	// 创建引擎事件接收器
	MyEventReceiver receiver;

	// 初始化引擎
	MyIrrlichtEngine::pEventReceiver = &receiver;
	MyIrrlichtEngine::screen_width = 1000;
	MyIrrlichtEngine::screen_height = 640;
	MyIrrlichtEngine::bFullScreen = false;

	// 创建引擎，并获取引擎指针
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();

	// 注册引擎回调函数
	pEngine->SetCallbackFunc( []( void* engine )->void*
	{
		std::cout << "1";
		return 0;
	} );

	// 创建并注册receiver的事件处理回调函数
	receiver.SetEventCallbackFunc( [ pEngine ]( const SEvent& event )->void*
	{	
		pEngine;		// 引擎指针
		std::cout << "\n" << event.MouseInput.X << ' ' << event.MouseInput.Y << std::endl;
		return 0;
	} );

	// 启动引擎
	pEngine->Run();

	return 0;
}