#include "UIManager.h"
#include <iostream>


void UIManager::OnEvent( const SEvent& event )
{
	//std::cout << event.MouseInput.X << ' ' << event.MouseInput.Y << std::endl;
	if ( event.EventType == EET_MOUSE_INPUT_EVENT && event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN )
		std::cout<< event.MouseInput.ButtonStates <<std::endl;
	if ( event.EventType == EET_KEY_INPUT_EVENT )
	{
		std::cout << event.KeyInput.PressedDown << std::endl;
		std::cout << event.KeyInput.Key << std::endl;
		std::cout << event.KeyInput.Char << std::endl;
	}

}

//获取根节点
IUIObject* UIManager::GetRoot()
{
	return Root;
}

//运行树
void UIManager::RunTree()
{
	if ( Root )
	{
		Root->OnAnimate(Timer->getRealTime());
		Root->DrawTree();
	}
}

//向树中增加节点
bool UIManager::AddUINode( IUIObject* node, IUIObject* parent )
{
	parent->AddChild(node);
	node->drop();
	return true;
}
