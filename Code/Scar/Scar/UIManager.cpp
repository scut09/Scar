#include "UIManager.h"
#include <iostream>


//��Ӧ�¼�
void UIManager::OnEvent( const SEvent& event )
{
	Root->OnEvent( event );
}

//��ȡ���ڵ�
IUIObject* UIManager::GetRoot()
{
	return Root;
}

//������
void UIManager::RunTree()
{
	if ( Root )
	{
		Root->OnAnimate(Timer->getRealTime());
		Root->DrawTree();
	}
}

//���������ӽڵ�
bool UIManager::AddUINode( IUIObject* node, IUIObject* parent )
{
	parent->AddChild(node);
	node->drop();
	return true;
}
