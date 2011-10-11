/********************************************************************
    创建时间: 2011-10-8   16:06
    文件名:   PythonManager.cpp
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     

*********************************************************************/

#include "PythonManager.h"

PythonManager* PythonManager::m_pPythonManager = 0;

PythonManager* PythonManager::GetPythonManager()
{
	AssurePythonManager();

	return m_pPythonManager;
}