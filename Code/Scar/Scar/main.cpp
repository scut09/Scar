/********************************************************************
	创建时间: 2011-9-27   16:21
	文件名:   main.cpp
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     

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