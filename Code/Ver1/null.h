//#include<python.h>#include<iostream>using
//namespace std;int main(){ Py_Initialize(); /* 
//										   ��ʼ��python������
//										   */ PyRun_SimpleString("print 'hello world!'"); /*  
//										   ����python���*/ Py_Finalize(); /*����python���������ͷ���Դ*/}����֮�󣬽����ڿ���̨���������hello world!��������ǵĵ�һ���������е�һ�к͵������Ǳ���ģ�����������������Ĵ���,������c++�����е���python�ű��еĺ���:������дһ���ű���
//										   ___def helloworld():  
//_______print 'hello world!' 
//	Ȼ�󱣴�Ϊfirst.py�ļ�����ǰ�����µ�Ŀ¼,��������:
