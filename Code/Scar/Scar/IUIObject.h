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
#include <functional>

using namespace irr;
using namespace irr::core;
using namespace irr::video;

class IUIAnimator;


/*
** 名字：IUIObject
** 说明：IUIObject的接口类，负责管理父、字节点，增删动画，以及绘制
**
*/
class IUIObject : public irr::IReferenceCounted
{
protected:
	std::list< IUIAnimator* > Animators;
	std::list< IUIObject* > Children;
	IUIObject* Parent;
	s32 Order;									//元件在树的同一层时的摆放顺序
	vector2d<f32> Center;						//矩形的中心点
	IVideoDriver * Driver;						//Driver指针
	f32 Alpha;									//元件透明度
	ITexture * Image;							//应用于UI上的图片

public:
	vector2d<f32> DstQuar[4];					//显示区域矩形
	
									
public:
	//IUIObject( s32 order = 0 );

	IUIObject( IVideoDriver * driver, const vector2d<f32>& pos, s32 width, s32 height, s32 order = 0 );

	//加载UI图片
	void SetImage( char * );

	//以中心点为基准设置元件位置
	void SetCenter( const vector2d<f32>& pos );
	//改变中心点位置
	bool ModifyCenter( const vector2d<f32>& pos );
	//获取元件中心点位置
	const vector2d<f32>& GetCenter() const;

	//获得Alpha值
	f32 GetAlpha();
	//设置Alpha值
	void SetAlpha( f32 alpha );

	virtual ~IUIObject();

	//设置元件顺序
	virtual s32 GetOrder() const;
	//获取元件顺序
	virtual void SetOrder( s32 order );

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
