#ifndef IUIObject_h__
#define IUIObject_h__

#include "def.h"
#include <list>
#include "IUIAnimator.h"
#include <irrlicht.h>

using namespace irr;

class IUIAnimator;


class IUIObject : public irr::IReferenceCounted
{
	std::list< IUIAnimator* > Animators;
	std::list< IUIObject* > Children;
	IUIObject* Parent;

public:
	 //运行动画列表中的所有动画
	void OnAnimate( u32 time )
	{
		auto iter = Animators.begin();
		while ( iter != Animators.end() )
		{
			auto i = iter;
			iter++;
			(*i)->animateUIObject( this, time );
		}
		//通知子节点运行动画列表
		auto it = Children.begin();
		for (; it != Children.end(); ++it)
			(*it)->OnAnimate( time );
	}

	//将某个动画加入动画运行列表
	void AddAnimator( IUIAnimator* ani	)
	{
		Animators.push_back( ani );
		ani->grab();
	}

	//将某个动画从动画列表中删除
	void RemoveAnimator( IUIAnimator* ani )
	{
		Animators.remove( ani );
		ani->drop();
	}

	//清空动画列表
	void RemoveAnimators()
	{
		for ( auto iter = Animators.begin(); iter != Animators.end(); ++iter )
		{
			(*iter)->drop();
		}
		Animators.clear();
	}

	//设置父节点
	void SetParent( IUIObject* parent )
	{
		if ( Parent )
			Parent->RemoveChild( this );
		Parent = parent;
	}

	//删除子节点
	void RemoveChild( IUIObject* node )
	{
		Children.remove( node );
		node->drop();
	}

	//增加子节点
	void AddChild( IUIObject* node )
	{
		Children.push_back( node );
		node->grab();
	}

	//获取子节点列表
	const std::list< IUIObject* >& GetChildren() const
	{
		return Children;
	}

	//将自己从父节点中删除
	void RemoveSelf()
	{
		if ( Parent )
			Parent->RemoveChild( this );
	}

};
#endif // IUIObject_h__
