/********************************************************************
	����ʱ��: 2011-9-27   14:58
	�ļ���:   def.h
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     

*********************************************************************/

#ifndef _DEF_H_
#define _DEF_H_

//
// Python ������֧��
//
// ʹ�þ�̬����python
//
#define BOOST_PYTHON_STATIC_LIB

#include <boost\python.hpp> //ǰ��������һ�����ö���Ϊ�˵������ͷ�ļ�����ؿ�  

//
// ��ΪPython�������GIL������ͬʱֻ����һ���߳������У�
// �������Ҫ���Լ����̲߳���python�����������Ҫ������GIL
//
//
#define GIL_LOCK	{ PyGILState_STATE gstate; gstate = PyGILState_Ensure();   
#define GIL_UNLOCK	PyGILState_Release( gstate ); }

// 
// Boost�߳̿�
//
#include <boost\thread.hpp>

//
// ����
//
#include "boost/assert.hpp"

//
// Irrlicht����
//
#include <irrlicht.h>



#endif