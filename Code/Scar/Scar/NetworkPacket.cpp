/********************************************************************
    创建时间: 2011-10-25   20:26
    文件名:   NetworkPacket.cpp
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     网络数据包

*********************************************************************/


#include "NetworkPacket.h"


Network::PACKAGE::PACKAGE()
{
	m_length = 13;			
	m_data[0] = '\0';
	m_PackageID = -1;
}

const char* Network::PACKAGE::GetData( int offsize ) const
{
	return (char*)this + offsize;
}

const char* Network::PACKAGE::GetData() const
{
	return m_data;
}

int Network::PACKAGE::SetData( const char* buffer, int length )
{
	if ( length > MAX_ADDITION_LENGTH )
	{
		length = MAX_ADDITION_LENGTH;
	}

	int i = 0;
	for ( ; i < length; i++ )
	{
		m_data[i] = buffer[i];
	}
	m_length = PackHeadLength + i;

	return i;
}

int Network::PACKAGE::SetData( const char* buffer )
{
	int i = 0;
	for ( ; i < MAX_ADDITION_LENGTH; i++ )
	{
		m_data[i] = buffer[i];
		if ( '\0' == buffer[i] )
		{
			break;
		}
	}
	i++;	//数量
	m_length = PackHeadLength + i;
	return i;
}

int Network::PACKAGE::GetLength() const
{
	return m_length;
}

int Network::PACKAGE::GetCMD() const
{
	return m_cmd;
}

void Network::PACKAGE::SetCMD( int cmd )
{
	m_cmd = cmd;
}

int Network::PACKAGE::GetID() const
{
	return m_PackageID;
}

void Network::PACKAGE::SetID( int id )
{
	m_PackageID = id;
}
