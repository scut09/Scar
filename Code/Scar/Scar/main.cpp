/********************************************************************
	����ʱ��: 2011-9-27   16:21
	�ļ���:   main.cpp
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     ���߼�

*********************************************************************/


#include "EngineHeader.h"
#include "Aircraft.h"
#include "FlyBehavior.h"
#include "MultiplayerScene.h"
#include "StartScene.h"
#include "PythonManager.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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

	// ��ʼ��Pythonģ��
	initEngine();
	initUI();

	// ���������¼�������
	MyEventReceiver receiver;

	// ��ʼ������
	MyIrrlichtEngine::pEventReceiver = &receiver;
	MyIrrlichtEngine::screen_width = 1366;
	MyIrrlichtEngine::screen_height = 768;
	MyIrrlichtEngine::bFullScreen = false;

	// �������棬����ȡ����ָ��
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();
	
	// ����Ϊ�ؼ��Եĳ�ʼ����������������������������룬������ܻᵼ��δ�������Ϊ
	//std::string buf;
	std::streambuf *default_buf = std::cout.rdbuf( MyIrrlichtEngine::Console_Buffer.rdbuf() );
	
	AddPythonPath();	// ���Python·��
	
	InitScene();		// ���쳡����תͼ

	// ��������
	pEngine->Run();

	pEngine->GetDevice()->drop();

	std::cout.rdbuf( default_buf );
	//std::cout <<  MyIrrlichtEngine::Console_Buffer.str();

	//Py_Finalize();
	return 0;
}