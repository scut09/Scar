/********************************************************************
	����ʱ��: 2011-9-27   14:56
	�ļ���:   EventListener.h
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     

*********************************************************************/


#ifndef _EVENT_LISTEN_H
#define _EVENT_LISTEN_H

#include <irrlicht.h>
#include <functional>

using namespace irr;

// MyEventReceiver���¼�����ص���������
typedef std::function< void*( const SEvent& ) > IEventReceiverCallbackFuncType;

class MyEventReceiver : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event)
	{
		m_callbackFunc( event );  // �����¼�����ص����������¼�

		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	virtual void SetEventCallbackFunc( IEventReceiverCallbackFuncType func )
	{
		m_callbackFunc = func;
	}

	MyEventReceiver() 
	{
		m_callbackFunc = []( const SEvent& event )->void* { return 0; };
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];

	IEventReceiverCallbackFuncType m_callbackFunc;
};

#endif