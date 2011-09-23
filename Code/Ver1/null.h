//#include<python.h>#include<iostream>using
//namespace std;int main(){ Py_Initialize(); /* 
//										   初始化python解释器
//										   */ PyRun_SimpleString("print 'hello world!'"); /*  
//										   调用python语句*/ Py_Finalize(); /*结束python解释器，释放资源*/}运行之后，将会在控制台程序下输出hello world!这就是我们的第一个程序，其中第一行和第三行是必须的，让我们来看看更多的代码,这是在c++程序中调用python脚本中的函数:我们先写一个脚本：
//										   ___def helloworld():  
//_______print 'hello world!' 
//	然后保存为first.py文件到当前工程下的目录,代码如下:
