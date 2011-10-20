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
#include "StartScene.h"


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


GameScene* InitScene()
{
	// 因为日后使用python创建出场景跳转，所以不需要管理内存，现在这里仅供测试

	// 创建根场景
	//StartScene* rootScene = new StartScene;
	//MyIrrlichtEngine::currentScene = rootScene;
	//MultiplayerScene* multiplayerScene = new MultiplayerScene;
	//rootScene->Scenes[ 0 ] = multiplayerScene;
	//multiplayerScene->Scenes[ 0 ] = rootScene;

	//// 初始化根场景
	//rootScene->Init();

	try
	{
		using namespace boost::python;

		object UILoader = import( "UILoader" );
		object GetRoot = UILoader.attr( "CreateGameScenes" );
		object root = GetRoot();
		//root.ptr()->ob_refcnt++;		// 增加引用计数

		//MyIrrlichtEngine::currentScene = extract<GameScene*>( root ); 
		//r->drop();	// 使用Python对象不用内存管理
	}
	catch ( ... )
	{
		PyErr_Print();
	}

	return NULL;
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
	MyIrrlichtEngine::screen_width = 1024;
	MyIrrlichtEngine::screen_height = 768;
	MyIrrlichtEngine::bFullScreen = false;

	// 创建引擎，并获取引擎指针
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	
	// 上面为关键性的初始化工作，请勿往上面插入其他代码，否则可能会导致未定义的行为
	using namespace boost::python;

	try
	{
		object main_module = import( "__main__" );
		object main_namespace = main_module.attr( "__dict__" );
		//object sys = import( "sys" );
		object ignored = exec( 
			"import sys\n"
			"sys.path.append('./python')\n", main_namespace );
		ignored = exec( "print sys.path", main_namespace );

		object UILoader = import( "UILoader" );
		object SetScreen = UILoader.attr( "SetScreen" );
		SetScreen( MyIrrlichtEngine::screen_width, MyIrrlichtEngine::screen_height );
	}
	catch ( ... )
	{
		PyErr_Print();
	}

	// 这里需要保存一个根场景的引用，否则它会被销毁
	GameScene* root = InitScene();	// 构造场景跳转图

	// 启动引擎
	pEngine->Run();

	pEngine->GetDevice()->drop();

	//Py_Finalize();
	return 0;
}