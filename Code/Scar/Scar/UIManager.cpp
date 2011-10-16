#include "UIManager.h"
#include <iostream>


void UIManager::OnEvent( const SEvent& event )
{
	std::cout << event.MouseInput.X << ' ' << event.MouseInput.Y << std::endl;



}

//��ȡ���ڵ�
IUIObject* UIManager::GetRoot()
{
	return Root;
}

//������
void UIManager::RunTree()
{
	Root->OnAnimate(Timer->getRealTime());
	Root->DrawTree();
}

//���������ӽڵ�
bool UIManager::AddUINode( IUIObject* node, IUIObject* parent )
{
	parent->AddChild(node);
	return true;
}
