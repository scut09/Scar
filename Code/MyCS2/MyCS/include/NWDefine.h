///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/11 10:46
//Describe: ����� �ṹ����
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
		///	@brief ��ȡ����
		///	@param [in] offsize:��ַƫ����
		///	@return void
		//////////////////////////////
		char* Getdata(int offsize)
		{
			return (char*)this+offsize;
		}

		//////////////////////////////
		///	@brief ��������
		///	@param [in] buffer:ָ�����ݵ�ָ��
		///	@param [in] length:Ҫ�����ĳ���
		///	@return ʵ�ʿ����ĳ���
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
		///	@brief �������� �Զ����㳤�� �� ��\0�� ��β
		///	@param [in] buffer:ָ�����ݵ�ָ��
		///	@return ʵ�ʿ����ĳ���
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
			i++;	//����
			m_length = PackHeadLength + i;
			return i;
		}

		//////////////////////////////
		///	@brief 	��ȡ���ݰ�����
		///	@return ���ݰ�����
		//////////////////////////////
		int			GetLength()
		{
			return m_length;
		}

		//////////////////////////////
		///	@brief ��ð�����	
		///	@return void
		//////////////////////////////
		int			GetCMD()
		{
			return m_cmd;
		}

		//////////////////////////////
		///	@brief ���ð�����
		///	@param [in] cmd:������
		///	@return void
		//////////////////////////////
		void		SetCMD(int cmd)
		{			
			m_cmd = cmd;
		}	

		//////////////////////////////
		///	@brief ���ð�����
		///	@param [in] cmd:������
		///	@return void
		//////////////////////////////
		int		GetID()
		{			
			return m_PackageID;
		}	

		//////////////////////////////
		///	@brief ���ð�����
		///	@param [in] cmd:������
		///	@return void
		//////////////////////////////
		void		SetID(int id)
		{			
			m_PackageID = id;
		}


	public:
		int		m_cmd;			//������
		int		m_PackageID;	//���ݰ����
	private:
		int		m_length;		//���ݰ�����
		char	m_data[1024];	//
	};

}

#endif