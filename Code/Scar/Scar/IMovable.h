/********************************************************************
	����ʱ��: 2011-9-27   15:27
	�ļ���:   IMovable.h
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     

*********************************************************************/


#ifndef IMovable_h__
#define IMovable_h__


#include <functional>

typedef void* LPVOID;

// �ص�����
typedef std::function< LPVOID( LPVOID ) > IMovableCallBackFuncType;


/*
** ���֣�IMovable
** ˵�������п��ƶ�����ĳ������
**
*/
class IMovable
{
public:
	virtual ~IMovable() {}

	//************************************
	// ������:  IMovable::Move
	// ����ֵ:  int
	// ��������:
	// ������   ����λ�ã�������ײ�ȵȣ���������������
	//************************************
	virtual int Move() = 0;							

	//************************************
	// ������:  IMovable::AddCallbackFunc
	// ����ֵ:  void
	// ����:    std::function< LPVOID > func
	// ��������:
	// ������   ���ÿ��Move()������ʱ�������õĻص�����
	//************************************
	virtual void AddCallbackFunc( std::function< LPVOID( LPVOID ) > func ) {}
};






#endif // IMovable_h__