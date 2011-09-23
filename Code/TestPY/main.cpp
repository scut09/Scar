#include <boost/python.hpp>  
#include <iostream>  

using namespace boost::python;  

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
		exec_file("WEB.py", main_namespace);  
	}  
	catch(...)  
	{  
		PyErr_Print();  
	}  

	Py_Finalize();

	return 0;  
}  