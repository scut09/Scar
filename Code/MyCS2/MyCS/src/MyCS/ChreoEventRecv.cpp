#include "ChreoEventRecv.h"

ChreoEventRecv::ChreoEventRecv(void)
{
	for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
	m_BtnID = -1;
	m_mouseClick = false;
	m_mouseMove = false;
}

ChreoEventRecv::~ChreoEventRecv(void)
{
}

bool ChreoEventRecv::OnEvent( const SEvent& event )
{
	
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)	//键盘事件
	{	
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	}
	else if (event.EventType == EET_GUI_EVENT)			//UI事件
	{
		//s32 id = event.GUIEvent.Caller->getID();
		
		if(gui::EGET_MENU_ITEM_SELECTED == event.GUIEvent.EventType)
		{
			gui::IGUIContextMenu* menu = (gui::IGUIContextMenu*)event.GUIEvent.Caller;
			m_BtnID = menu->getItemCommandId(menu->getSelectedItem());
		}		
	}
	else if(event.EventType == EET_MOUSE_INPUT_EVENT)	//鼠标事件
	{
		if(event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP)
		{
			m_mouseClick = true;
		}
		else if(event.MouseInput.Event == EMIE_MOUSE_MOVED)
		{

			m_x = event.MouseInput.X;
			m_y = event.MouseInput.Y;

			if (m_x == 512 && m_y == 384)
			{
				m_mouseMove = false;
			}
			else
			{
				m_mouseMove = true;
			}
			
		}
	}
	return false;
}

bool ChreoEventRecv::IsKeyDown( EKEY_CODE keyCode ) const
{
	return KeyIsDown[keyCode];
}

int ChreoEventRecv::GetBtnDownID()
{
	int temp = m_BtnID;
	m_BtnID = -1;
	return temp;
}

bool ChreoEventRecv::IsMouseClick()
{
	if (m_mouseClick)
	{
		m_mouseClick = false;
		return true;
	}
	return false;
}

bool ChreoEventRecv::IsMouseMove( int& x, int& y )
{
	if (m_mouseMove)
	{
		m_mouseMove = false;
		x = m_x;
		y = m_y;
		return true;
	}
	return false;
}