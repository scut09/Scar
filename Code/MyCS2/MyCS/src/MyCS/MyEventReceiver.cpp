#include "MyEventReceiver.h"

CMyEventReceiver::CMyEventReceiver(void)
{
	for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
	m_BtnID = -1;
}

CMyEventReceiver::~CMyEventReceiver(void)
{
}

bool CMyEventReceiver::OnEvent( const SEvent& event )
{
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	{	
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		
	}
	else if (event.EventType == EET_GUI_EVENT)
	{
		s32 id = event.GUIEvent.Caller->getID();
		if(5 /*EGET_BUTTON_CLICKED*/ == event.GUIEvent.EventType)
		{
			m_BtnID = id;
		}
		else
		{
			m_BtnID = -1;
		}
	}	
	return false;

}

bool CMyEventReceiver::IsKeyDown( EKEY_CODE keyCode ) const
{
	return KeyIsDown[keyCode];
}

int CMyEventReceiver::GetBtnDownID()
{	
	int temp = m_BtnID;
	m_BtnID = -1;
	return temp;
}