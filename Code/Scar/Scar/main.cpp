/********************************************************************
	����ʱ��: 2011-9-27   16:21
	�ļ���:   main.cpp
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     

*********************************************************************/


#include "MyIrrlichtEngine.h"


int main()
{
	MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();

	//EngineRunCallbackFuncType func = []( void* engine )->void*
	//{

	//	return 0;
	//};

	//pEngine->SetCallbackFunc( func );

	pEngine->Run();

	return 0;
}