#include "UIManager.h"
#include <iostream>


void UIManager::OnEvent( const SEvent& event )
{
	std::cout << event.MouseInput.X << ' ' << event.MouseInput.Y << std::endl;



}

//��ȡ���ڵ�
UIObject* UIManager::GetRoot()
{
	return Root;
}

//������
void UIManager::RunTree()
{
	Root->OnAnimate(Timer->getRealTime());
	Root->DrawTree();
}
