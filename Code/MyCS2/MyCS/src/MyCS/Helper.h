///////////////////////////////////////////////////////
//  copyright:	Tian's 2009-2010
//  by author:	Tian
//create date:	2009/11/10 1:10
//description:	...
///////////////////////////////////////////////////////

#ifndef CHelper_h
#define CHelper_h

#pragma once

class CHelper
{
public:
	CHelper(void);
	~CHelper(void);
public:	
	//---------------------------------------
	//des:ʹ�����Ӧ�ð�ָ��ɾ��
	//---------------------------------------
	static char* wchar_to_char(const wchar_t* lpchar);

	//---------------------------------------
	//des:ʹ�����Ӧ�ð�ָ��ɾ��
	//---------------------------------------
	static wchar_t* char_to_wchar(const char* lpchar);

	///////////////////////////////////////
	//desc:�ַ�������
	//parm [in] des:Ŀ���ַ���
	//parm [in] maxLen:Ŀ��ɿ�������󳤶�
	//parm [in] src:Դ�ַ���
	//return:�����ĳ���
	///////////////////////////////////////
	static int	CopyChar(char * des, int maxLen, const char* src);
};

#endif