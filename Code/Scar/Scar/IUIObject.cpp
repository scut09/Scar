/********************************************************************
    创建时间: 2011-10-13   14:36
    文件名:   IUIObject.h
    作者:     华亮 屠文翔
    说明:     IUIObject接口，2D场景节点的接口。
			我们可以为实现IUIObject接口的类添加IUIAnimator动画以实现动画

*********************************************************************/

#include "IUIObject.h"

IUIObject::IUIObject()
	: Parent( 0 )
{
}

IUIObject::~IUIObject()
{
	RemoveAll();			// 删除所有孩子,将孩子的引用计数器减一，设置它的Parent为0
	RemoveAnimators();		// 删除所有的动画
}

void IUIObject::DrawTree()
{
	Draw();
	for(auto iter = Children.begin(); iter != Children.end(); ++iter)
	{
		(*iter)->DrawTree();
	}
}

void IUIObject::OnAnimate( u32 time )
{
	auto iter = Animators.begin();
	while ( iter != Animators.end() )
	{
		auto i = iter;
		iter++;
		//相应动画的接口
		(*i)->animateUIObject( this, time );
	}
	//通知子节点运行动画列表
	auto it = Children.begin();
	for (; it != Children.end(); ++it)
		(*it)->OnAnimate( time );
}

void IUIObject::AddAnimator( IUIAnimator* ani )
{
	Animators.push_back( ani );
	ani->grab();
	//为所有子节点增加相应的动画
	for( auto iter = Children.begin(); iter != Children.end(); ++iter )
	{
		IUIAnimator* aniCopy = ani->Clone(); 
		(*iter)->AddAnimator(aniCopy);
		aniCopy->drop();
	}
}

const std::list< IUIAnimator* >& IUIObject::GetAnimators() const
{
	return Animators;
}

void IUIObject::RemoveAnimator( IUIAnimator* ani )
{
	Animators.remove( ani );
	ani->drop();
}

void IUIObject::RemoveAnimators()
{
	for ( auto iter = Animators.begin(); iter != Animators.end(); ++iter )
	{
		(*iter)->drop();
	}
	Animators.clear();
}

void IUIObject::SetParent( IUIObject* parent )
{
	grab();		// 增加自己的引用计数，放在在将自己从父节点中移除时被销毁
	remove();	// 将自己从父节点中移除

	// 用户可能输入为空
	Parent = parent;
	if ( parent )
		parent->AddChild( this );

	drop();		// 将自己的引用计数建1，当引用计数减为0是，自己会被delelte
}

void IUIObject::RemoveChild( IUIObject* node )
{
	Children.remove( node );
	node->drop();
}

void IUIObject::AddChild( IUIObject* child )
{
	if ( ! child )	return;

	child->grab();
	child->remove();			// 从原父节点中移除自己
	Children.push_back(child);
	child->Parent = this;		// 这里不能用SetParent，否则会无限递归到栈溢出
}

void IUIObject::RemoveAll()
{
	for ( auto iter = Children.begin(); iter != Children.end(); ++iter )
	{
		(*iter)->SetParent( 0 );
		(*iter)->drop();
	}

	Children.clear();
}

const std::list< IUIObject* >& IUIObject::GetChildren() const
{
	return Children;
}

void IUIObject::remove()
{
	if ( Parent )
		Parent->RemoveChild( this );
}
