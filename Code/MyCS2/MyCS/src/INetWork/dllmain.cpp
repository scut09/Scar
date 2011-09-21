///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/15 14:22
//Describe: �������� �ڴ˳�ʼ��socket����
///////////////////////////////////////////////////////////////////////

#include <WinSock2.h>

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
					  DWORD  ul_reason_for_call,
					  LPVOID lpReserved
					  )
{

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:		//��ʼ��socket
		{
			WORD wVersionRequested;
			WSADATA wsaData;
			int err;

			wVersionRequested = MAKEWORD( 1, 1 );

			err = WSAStartup( wVersionRequested, &wsaData );
			if ( err != 0 )
			{
				return false;
			}

			if ( LOBYTE( wsaData.wVersion ) != 1 ||
				HIBYTE( wsaData.wVersion ) != 1 ) 
			{
				WSACleanup();
				return false; 
			}
			break;
		}

	case DLL_PROCESS_DETACH:		//�ر�socket
		{
			WSACleanup();
			break;
		}		

	default:
		break;
	}

	return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif