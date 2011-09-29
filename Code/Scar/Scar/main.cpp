/********************************************************************
	����ʱ��: 2011-9-27   16:21
	�ļ���:   main.cpp
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     ���߼�

*********************************************************************/


#include "EngineHeader.h"
#include <iostream>

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

	// ע������ص�����
	pEngine->SetCallbackFunc( []( void* engine )->void*
	{
		//std::cout << "1";
		return 0;
	} );

	// ������ע��receiver���¼�����ص�����
	receiver.SetEventCallbackFunc( [ pEngine ]( const SEvent& event )->void*
	{	
		pEngine;		// ����ָ��
		//std::cout << "\n" << event.MouseInput.X << ' ' << event.MouseInput.Y << std::endl;
		return 0;
	} );

	pEngine->LoadModels();

	InitModels();

	ModelManager* modelMan = pEngine->GetModelManager();

	modelMan->AddSceneNodeFromMesh( "1" );
	scene::ISceneNode* node = modelMan->AddSceneNodeFromMesh( "bottle" );
	node->setPosition( core::vector3df( 1000.0, 200.0, 100.0 ) );

	irr::video::SLight light;

	// ��������
	pEngine->Run();

	//Py_Finalize();
	return 0;
}