/********************************************************************
	创建时间: 2011-9-27   16:21
	文件名:   main.cpp
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     主逻辑

*********************************************************************/


#include "EngineHeader.h"
#include "PythonManager.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

void InitScene()
{
	try
	{
		using namespace boost::python;

		object UILoader = import( "UILoader" );
		object CreateGameScenes = UILoader.attr( "CreateGameScenes" );
		CreateGameScenes();
	}
	catch ( ... )
	{
		PyErr_Print();
	}
}

int main()
{
	Py_Initialize(); 
	if ( ! Py_IsInitialized() )	return -1;

	// 初始化Python模块
	initEngine();
	initUI();

	// 创建引擎事件接收器
	MyEventReceiver receiver;

	// 初始化引擎
	MyIrrlichtEngine::pEventReceiver = &receiver;
	MyIrrlichtEngine::screen_width = 1366;
	MyIrrlichtEngine::screen_height = 768;
	MyIrrlichtEngine::bFullScreen = false;

	// 创建引擎，并获取引擎指针
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	
	// 上面为关键性的初始化工作，请勿往上面插入其他代码，否则可能会导致未定义的行为
	//std::string buf;
	std::streambuf *default_buf = std::cout.rdbuf( MyIrrlichtEngine::Console_Buffer.rdbuf() );
	
	AddPythonPath();	// 添加Python路径
	
	InitScene();		// 构造场景跳转图

	// 启动引擎
	pEngine->Run();

	pEngine->GetDevice()->drop();

	std::cout.rdbuf( default_buf );
	//std::cout <<  MyIrrlichtEngine::Console_Buffer.str();

	//Py_Finalize();
	return 0;
}