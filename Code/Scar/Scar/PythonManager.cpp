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