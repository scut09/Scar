#include "UIManager.h"
#include <iostream>


//响应事件
void UIManager::OnEvent( const SEvent& event )
{
	Root->OnEvent( event );
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
