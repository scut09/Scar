#include "UIManager.h"
#include <iostream>

//
//��Ӧ�¼�
void UIManager::OnEvent( const SEvent& event )
{
	RootUIObject->OnEvent( event );
}
//
////��ȡ���ڵ�
//IUIObject* UIManager::GetRoot()
//{
//	return Root;
//}
//
//������
//void UIManager::RunTree()
//{
//	if ( Root )
//	{
//		Root->OnAnimate(Timer->getRealTime());
//		Root->DrawTree();
//	}
//}
//
////���������ӽڵ�
//bool UIManager::AddUINode( IUIObject* node, IUIObject* parent )
//{
//	parent->AddChild(node);
//	node->drop();
//	return true;
//}

IUIObject* UIManager::GetObjectByName( const std::string& name, IUIObject* node )
{
	//if ( node == NULL )
	//	node = Root;

	if ( node->GetName() == name )
		return node;

	for ( auto iter = node->GetChildren().begin(); iter != node->GetChildren().end(); ++iter )
	{
		IUIObject* it = GetObjectByName( name, (*iter) );
		if ( it != 0 )
			return it;
	}
	return 0;
}
