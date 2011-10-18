/********************************************************************
    ����ʱ��: 2011-10-8   16:06
    �ļ���:   PythonManager.cpp
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     

*********************************************************************/

#include "PythonManager.h"

PythonManager* PythonManager::m_pPythonManager = 0;

PythonManager* PythonManager::GetPythonManager()
{
	AssurePythonManager();

	return m_pPythonManager;
}

void InitPythonPath()
{
	try
	{
		using namespace boost::python;

		object main_module = import( "__main__" );
		object main_namespace = main_module.attr( "__dict__" );
		//object sys = import( "sys" );
		object ignored = exec( 
			"import sys\n"
			"sys.path.append('./python')\n", 
			main_namespace );
		//ignored = exec( "print sys.path", main_namespace );
	}
	catch ( ... )
	{
		PyErr_Print();
	}
}
