#include "UIManager.h"
#include <iostream>


void UIManager::OnEvent( const SEvent& event )
{
	std::cout << event.MouseInput.X << ' ' << event.MouseInput.Y << std::endl;



}

//获取根节点
UIObject* UIManager::GetRoot()
{
	return Root;
}

//运行树
void UIManager::RunTree()
{
	Root->OnAnimate(Timer->getRealTime());
	Root->DrawTree();
}
