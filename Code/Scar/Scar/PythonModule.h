/********************************************************************
	创建时间: 2011-9-29   9:59
	文件名:   PythonModule.h
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     将C++的类导出到Python中

*********************************************************************/


#ifndef PythonModule_h__
#define PythonModule_h__

#include "PythonWrapper.h"
#include "AnimationManager.h"

extern "C" void initEngine(); 
extern "C" void initUI(); 
extern "C" void initGameSceneModule();
extern "C" void initPythonSceneMgr();

#endif // PythonModule_h__