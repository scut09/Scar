/*
** �ļ�����main.cpp
** �����ˣ�����
** ˵����
**
*/

/*
	����ǰ������boost��include·����lib·��
*/


#include "def.h"

#define BOOST_PYTHON_STATIC_LIB

#include <iostream>
#include <Windows.h>
#include <boost\thread.hpp>

boost::mutex g_mutex;

void ThreadFunc( boost::python::object main_module )
{
	using namespace boost::python;

	try
	{		
		while ( 1 )
		{
			boost::mutex::scoped_lock lock( g_mutex );
			//Py_BEGIN_ALLOW_THREADS;
			object GetI = main_module.attr("GetI");  

			object i = GetI();

			std::cout << extract< int >( i ) << ' ';
			//Py_END_ALLOW_THREADS;

			//Sleep( 500 );
		}
	}
	catch ( ... )
	{
		PyErr_Print();
	}
}

void ThreadFunc2( boost::python::object main_module )
{
	using namespace boost::python;

	try
	{		
		int i = 0;
		while ( 1 )
		{
			//Py_BEGIN_ALLOW_THREADS;

			boost::mutex::scoped_lock lock( g_mutex );


			object SetI = main_module.attr("SetI");  

			SetI( i++ );

			//Py_END_ALLOW_THREADS;


			//Sleep( 500 );
		}
	}
	catch ( ... )
	{
		PyErr_Print();
	}
}


int main()  
{  
	Py_Initialize();	//ʹ��python֮ǰ��Ҫ����Py_Initialize();����������г�ʼ��  

	//PyEval_InitThreads();


	boost::python::object main_module = boost::python::import("a");  

	boost::thread thread( boost::bind( &ThreadFunc, main_module ) );
	boost::thread thread2( boost::bind( &ThreadFunc2, main_module ) );


	thread.join();
	thread2.join();

	Py_Finalize();	//����Py_Finalize�������Py_Initialize���Ӧ�ġ�  

	return 0;  
}  