/********************************************************************
	����ʱ��: 2011-9-27   16:21
	�ļ���:   main.cpp
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     ���߼�

*********************************************************************/


#include "EngineHeader.h"
#include <iostream>
#include "../Irrlicht/CSceneNodeAnimatorCameraFPS.h"

class foo : public CSceneNodeAnimatorCameraFPS
{

};

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

	// ��ʼ��Pythonģ��
	initEngine();

	// ���������¼�������
	MyEventReceiver receiver;

	// ��ʼ������
	MyIrrlichtEngine::pEventReceiver = &receiver;
	MyIrrlichtEngine::screen_width = 1000;
	MyIrrlichtEngine::screen_height = 640;
	MyIrrlichtEngine::bFullScreen = false;

	// �������棬����ȡ����ָ��
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();

	ModuleControl control;



	// ע������ص�����
	pEngine->SetCallbackFunc( [ &control ]( void* engine )->void*
	{
		control.MoveForward( 1.0 );

		//std::cout << "1";
		return 0;
	} );

	

	// ������ע��receiver���¼�����ص�����
	receiver.SetEventCallbackFunc( [ pEngine, &control ]( const SEvent& event )->void*
	{	
		control.OnEvent( event );
		pEngine;		// ����ָ��
		//std::cout << "\n" << event.MouseInput.X << ' ' << event.MouseInput.Y << std::endl;
		return 0;
	} );

	pEngine->LoadModels();

	InitModels();

	scene::ISceneManager* smgr = pEngine->GetSceneManager();

	ModelManager* modelMan = pEngine->GetModelManager();

	control.Initialize( smgr->addCameraSceneNodeFPS(), modelMan->AddSceneNodeFromMesh( "1" ) );

	scene::ISceneNode* node = modelMan->AddSceneNodeFromMesh( "bottle" );

	node->setPosition( core::vector3df( 1000.0, 200.0, 100.0 ) );

	irr::video::SLight light;

	// ��������
	pEngine->Run();

	//Py_Finalize();
	return 0;
}