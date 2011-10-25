#ifndef NetworkPacket_h__
#define NetworkPacket_h__

#include "GameBag.h"

namespace Network
{
	const int MAX_ADDITION_LENGTH = 1024;

	//
	// ��Ϸ��
	//		 ����������󳤶�Ϊ1024,���ڴ˳��ȵ������зְ�����
	//
	struct PACKAGE
	{
		PACKAGE();

		// ����ƫ�Ƶ�ַ��ȡ��������,�������Ϊ12.
		char* GetData( int offsize );
		// ��ȡ��������
		char* GetData();
		// ��������,length����1024�ᱻ�Զ��ض�!
		int	SetData( const char* buffer, int length );
		// ��������,������0Ϊ����,һ�������ı�.
		int	SetData( const char* buffer );

		// ��ȡ������
		int	GetLength() const;
		// ��ȡ������

		int	GetCMD() const;
		// ���ð�����
		void SetCMD( int cmd );	

		// ��ȡ��ID
		int	GetID() const;	
		// ���ð�ID
		void SetID( int id );

	public:
		int		m_cmd;			// ������
		int		m_PackageID;	// ���ݰ����

	private:
		int		m_length;		// ���ݰ�����
		char	m_data[ MAX_ADDITION_LENGTH ];	// ���ݰ���������
	};


}


#endif // NetworkPacket_h__
