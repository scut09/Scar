#include "UIManager.h"
#include <iostream>

//
//响应事件
void UIManager::OnEvent( const SEvent& event )
{
	RootUIObject->OnEvent( event );
}
//
////获取根节点
//IUIObject* UIManager::GetRoot()
//{
//	return Root;
//}
//
//运行树
//void UIManager::RunTree()
//{
//	if ( Root )
//	{
//		Root->OnAnimate(Timer->getRealTime());
//		Root->DrawTree();
//	}
//}
//
////向树中增加节点
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
