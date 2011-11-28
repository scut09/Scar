/********************************************************************
	����ʱ��: 2011-9-27   16:21
	�ļ���:   main.cpp
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     ���߼�

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

	// ��ʼ��Pythonģ��
	//try
	{
		initPythonSceneMgr();
		initEngine();
		initUI();
		initGameSceneModule();
		initShader();
	}
	//catch ( ... )
	{
	//	PyErr_Print();
	}


	// ���������¼�������
	MyEventReceiver receiver;

	// ��ʼ������
	MyIrrlichtEngine::pEventReceiver = &receiver;
	MyIrrlichtEngine::screen_width = 1280;
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

	irr::IrrlichtDevice* device = pEngine->GetDevice();
	// ���������ǵİ�װ����
	MyIrrlichtEngine::DestoryEngine();
	// ����Irricht����
	device->drop();


	std::cout.rdbuf( default_buf );
	//std::cout <<  MyIrrlichtEngine::Console_Buffer.str();

	//Py_Finalize();
	return 0;
}