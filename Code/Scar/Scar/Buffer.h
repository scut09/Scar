/********************************************************************
    ����ʱ��: 2011-10-27   18:23
    �ļ���:   Buffer.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     �ṩһ������أ�֧���߳�ͬ����
			�������Ϊ��ʱ���������Get��������ֱ������ز�Ϊ�ա�
			���仰˵��Getһ���᷵��һ������������ͻ����������档

*********************************************************************/

#ifndef Buffer_h__
#define Buffer_h__

#include <queue>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

namespace Network
{

// ���������������ߵĻ��壬�����Get��ʱ�򻺳�Ϊ�գ���������ֱ����Ϊ��
template< typename T >
class Buffer
{
	std::queue<T>	m_queue;
	boost::mutex	m_mutex;
	boost::condition_variable_any m_cond_get;

public:
	void Put( const T& element )
	{
		{
			boost::mutex::scoped_lock lock( m_mutex );
			m_queue.push( element );
		}

		m_cond_get.notify_one();		// ֪ͨGet�Ѿ��ж�������
	}

	T Get()
	{
		T head;

		{
			boost::mutex::scoped_lock lock( m_mutex );

			while ( 1 )
			{
				if ( m_queue.empty() )
				{
					m_cond_get.wait( m_mutex );
					continue;
				}

				head = m_queue.front();
				m_queue.pop();
				break;
			}

		}

		return head;
	}

	bool IsEmpty() const
	{
		boost::mutex::scoped_lock lock( m_mutex );

		return m_queue.empty();
	}
};

}

#endif // Buffer_h__