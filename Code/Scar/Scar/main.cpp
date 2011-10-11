/********************************************************************
	创建时间: 2011-9-27   16:21
	文件名:   main.cpp
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     主逻辑

*********************************************************************/


#include "EngineHeader.h"
#include <iostream>
#include "Aircraft.h"
#include "FlyBehavior.h"
#include "MultiplayerScene.h"

void InitModels()
{
	using namespace boost::python;

	try
	{
		object modelLoader = import( "ModelLoader" );
		object Load = modelLoader.attr( "Load" );
		Load();
	}
	catch ( ... )
	{
		PyErr_Print();
	}
}

boost::python::object StartScene()
{
	using namespace boost::python;

	try
	{
		object s = import( "scene" );
		object GotoScene = s.attr( "GotoScene" );
		return GotoScene;
		//GotoScene();
	}
	catch ( ... )
	{
		PyErr_Print();
	}
}

scene::ISceneNode* Test( scene::ISceneNode* node )
{
	core::vector3df pedge[ 8 ];

	node->getTransformedBoundingBox().getEdges( pedge );

	core::line3df pray[ 12 ];

	pray[ 0 ].start = pedge[ 0 ];
	pray[ 0 ].end = pedge[ 2 ];

	pray[ 1 ].start = pedge[ 0 ];
	pray[ 1 ].end = pedge[ 1 ];

	pray[ 2 ].start = pedge[ 2 ];
	pray[ 2 ].end = pedge[ 3 ];

	pray[ 3 ].start = pedge[ 3 ];
	pray[ 3 ].end = pedge[ 1 ];

	pray[ 4 ].start = pedge[ 1 ];
	pray[ 4 ].end = pedge[ 5 ];

	pray[ 5 ].start = pedge[ 0 ];
	pray[ 5 ].end = pedge[ 4 ];

	pray[ 6 ].start = pedge[ 2 ];
	pray[ 6 ].end = pedge[ 6 ];

	pray[ 7 ].start = pedge[ 3 ];
	pray[ 7 ].end = pedge[ 7 ];

	pray[ 8 ].start = pedge[ 5 ];
	pray[ 8 ].end = pedge[ 4 ];

	pray[ 9 ].start = pedge[ 5 ];
	pray[ 9 ].end = pedge[ 7 ];

	pray[ 10 ].start = pedge[ 4 ];
	pray[ 10 ].end = pedge[ 6 ];

	pray[ 11 ].start = pedge[ 6 ];
	pray[ 11 ].end = pedge[ 7 ];

	core::vector3df intersection;
	core::triangle3df hitTriangle;

	scene::ISceneNode* selectedSceneNode = 0;
	for( int i = 0; i < 12; i++ )
	{
		if ( selectedSceneNode = MyIrrlichtEngine::GetEngine()->GetCollisionManager()->getSceneNodeAndCollisionPointFromRay( pray[i], intersection, hitTriangle ) )
			break;
	}

	return selectedSceneNode;
}



int main()
{
	Py_Initialize(); 
	if ( ! Py_IsInitialized() )	return -1;

	// 初始化Python模块
	initEngine();

	// 创建引擎事件接收器
	MyEventReceiver receiver;

	// 初始化引擎
	MyIrrlichtEngine::pEventReceiver = &receiver;
	MyIrrlichtEngine::screen_width = 1000;
	MyIrrlichtEngine::screen_height = 640;
	MyIrrlichtEngine::bFullScreen = false;

	// 创建引擎，并获取引擎指针
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();

	// 上面为关键性的初始化工作，请勿往上面插入其他代码，否则可能会导致未定义的行为



	MultiplayerScene scene;
	scene.Init();


	// 注册引擎回调函数
	pEngine->SetCallbackFunc( [ &scene ]( void* engine )->void*
	{
		scene.Run();

		return 0;
	} );

	

	// 创建并注册receiver的事件处理回调函数
	receiver.SetEventCallbackFunc( [ pEngine ]( const SEvent& event )->void*
	{	
		//control.OnEvent( event );
		pEngine;		// 引擎指针
		//std::cout << "\n" << event.MouseInput.X << ' ' << event.MouseInput.Y << std::endl;
		return 0;
	} );

	pEngine->LoadModels();





	// 启动引擎
	pEngine->Run();

	//Py_Finalize();
	return 0;
}