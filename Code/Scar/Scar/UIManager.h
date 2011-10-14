#ifndef UIManager_h__
#define UIManager_h__

#include <irrlicht.h>
#include "UIObject.h"

using namespace irr;

class UIManager
{
public:
	UIManager( ITimer* timer ) : Timer(timer), Root(NULL), Focus(NULL), Over(NULL)
	{
		
	}
	bool SetRoot( UIObject* root )
	{
		Root = root;
		return true;
	}
	//获取UI树根节点
	UIObject* GetRoot();
	//向UI树中插入节点
	bool AddUINode( UIObject* node, UIObject* parent, s32 order = 0 )
	{
		parent->AddChild(node);
		//for( auto iter = parent->GetChildren())
		for( auto iter = parent->GetAnimators().begin(); iter != parent->GetAnimators().end(); ++iter )
		{
			node->AddAnimator( (*iter)->Clone() );		
		}
		/*vector2d<f32> offset = pos - node->Center;
		for(int i=0; i<4; i++)
		node->DstQuar[i] += offset;*/
		return true;
	}
	//从UI树中删除节点,也会删除该节点的所有后代节点
	bool RemoveUINode( UIObject* node );
	//获取被当前坐标命中的UI元件
	UIObject* GetHitUIByPos(s32 x, s32 y);
	//运行UI树
	void RunTree();
	//消息处理
	void OnEvent( const SEvent& event );

private:
	UIObject* Root;				//UI树根节点
	UIObject* Focus;			//被激活的UI节点
	UIObject* Over;				//当前鼠标滑过节点
	ITimer* Timer;				//Timer




};
#endif // UIManager_h__
