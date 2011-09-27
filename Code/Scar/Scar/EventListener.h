/*
** 作者：华亮
** 说明：
**
*/


#ifndef _EVENT_LISTEN_H
#define _EVENT_LISTEN_H

#include <irrlicht.h>
#include <functional>

using namespace irr;

// MyEventReceiver的事件处理回调函数类型
typedef std::function< void*( const SEvent& ) > IEventReceiverCallbackFuncType;

class MyEventReceiver : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event)
	{
		m_callbackFunc( event );  // 调用事件处理回调函数处理事件

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

	MyEventReceiver( IEventReceiverCallbackFuncType func ) : m_callbackFunc( func )
	{
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];

	IEventReceiverCallbackFuncType m_callbackFunc;
};

#endif