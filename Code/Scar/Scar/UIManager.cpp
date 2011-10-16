#include "UIManager.h"
#include <iostream>


void UIManager::OnEvent( const SEvent& event )
{
	std::cout << event.MouseInput.X << ' ' << event.MouseInput.Y << std::endl;



}

//获取根节点
IUIObject* UIManager::GetRoot()
{
	return Root;
}

//运行树
void UIManager::RunTree()
{
	Root->OnAnimate(Timer->getRealTime());
	Root->DrawTree();
}

//向树中增加节点
bool UIManager::AddUINode( IUIObject* node, IUIObject* parent )
{
	parent->AddChild(node);
	return true;
}
