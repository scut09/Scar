#ifndef UIManager_h__
#define UIManager_h__

#include <irrlicht.h>
#include "IUIObject.h"
#include "UIAnimators.h"
#include "AllUIObjects.h"

using namespace irr;

class UIManager
{
private:
	IUIObject*		RootUIObject;	// 所有UIObject的根节点，不会显示出来，只是占位
	ITimer*			Timer;			//Timer


public:
	UIManager( ITimer* timer ) : Timer(timer), Root(NULL)
	{
		RootUIObject = new UIImage( 0, 0, 0 );
	}

	~UIManager()
	{
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

		return new UIImage( parent, width, height, order, shape, position, rotdeg, scale );
	}

	IUIObject* AddUIButton( IUIObject* parent, s32 width, s32 height, s32 order = 0, int shape = SQUARE,
		const vector2d<f32>& position = vector2d<f32>(0,0),
		f32 rotdeg = 0,
		const vector2d<f32>& scale = vector2d<f32>(1,1) )
	{
		if ( ! parent )
			parent = RootUIObject;

		return new UIButton( parent, width, height, order, shape, position, rotdeg, scale );
	}

	IUIObject* AddUIStaticText( IUIObject* parent, s32 width, s32 hegit,
		stringw text,
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

		return new UIStaticText( parent, width, hegit, text, color, fontsize,
			hcenter, vcenter, order, shape, position, rotdeg, scale, Isvisible );
	}




	/************************************************************************/
	/* 创建Animtor                                                          */
	/************************************************************************/

	// 创建平移动画
	IUIAnimator* CreateAnimatorTranslation( u32 begin, u32 duration, const vector2d<s32>& offset, bool loop = false )
	{
		return new TranslateUIAnimator( begin, duration, offset, loop );
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
		if ( RootUIObject )
		{
			RootUIObject->OnAnimate( Timer->getRealTime() );
			RootUIObject->DrawTree();
		}
	}




//protected:
	//从树上获取特定名字的节点
	IUIObject* GetObjectByName( const std::string& name, IUIObject* node = 0 );


public:

	/************************************************************************/
	/* 历史遗留，即将被删除                                                  */
	/************************************************************************/
	bool SetRoot( IUIObject* root )
	{
		//root->grab();
		//if ( Root )
		//	Root->drop();
		Root = root;
		return true;
	}

	IUIObject* GetRoot()
	{
		return Root;
	}

	//运行UI树
	void RunTree();


private:
	IUIObject*	Root;				//UI树根节点





};
#endif // UIManager_h__
