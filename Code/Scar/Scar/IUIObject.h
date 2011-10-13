/********************************************************************
    创建时间: 2011-10-13   14:36
    文件名:   IUIObject.h
    作者:     华亮 屠文翔
    说明:     IUIObject接口，2D场景节点的接口。
			我们可以为实现IUIObject接口的类添加IUIAnimator动画以实现动画

*********************************************************************/

#ifndef IUIObject_h__
#define IUIObject_h__

#include "def.h"
#include <list>
#include "IUIAnimator.h"
#include <irrlicht.h>

using namespace irr;

class IUIAnimator;


/*
** 名字：IUIObject
** 说明：UIObject的接口类，负责管理父、字节点，增删动画，以及绘制
**
*/
class IUIObject : public irr::IReferenceCounted
{
//public:
	std::list< IUIAnimator* > Animators;
	std::list< IUIObject* > Children;
	IUIObject* Parent;

public:
	IUIObject();

	virtual ~IUIObject();

	//绘制当前节点
	virtual void Draw() = 0;

	//绘制树 绘制当前节点以及当前节点的所有子节点
	virtual void DrawTree();

	 //运行动画列表中的所有动画
	virtual void OnAnimate( u32 time );

	//将某个动画加入动画运行列表
	virtual void AddAnimator( IUIAnimator* ani	);

	//获取动画列表
	virtual const std::list< IUIAnimator* >& GetAnimators() const;

	//将某个动画从动画列表中删除
	virtual void RemoveAnimator( IUIAnimator* ani );

	//清空动画列表
	virtual void RemoveAnimators();

	//设置父节点
	virtual void SetParent( IUIObject* parent );

	//删除子节点
	virtual void RemoveChild( IUIObject* node );

	//增加子节点
	virtual void AddChild( IUIObject* child );

	virtual void RemoveAll();

	//获取子节点列表
	virtual const std::list< IUIObject* >& GetChildren() const;

	// 将自己从父节点中删除
	// 为了和父类irr::IReferenceCounted中的drop，grab风格一样，所以我们用小写开头
	virtual void remove();

};
#endif // IUIObject_h__
