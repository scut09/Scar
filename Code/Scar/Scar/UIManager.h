#ifndef UIManager_h__
#define UIManager_h__

#include <irrlicht.h>
#include "IUIObject.h"
#include "UIAnimators.h"
#include "AllUIObjects.h"
#include <string>

using namespace irr;

class UIManager
{
private:
	IUIObject*		RootUIObject;	// 所有UIObject的根节点，不会显示出来，只是占位
	ITimer*			Timer;			//Timer


public:
	UIManager( ITimer* timer ) : Timer(timer)
	{
		if ( Timer )
			Timer->grab();

		RootUIObject = new UIImage( 0, 0, 0 );
	}

	~UIManager()
	{
		if ( Timer )
			Timer->drop();

		RootUIObject->drop();
	}

	// 获取根节点
	IUIObject* GetRootUIObject()
	{
		return RootUIObject;
	}

	// 移除所有节点
	void Clear()
	{
		RootUIObject->RemoveAll();
	}

	// 根据名字获取UIObject
	IUIObject* GetUIObjectByName( const std::string& name )
	{
		return GetObjectByName( name, RootUIObject );
	}

	void OnEvent( const SEvent& event );


	/************************************************************************/
	/* 往UIManager中添加UIObject                                             */
	/************************************************************************/

	IUIObject* AddUIImage( IUIObject* parent, s32 width, s32 height, s32 order = 0, int shape = SQUARE,
		const vector2d<f32>& position = vector2d<f32>( 0, 0 ),
		f32 rotdeg = 0,
		const vector2d<f32>& scale = vector2d<f32>( 1.f, 1.f ) )
	{
		if ( ! parent )
			parent = RootUIObject;

		IUIObject* obj = new UIImage( parent, width, height, order, shape, position, rotdeg, scale );
		obj->drop();

		return obj;
	}

	IUIObject* AddUIButton( IUIObject* parent, s32 width, s32 height, s32 order = 0, int shape = SQUARE,
		const vector2d<f32>& position = vector2d<f32>(0,0),
		f32 rotdeg = 0,
		const vector2d<f32>& scale = vector2d<f32>(1,1) )
	{
		if ( ! parent )
			parent = RootUIObject;

		IUIObject* obj = new UIButton( parent, width, height, order, shape, position, rotdeg, scale );
		obj->drop();

		return obj;
	}

	IUIObject* AddUIStaticText( IUIObject* parent, s32 width, s32 hegit,
		std::wstring text,
		SColor color,
		u32 fontsize = 14,
		bool hcenter = false,
		bool vcenter = false,
		s32 order = 0, int shape = SQUARE,
		const vector2d<f32>& position = vector2d<f32>(0,0),
		f32 rotdeg = 0,
		const vector2d<f32>& scale = vector2d<f32>(1,1),
		bool Isvisible = true)
	{
		if ( ! parent )
			parent = RootUIObject;

		IUIObject* obj = new UIStaticText( parent, width, hegit, text.c_str(), color, fontsize,
			hcenter, vcenter, order, shape, position, rotdeg, scale, Isvisible );
		obj->drop();

		return obj;
	}

	IUIObject* AddUIBox( IUIObject* parent, s32 width, s32 height, s32 order = 0, int shape = SQUARE,
		const vector2d<f32>& position = vector2d<f32>( 0, 0 ),
		f32 rotdeg = 0,
		const vector2d<f32>& scale = vector2d<f32>( 1.f, 1.f ) ) 
	{
		if ( ! parent )
			parent = RootUIObject;

		IUIObject* obj = new CUIBox(  parent, width, height, order,shape, position, rotdeg, scale );
		obj->drop();

		return obj;
	}


	/************************************************************************/
	/* 创建Animtor                                                          */
	/************************************************************************/

	// 创建平移动画
	IUIAnimator* CreateAnimatorTranslation( u32 begin, u32 duration, const vector2df& offset, bool loop = false )
	{
		return new TranslateUIAnimator( begin, duration, offset, loop );
	}
	IUIAnimator* CreateAnimatorTranslation( u32 delay, u32 duration, const vector2df& from, const vector2df& to, bool loop = false )
	{
		return new TranslateUIAnimator( delay, duration, from, to, loop );
	}

	// 创建旋转动画
	IUIAnimator* CreateAnimatorRotation( u32 begin, u32 duration, f32 angle, bool loop = false )
	{
		return new RotateUIAnimator( begin, duration, angle, loop );
	}

	// 创建缩放动画
	IUIAnimator* CreateAnimatorScale( u32 begin, u32 duration, vector2d<f32> scale, bool loop = false )
	{
		return new ScaleUIAnimator( begin, duration, scale, loop );
	}	

	// 创建Alpha改变动画	
	IUIAnimator* CreateAnimatorAlphaChange( u32 begin, u32 duration, f32 srcalpha,
		f32 taralpha, bool loop = false )
	{
		return new AlphaChangeUIAnimator( begin, duration, srcalpha, taralpha, loop );
	}

	// 创建自我删除动画
	IUIAnimator* CreateAnimatorDeletion( u32 now, u32 time )
	{
		return new DeletionAnimator( now, time );
	}

	// 创建延迟调用动画
	IUIAnimator* CreateAnimatorTimelag( u32 begin, u32 duration, std::string moduleName, std::string funName, bool loop = false )
	{
		return new TimelagUIAnimator( begin, duration, moduleName, funName, loop );
	}

	// 绘制所有的UI树上的节点
	void DrawAll()
	{
		RootUIObject->OnAnimate( Timer->getRealTime() );
		RootUIObject->DrawTree();		
	}




protected:
	//从树上获取特定名字的节点
	IUIObject* GetObjectByName( const std::string& name, IUIObject* node = 0 );


public:

	/************************************************************************/
	/* 历史遗留，即将被删除                                                  */
	/************************************************************************/
	//bool SetRoot( IUIObject* root )
	//{
	//	//root->grab();
	//	//if ( Root )
	//	//	Root->drop();
	//	Root = root;
	//	return true;
	//}

	//IUIObject* GetRoot()
	//{
	//	return Root;
	//}

	////运行UI树
	//void RunTree();


//private:
//	IUIObject*	Root;				//UI树根节点





};
#endif // UIManager_h__
