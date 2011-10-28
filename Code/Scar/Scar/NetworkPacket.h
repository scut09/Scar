/********************************************************************
    创建时间: 2011-10-25   20:22
    文件名:   NetworkPacket.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     网络数据包

*********************************************************************/

#ifndef NetworkPacket_h__
#define NetworkPacket_h__


namespace Network
{
	const int MAX_ADDITION_LENGTH = 1024;			// 数据包附加信息最大值
	const int PackHeadLength = 16;					// 数据包头的大小
	const unsigned int MagicNumber = 0xf3ac43de;	// 魔数，用于检测包的有效性

	//
	// 游戏包
	//		 附加数据最大长度为1024,长于此长度的请自行分包发送
	//
	struct PACKAGE
	{
		PACKAGE();

		// 根据偏移地址获取附加数据,数据起点为12.
		const char* GetData( int offsize ) const;
		// 获取附加数据
		const char* GetData() const;
		// 设置数据,length大于1024会被自动截断!
		int	SetData( const char* buffer, int length );
		// 设置数据,数据以0为结束,一般用于文本.
		int	SetData( const char* buffer );

		// 获取包长度
		int	GetLength() const;
		// 获取包类型

		int	GetCMD() const;
		// 设置包类型
		void SetCMD( int cmd );	

		// 获取包ID
		int	GetID() const;	
		// 设置包ID
		void SetID( int id );

		// 获取魔数
		unsigned int GetMagicNumber() const;

	public:
		unsigned int	m_magic_number;	// 魔数，用于检查是否有效
		int				m_cmd;			// 包命令
		int				m_PackageID;	// 数据包编号

	private:
		int		m_length;		// 数据包长度
		char	m_data[ MAX_ADDITION_LENGTH ];	// 数据包其他部分
	};


}


#endif // NetworkPacket_h__
