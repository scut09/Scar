#include <boost/python.hpp>  
//#include <boost/thread.hpp>
#include <iostream>  
#include <string>

#include <Windows.h>
#include <cstdlib>

using namespace boost::python;  

void hello( char * msg )  
{  
	std::cout<<"Hello from C :)   " << msg << std::endl;  
}  

BOOST_PYTHON_MODULE(emb)  
{  
	def("hello", hello);  
}  



class PyThreadStateLock 
{
public:  
	PyThreadStateLock(void)   
	{     
		state = PyGILState_Ensure( );  
	}    
	~PyThreadStateLock(void)   
	{ 
		PyGILState_Release( state );  
	} 
private: 
	PyGILState_STATE state; 
}; 

int x = rand();
int y = rand();
int z = rand();

CRITICAL_SECTION lock;


DWORD WINAPI ThreadFUnc( PVOID param )
{
	while ( 1 )
	{
		int tx, ty, tz;
		std::cin >> tx >> ty >> tz;
		EnterCriticalSection( &lock );
		x = tx;
		y = ty;
		z = tz;
		LeaveCriticalSection( &lock );
	}

	return 0;
}



void Run()
{
	try  
	{  
		initemb();  

		object main_module = import("__main__");  
		object main_namespace = main_module.attr("__dict__");  
		//object run = exec_file( "client.py", main_namespace, main_namespace );

		PyObject * pModule = NULL; //声明变量   
		PyObject * pFunc = NULL;       //声明变量  

		object main = import("client");
		object id = main.attr("Connect")();

		object Run = main.attr("Run");
		object Send = main.attr("Send");
		object SetPos = main.attr("SetPos");

		std::cout << extract<char*>(id) << std::endl;

		while ( 1 )
		{
			//std::string input;
			//std::cin >> input;
			//if ( input == "end" )
			//	break;

			int tx, ty, tz;
			EnterCriticalSection( &lock );
			tx = x;
			ty = y;
			tz = z;
			LeaveCriticalSection( &lock );

			Run();
			Send();
			SetPos( tx, ty, tz );

			Sleep( 10 );
		}	



	}  
	catch(...)  
	{  
		PyErr_Print();  
	}  

	std::cout << "ET";


}






//boost::mutex m_io_monitor;
//
//
//
//void do_task()
//{
//	for (int i = 0; i < 10; ++i)
//	{
//		{
//			boost::mutex::scoped_lock lock(m_io_monitor);
//			PyRun_SimpleString("from time import time,ctime/nprint 'Today is',ctime(time())/n");
//		}
//
//		boost::xtime xt;
//		boost::xtime_get(&xt, boost::TIME_UTC); // initialize xt with current time
//		xt.sec += 1; // change xt to next second
//		boost::thread::sleep(xt); // do sleep
//	}
//}

void SayHi()
{
	std::cout << "Hi";
}


int main()  
{  
	Py_Initialize();  
	PyEval_InitThreads(); 
	//PyEval_ReleaseThread(PyThreadState_Get()); 

	//boost::thread func(SayHi);
	//func.join();

	InitializeCriticalSection( &lock );


	DWORD dwID;
	HANDLE handle = CreateThread( NULL, 0, ThreadFUnc, (PVOID)0, 0, &dwID );	

	////if ( handle == 0 )
	////{
	////	std::cout << "Failed";
	////}

	////Sleep( 1000 );
	////exec_file("client.py", main_namespace );  

	WaitForSingleObject( handle, 0 );

	Run();

	PyGILState_Ensure(); 
	Py_Finalize();
	return 0;  
}  