#include <boost/python.hpp>  
#include <iostream>  
#include <string>

#include <Windows.h>

using namespace boost::python;  

DWORD WINAPI ThreadFUnc( PVOID param )
{
	object main = *(object*)param;

	//std::cout << extract<int>(main["port"]) ;

	
	

	return 0;
}

void hello( char * msg )  
{  
	std::cout<<"Hello from C :)   " << msg << std::endl;  
}  

BOOST_PYTHON_MODULE(emb)  
{  
	def("hello", hello);  
}  

int main()  
{  
	Py_Initialize();  

	try  
	{  
		initemb();  

		object main_module = import("__main__");  
		object main_namespace = main_module.attr("__dict__");  
		//object run = exec_file( "client.py", main_namespace, main_namespace );

		PyObject * pModule = NULL; //声明变量   
		PyObject * pFunc = NULL;       //声明变量  
		//pModule = PyImport_ImportModule("client");  //这里是要调用的文件名  
		//pFunc = PyObject_GetAttrString(pModule, "Connect"); //这里是要调用的函数名  
		//PyEval_CallObject(pFunc, NULL);            //调用函数  

		//PyObject * pRun = PyObject_GetAttrString(pModule, "Run");
		//PyObject * pSend = PyObject_GetAttrString(pModule, "Send");

		object main = import("client");
		object id = main.attr("Connect")();

		object Run = main.attr("Run");
		object Send = main.attr("Send");
		object SetPos = main.attr("SetPos");

		//PyRun_SimpleString( "Connect()" );

		std::cout << extract<char*>(id) << std::endl;

		while ( 1 )
		{
			std::string input;
			std::cin >> input;
			if ( input == "end" )
				break;

			Run();
			Send();
			SetPos( 1, 2, 3 );

			//PyRun_SimpleString( "setPos( 1.1, 2.2, 3.3)" );
			//PyEval_CallObject( pRun, NULL);            //调用函数  
			//PyEval_CallObject( pSend, NULL);            //调用函数  
		}	



		//DWORD dwID;
		//HANDLE handle = CreateThread( NULL, 0, ThreadFUnc, (PVOID)&main_namespace, 0, &dwID );	

		//if ( handle == 0 )
		//{
		//	std::cout << "Failed";
		//}

		//Sleep( 1000 );
		//exec_file("client.py", main_namespace );  

		//WaitForSingleObject( handle, 0 );

	}  
	catch(...)  
	{  
		PyErr_Print();  
	}  

	std::cout << "ET";

	Py_Finalize();

	return 0;  
}  