/********************************************************************
	����ʱ��: 2011-9-27   16:21
	�ļ���:   main.cpp
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     ���߼�

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
	// ��Ϊ�պ�ʹ��python������������ת�����Բ���Ҫ�����ڴ棬���������������

	// ����������
	//StartScene* rootScene = new StartScene;
	//MyIrrlichtEngine::currentScene = rootScene;
	//MultiplayerScene* multiplayerScene = new MultiplayerScene;
	//rootScene->Scenes[ 0 ] = multiplayerScene;
	//multiplayerScene->Scenes[ 0 ] = rootScene;

	//// ��ʼ��������
	//rootScene->Init();

	try
	{
		using namespace boost::python;

		object UILoader = import( "UILoader" );
		object GetRoot = UILoader.attr( "CreateGameScenes" );
		object root = GetRoot();
		//root.ptr()->ob_refcnt++;		// �������ü���

		//MyIrrlichtEngine::currentScene = extract<GameScene*>( root ); 
		//r->drop();	// ʹ��Python�������ڴ����
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

	// ��ʼ��Pythonģ��
	initEngine();
	initUI();

	// ���������¼�������
	MyEventReceiver receiver;

	// ��ʼ������
	MyIrrlichtEngine::pEventReceiver = &receiver;
	MyIrrlichtEngine::screen_width = 1024;
	MyIrrlichtEngine::screen_height = 768;
	MyIrrlichtEngine::bFullScreen = false;

	// �������棬����ȡ����ָ��
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	
	// ����Ϊ�ؼ��Եĳ�ʼ����������������������������룬������ܻᵼ��δ�������Ϊ
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

	// ������Ҫ����һ�������������ã��������ᱻ����
	GameScene* root = InitScene();	// ���쳡����תͼ

	// ��������
	pEngine->Run();

	pEngine->GetDevice()->drop();

	//Py_Finalize();
	return 0;
}