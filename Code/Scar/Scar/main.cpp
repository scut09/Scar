/*
** 文件名：main.cpp
** 创建人：华亮
** 说明：
**
*/

/*
	编译前请设置boost的include路径和lib路径
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
	Py_Initialize();	//使用python之前，要调用Py_Initialize();这个函数进行初始化  

	//PyEval_InitThreads();


	boost::python::object main_module = boost::python::import("a");  

	boost::thread thread( boost::bind( &ThreadFunc, main_module ) );
	boost::thread thread2( boost::bind( &ThreadFunc2, main_module ) );


	thread.join();
	thread2.join();

	Py_Finalize();	//调用Py_Finalize，这个根Py_Initialize相对应的。  

	return 0;  
}  