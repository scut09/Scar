///*
//** �ļ�����main.cpp
//** �����ˣ�����
//** ˵����
//**
//*/
//
//
//#include "def.h"
//#include <iostream>
//
//boost::mutex g_mutex;
//
//void ThreadFunc( boost::python::object main_module )
//{
//	using namespace boost::python;
//
//	try
//	{		
//		while ( 1 )
//		{
//			boost::mutex::scoped_lock lock( g_mutex );
//	
//			object GetI = main_module.attr("GetI");  
//			object i = GetI();
//			std::cout << extract< int >( i ) << ' ';
//		}
//	}
//	catch ( ... )
//	{
//		PyErr_Print();
//	}
//}
//
//void ThreadFunc2( boost::python::object main_module )
//{
//	using namespace boost::python;
//
//	try
//	{		
//		int i = 0;
//		while ( 1 )
//		{
//
//			boost::mutex::scoped_lock lock( g_mutex );
//
//			object SetI = main_module.attr("SetI");  
//
//			SetI( i++ );
//		}
//	}
//	catch ( ... )
//	{
//		PyErr_Print();
//	}
//}
//
//
//int main()  
//{  
//	Py_Initialize();	//ʹ��python֮ǰ��Ҫ����Py_Initialize();����������г�ʼ��  
//
//	boost::python::object main_module = boost::python::import("a");  
//
//	boost::thread thread( boost::bind( &ThreadFunc, main_module ) );
//	boost::thread thread2( boost::bind( &ThreadFunc2, main_module ) );
//
//	thread.join();
//	thread2.join();
//
//	Py_Finalize();	//����Py_Finalize�������Py_Initialize���Ӧ�ġ�  
//
//	return 0;  
//}  