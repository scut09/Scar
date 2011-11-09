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
		//root->grab();
		//if ( Root )
		//	Root->drop();
		Root = root;
		return true;
	}
	//获取UI树根节点
	IUIObject* GetRoot();
	//向UI树中插入节点
	bool AddUINode( IUIObject* node, IUIObject* parent );
	//从UI树中删除节点,也会删除该节点的所有后代节点
	bool RemoveUINode( IUIObject* node )
	{
		return NULL;
	}

	//获取被当前坐标命中的UI元件
	IUIObject* GetHitUIByPos(s32 x, s32 y)
	{
		return NULL;
	}

	//运行UI树
	void RunTree();
	//消息处理
	void OnEvent( const SEvent& event );
	//从树上获取特定名字的节点
	IUIObject* GetObjectByName( const std::string& name, IUIObject* node = 0 );

	// 命中检测
	IUIObject* HistTest( s32 x, s32 y )
	{
		return NULL;
	}

private:
	IUIObject*	Root;				//UI树根节点
	IUIObject*	Focus;				//被激活的UI节点
	IUIObject*	Over;				//当前鼠标滑过节点
	ITimer*		Timer;				//Timer




};
#endif // UIManager_h__
