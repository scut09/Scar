/*
** 作者：华亮
** 说明：
**
*/

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
// Boost线程库
//
#include <boost\thread.hpp>


//
// Irrlicht引擎
//
#include <irrlicht.h>



#endif