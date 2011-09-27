/********************************************************************
	����ʱ��: 2011-9-27   16:21
	�ļ���:   main.cpp
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     ���߼�

*********************************************************************/


#include "MyIrrlichtEngine.h"
#include "EventListener.h"
#include <iostream>

int main()
{
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
		std::cout << "1";
		return 0;
	} );

	// ������ע��receiver���¼�����ص�����
	receiver.SetEventCallbackFunc( [ pEngine ]( const SEvent& event )->void*
	{	
		pEngine;		// ����ָ��
		std::cout << "\n" << event.MouseInput.X << ' ' << event.MouseInput.Y << std::endl;
		return 0;
	} );

	// ��������
	pEngine->Run();

	return 0;
}