/********************************************************************
    创建时间: 2011-10-13   14:36
    文件名:   IUIObject.h
    作者:     华亮 屠文翔
    说明:     IUIObject接口，2D场景节点的接口。
			我们可以为实现IUIObject接口的类添加IUIAnimator动画以实现动画

*********************************************************************/

#ifndef IUIObject_h__
#define IUIObject_h__

//#pragma warning( push )


#define MAKE_INDENTITY3( m ) do { m.clear(); m(0, 0) = m( 1, 1 ) = m( 2, 2 ) = 1; } while ( 0 )

//#include "def.h"
#include <vector>
#include "IUIAnimator.h"
#include <irrlicht.h>
#include <functional>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <hash_map>


using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace boost::numeric::ublas;
namespace ub = boost::numeric::ublas;

class IUIAnimator;

enum SHAPE_FLAGS
{
	SQUARE = 0,
	CIRCLE,
	TRIANGLE
};

/*
** 名字：IUIObject
** 说明：IUIObject的接口类，负责管理父、字节点，增删动画，以及绘制
**
*/
class IUIObject : public Scar::IReferenceCounted
{
protected:
	struct EventHandler
	{
		std::string FuncName;
		std::string ModuleName;

		EventHandler() {}
		EventHandler( const std::string& func, const std::string& module )
			: FuncName( func ), ModuleName( module ) {}
	};

protected:
	std::vector< IUIAnimator* >	Animators;		// 动画列表
	std::vector< IUIObject* >	Children;		// 子节点列表
	IUIObject*					Parent;			// 父节点指针
	s32							Order;			// 元件在树的同一层时的摆放顺序
	bool						IsVisible;		// 元件是否可见

	IVideoDriver*				Driver;			// Driver指针
	ITexture*					Image;			// 应用于UI上的图片

	f32				RelativeAlpha;				// 相对透明度
	vector2d<f32>	RelativeTranslation;		// 相对平移量
	f32				RelativeRotation;			// 相对旋转
	vector2d<f32>	RelativeScale;				// 相对缩放
	matrix<f32>		AbsoluteTransformation;		// 绝对坐标系变换矩阵

	std::hash_map< std::string, EventHandler >	FuncMap;	// 注册处理函数信息


	vector2d<f32>	DestinationQuadrangle[4];	// 显示区域矩形
	int				Shape;						// 元件的判定区域形状

	bool IsPointInSquare( s32 x, s32 y );		// 判断点是否在矩形区域内
	bool IsPointInCircle( s32 x, s32 y );		// 判断点是否在圆形区域内

									
public:

	IUIObject( IUIObject* parent, s32 width, s32 height, s32 order = 0, int shape = SQUARE,
		const vector2d<f32>& position = vector2d<f32>( 0, 0 ),
		f32 rotdeg = 0,
		const vector2d<f32>& scale = vector2d<f32>( 1.f, 1.f ) );

	// 加载UI图片
	void LoadImage( char * );

	virtual ~IUIObject();

	// 注册Python的函数
	void AddFunc( const std::string& eventName, const std::string& funcName, const std::string& ModuleName );

	// 取消注册Python函数
	void RemoveFunc( const std::string& funcName );

	virtual matrix<f32> GetRelativeTransformation() const;

	// 获取当前节点的绝对变换矩阵
	virtual const matrix<f32>& GetAbsoluteTransformation() const
	{
		return AbsoluteTransformation;
	}

	// 获取当前节点的绝对位置
	virtual vector2d<f32> GetAbsolutePosition() const
	{
		matrix<f32> mat = GetAbsoluteTransformation();
		vector2d<f32> abspos;
		abspos.X = mat( 2, 0 );
		abspos.Y = mat( 2, 1 );
		return abspos;
	}

	// 更新当前节点基于相对变换矩阵的绝对变换矩阵
	virtual void UpdateAbsolutePosition()
	{
		if (Parent)
		{
			AbsoluteTransformation.assign( ub::prod( GetRelativeTransformation(), Parent->GetAbsoluteTransformation() ) );
		}
		else
		{
			AbsoluteTransformation.assign( GetRelativeTransformation() );
		}
	}

	// 获取当前节点绝对透明度
	 virtual f32 GetAbsoluteAlpha() const
	 {
		 f32 absalp = RelativeAlpha;
		 IUIObject* p = Parent;
		 while( p != NULL )
		 {
			 absalp *= p->RelativeAlpha / 255.f;
			 p = p->Parent;
		 }
		 return absalp;
	 }

	// 绘制当前节点
	virtual void Draw() = 0;

	// 绘制树 绘制当前节点以及当前节点的所有子节点
	virtual void DrawTree();

	// 运行动画列表中的所有动画
	virtual void OnAnimate( u32 time );

	// 将某个动画加入动画运行列表
	virtual void AddAnimator( IUIAnimator* ani	);

	// 获取动画列表
	virtual const std::vector< IUIAnimator* >& GetAnimators() const;

	// 将某个动画从动画列表中删除
	virtual void RemoveAnimator( IUIAnimator* ani );

	// 清空动画列表
	virtual void RemoveAnimators();

	// 设置父节点
	virtual void SetParent( IUIObject* parent );

	// 移除子节点
	virtual void RemoveChild( IUIObject* node );

	// 增加子节点
	virtual void AddChild( IUIObject* child );

	// 移除所有子节点
	virtual void RemoveAll();

	// 获取子节点列表
	virtual const std::vector< IUIObject* >& GetChildren() const;

	// 将自己从父节点中删除
	// 为了和父类irr::IReferenceCounted中的drop，grab风格一样，所以我们用小写开头
	virtual void remove();

	// 判断当前坐标是否在元件中
	virtual IUIObject* HitTest( s32 x, s32 y )
	{		
		return 0;
	}

	virtual bool IsPointIn( s32 x, s32 y );

	// 元件叠放顺序
	virtual void SetOrder( s32 order )
	{
		Order = order;
	}
	virtual s32 GetOrder() const
	{
		return Order;
	}

	// 相对Alpha值
	virtual	void SetAlpha( f32 alpha )
	{
		RelativeAlpha = alpha;
	}
	virtual f32 GetAlpha() const
	{
		return RelativeAlpha;
	}

	// 相对位置
	virtual void SetPosition( const vector2d<f32>& pos )
	{
		RelativeTranslation = pos;
	}
	virtual const vector2d<f32>& GetPosition() const
	{
		return RelativeTranslation;
	}

	// 相对旋转角度
	virtual void SetRotation( f32 rotdeg )
	{
		RelativeRotation = rotdeg;
	}
	virtual f32 GetRotation() const
	{
		return RelativeRotation;
	}

	// 相对缩放
	virtual void SetScale( const vector2d<f32>& scale )
	{
		RelativeScale = scale;
	}
	virtual const vector2d<f32>& GetScale() const
	{
		return RelativeScale;
	}

	// 可见性
	virtual void SetVisible( bool isvisible )
	{
		IsVisible = isvisible;
	}
	virtual bool GetVisible()
	{
		return IsVisible;
	}

	//virtual void OnEvent( const SEvent& event )
	//{
	//	for ( auto iter = Children.begin(); iter != Children.end(); ++iter )
	//	{
	//		(*iter)->OnEvent( event );
	//	}
	//}

/////////////////////////////////////////////////////////////////////////////////////
public:
	virtual void OnMouseMove( const irr::SEvent::SMouseInput& event ) {}

	virtual void OnMouseLeftButtonUp( const irr::SEvent::SMouseInput& event ) {}

	virtual void OnMouseLeftButtonDown( const irr::SEvent::SMouseInput& event ) {}

	virtual void OnMouseRightButtonUp( const irr::SEvent::SMouseInput& event ) {}

	virtual void OnMouseRightButtonDown( const irr::SEvent::SMouseInput& event ) {}

	virtual void OnWheel( const irr::SEvent::SMouseInput& event ) {}

	virtual void OnKeyDown( const irr::SEvent::SKeyInput& event ) {}

	virtual void OnKeyUp( const irr::SEvent::SKeyInput& event ) {}


	virtual void OnEvent( const SEvent& event );

};

//#pragma warning( pop ) 

#endif // IUIObject_h__
