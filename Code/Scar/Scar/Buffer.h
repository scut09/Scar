/********************************************************************
    创建时间: 2011-10-27   18:23
    文件名:   Buffer.h
    作者:     华亮 Cedric Porter [ Stupid ET ]	
    说明:     提供一个缓冲池，支持线程同步。
			当缓冲池为空时，如果调用Get它会阻塞直至缓冲池不为空。
			换句话说，Get一定会返回一个东西，否则就会阻塞在里面。

*********************************************************************/

#ifndef Buffer_h__
#define Buffer_h__

#include <queue>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

namespace Network
{

// 类似生产者消费者的缓冲，如果在Get的时候缓冲为空，它会阻塞直到不为空
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

		m_cond_get.notify_one();		// 通知Get已经有东西加入
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