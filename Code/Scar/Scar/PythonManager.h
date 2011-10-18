/********************************************************************
    ����ʱ��: 2011-10-8   16:05
    �ļ���:   PythonManager.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     �ṩȫ�ֵ�python����

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

	object m_sceneModule;	// python����ģ��
	object m_modelLoader;	// pythonģ��ģ��

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