#ifndef UIManager_h__
#define UIManager_h__

#include <irrlicht.h>
#include "IUIObject.h"

using namespace irr;

class UIManager
{
public:
	UIManager( ITimer* timer ) : Timer(timer), Root(NULL), Focus(NULL), Over(NULL)
	{
		
	}
	bool SetRoot( IUIObject* root )
	{
		Root = root;
		return true;
	}
	//获取UI树根节点
	IUIObject* GetRoot();
	//向UI树中插入节点
	bool AddUINode( IUIObject* node, IUIObject* parent )
	{
		parent->AddChild(node);
		//for( auto iter = parent->GetChildren().begin(); iter != parent->GetChildren().end(); ++iter )
		//{
		//	
		//}
		for( auto iter = parent->GetAnimators().begin(); iter != parent->GetAnimators().end(); ++iter )
		{
			node->AddAnimator( (*iter)->Clone() );		
		}
		return true;
	}
	//从UI树中删除节点,也会删除该节点的所有后代节点
	bool RemoveUINode( IUIObject* node );
	//获取被当前坐标命中的UI元件
	IUIObject* GetHitUIByPos(s32 x, s32 y);
	//运行UI树
	void RunTree();
	//消息处理
	void OnEvent( const SEvent& event );

private:
	IUIObject* Root;				//UI树根节点
	IUIObject* Focus;			//被激活的UI节点
	IUIObject* Over;				//当前鼠标滑过节点
	ITimer* Timer;				//Timer




};
#endif // UIManager_h__
