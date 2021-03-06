/********************************************************************
    创建时间: 2011-10-8   16:06
    文件名:   PythonManager.cpp
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     

*********************************************************************/

#include "PythonManager.h"
#include "MyIrrlichtEngine.h"

PythonManager* PythonManager::m_pPythonManager = 0;

PythonManager* PythonManager::GetPythonManager()
{
	AssurePythonManager();

	return m_pPythonManager;
}

void AddPythonPath()
{
	try
	{
		using namespace boost::python;

		object main_module = import( "__main__" );
		object main_namespace = main_module.attr( "__dict__" );
		//object sys = import( "sys" );
		object ignored = exec( 
			"import sys\n"
			"sys.path.append('./python')\n", main_namespace );
		//ignored = exec( "print sys.path", main_namespace );

		object UILoader = import( "UILoader" );
		object SetScreen = UILoader.attr( "SetScreen" );
		SetScreen( MyIrrlichtEngine::screen_width, MyIrrlichtEngine::screen_height );
	}
	catch ( ... )
	{
		PyErr_Print();
	}
}
