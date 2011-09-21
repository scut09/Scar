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
	//des:使用完后应该把指针删除
	//---------------------------------------
	static char* wchar_to_char(const wchar_t* lpchar);

	//---------------------------------------
	//des:使用完后应该把指针删除
	//---------------------------------------
	static wchar_t* char_to_wchar(const char* lpchar);

	///////////////////////////////////////
	//desc:字符串拷贝
	//parm [in] des:目标字符串
	//parm [in] maxLen:目标可拷贝的最大长度
	//parm [in] src:源字符串
	//return:拷贝的长度
	///////////////////////////////////////
	static int	CopyChar(char * des, int maxLen, const char* src);
};

#endif