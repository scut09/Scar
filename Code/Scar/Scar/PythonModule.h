/********************************************************************
	����ʱ��: 2011-9-29   9:59
	�ļ���:   PythonModule.h
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     ��C++���ർ����Python��

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