///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/11 10:46
//Describe: 网络层 结构定义
///////////////////////////////////////////////////////////////////////

#ifndef  NWDefine_h
#define  NWDefine_h

#include <Windows.h>

namespace Net
{
	const int PackHeadLength = 12;

	struct PACKAGE
	{
		PACKAGE()
		{
			m_length = 13;			
			m_data[0] = '\0';
			m_PackageID = -1;
		}
		//////////////////////////////
		///	@brief 获取数据
		///	@param [in] offsize:地址偏移量
		///	@return void
		//////////////////////////////
		char* Getdata(int offsize)
		{
			return (char*)this+offsize;
		}

		//////////////////////////////
		///	@brief 设置数据
		///	@param [in] buffer:指向数据的指针
		///	@param [in] length:要拷贝的长度
		///	@return 实际拷贝的长度
		//////////////////////////////
		int			Setdata(const char* buffer, int length)
		{
			if (length > 1024)
			{
				length = 1024;
			}
			int i = 0;
			for (; i < length; i++)
			{
				m_data[i] = buffer[i];
			}
			m_length = PackHeadLength + i;
			return i;
		}

		//////////////////////////////
		///	@brief 设置数据 自动计算长度 以 ‘\0’ 结尾
		///	@param [in] buffer:指向数据的指针
		///	@return 实际拷贝的长度
		//////////////////////////////
		int			Setdata(const char* buffer)
		{
			int i = 0;
			for (; i < 1024; i++)
			{
				m_data[i] = buffer[i];
				if ('\0' == buffer[i])
				{
					break;
				}
			}
			i++;	//数量
			m_length = PackHeadLength + i;
			return i;
		}

		//////////////////////////////
		///	@brief 	获取数据包长度
		///	@return 数据包长度
		//////////////////////////////
		int			GetLength()
		{
			return m_length;
		}

		//////////////////////////////
		///	@brief 获得包命令	
		///	@return void
		//////////////////////////////
		int			GetCMD()
		{
			return m_cmd;
		}

		//////////////////////////////
		///	@brief 设置包命名
		///	@param [in] cmd:包命名
		///	@return void
		//////////////////////////////
		void		SetCMD(int cmd)
		{			
			m_cmd = cmd;
		}	

		//////////////////////////////
		///	@brief 设置包命名
		///	@param [in] cmd:包命名
		///	@return void
		//////////////////////////////
		int		GetID()
		{			
			return m_PackageID;
		}	

		//////////////////////////////
		///	@brief 设置包命名
		///	@param [in] cmd:包命名
		///	@return void
		//////////////////////////////
		void		SetID(int id)
		{			
			m_PackageID = id;
		}


	public:
		int		m_cmd;			//包命令
		int		m_PackageID;	//数据包编号
	private:
		int		m_length;		//数据包长度
		char	m_data[1024];	//
	};

}

#endif