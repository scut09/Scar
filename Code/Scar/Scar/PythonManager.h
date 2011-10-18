/********************************************************************
    创建时间: 2011-10-8   16:05
    文件名:   PythonManager.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     提供全局的python访问

*********************************************************************/

#ifndef PythonManager_h__
#define PythonManager_h__

#include "def.h"

using namespace boost::python;

void InitPythonPath();

class PythonManager
{

	PythonManager()
	{
		Init();
	}

	static PythonManager* m_pPythonManager;

	object m_sceneModule;	// python场景模块
	object m_modelLoader;	// python模型模块

	void Init()
	{
		using namespace boost::python;

		try
		{
			m_modelLoader = import( "ModelLoader" );
			m_sceneModule = import( "scene" );
		}
		catch ( ... )
		{
			PyErr_Print();
		}
	}

	static void AssurePythonManager()
	{
		if ( ! m_pPythonManager )
		{
			m_pPythonManager = new PythonManager;
		}
	}


public:
	static PythonManager* GetPythonManager();

	object GetModelLoader()
	{
		return m_modelLoader;
	}

};

#endif // PythonManager_h__