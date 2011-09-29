/********************************************************************
	创建时间: 2011-9-27   14:58
	文件名:   def.h
	作者:     华亮 Cedric Porter [ Stupid ET ]	
	说明:     

*********************************************************************/

#ifndef _DEF_H_
#define _DEF_H_

//
// Python 解释器支持
//
// 使用静态链接python
//
#define BOOST_PYTHON_STATIC_LIB

#include <boost\python.hpp> //前面所做的一切配置都是为了调用这个头文件和相关库  

//
// 因为Python虚拟机的GIL，所以同时只能有一个线程在运行，
// 我们如果要让自己的线程操纵python虚拟机，我们要先申请GIL
//
//
#define GIL_LOCK	{ PyGILState_STATE gstate; gstate = PyGILState_Ensure();   
#define GIL_UNLOCK	PyGILState_Release( gstate ); }

// 
// Boost线程库
//
#include <boost\thread.hpp>

//
// 断言
//
#include "boost/assert.hpp"

//
// Irrlicht引擎
//
#include <irrlicht.h>



#endif