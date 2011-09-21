#include "Helper.h"

CHelper::CHelper(void)
{
}

CHelper::~CHelper(void)
{
}

char* CHelper::wchar_to_char( const wchar_t* lpchar )
{
	int length = 0;
	char c = lpchar[length];
	while ( c != '\0')	//计算长度
	{
		length++;
		c = lpchar[length];
	}
	char* temp = new char[length+1];

	for (int i = 0; i < length; i++)
	{
		temp[i] = lpchar[i];
	}
	temp[length] = '\0';
	return temp;

}

int CHelper::CopyChar( char * des, int maxLen, const char* src )
{
	if(0 == des || 0 == src)
	{
		return 0;
	}
	int len = 0;
	while(len < maxLen)
	{
		des[len] = src[len];
		len++;
	}
	return len + 1;
}

wchar_t* CHelper::char_to_wchar( const char* lpchar )
{
	int length = 0;
	char c = lpchar[length];
	while ( c != '\0')	//计算长度
	{
		length++;
		c = lpchar[length];
	}
	wchar_t* temp = new wchar_t[length+1];

	for (int i = 0; i < length; i++)
	{
		temp[i] = lpchar[i];
	}
	temp[length] = '\0';
	return temp;
}