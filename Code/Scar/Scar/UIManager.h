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
	IUIObject*		RootUIObject;	// ����UIObject�ĸ��ڵ㣬������ʾ������ֻ��ռλ
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

	// ��ȡ���ڵ�
	IUIObject* GetRootUIObject()
	{
		return RootUIObject;
	}

	// �Ƴ����нڵ�
	void Clear()
	{
		RootUIObject->RemoveAll();
	}

	// �������ֻ�ȡUIObject
	IUIObject* GetUIObjectByName( const std::string& name )
	{
		return GetObjectByName( name, RootUIObject );
	}

	void OnEvent( const SEvent& event );


	/************************************************************************/
	/* ��UIManager�����UIObject                                             */
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
	/* ����Animtor                                                          */
	/************************************************************************/

	// ����ƽ�ƶ���
	IUIAnimator* CreateAnimatorTranslation( u32 begin, u32 duration, const vector2d<s32>& offset, bool loop = false )
	{
		return new TranslateUIAnimator( begin, duration, offset, loop );
	}

	// ������ת����
	IUIAnimator* CreateAnimatorRotation( u32 begin, u32 duration, f32 angle, bool loop = false )
	{
		return new RotateUIAnimator( begin, duration, angle, loop );
	}

	// �������Ŷ���
	IUIAnimator* CreateAnimatorScale( u32 begin, u32 duration, vector2d<f32> scale, bool loop = false )
	{
		return new ScaleUIAnimator( begin, duration, scale, loop );
	}	

	// ����Alpha�ı䶯��	
	IUIAnimator* CreateAnimatorAlphaChange( u32 begin, u32 duration, f32 srcalpha,
		f32 taralpha, bool loop = false )
	{
		return new AlphaChangeUIAnimator( begin, duration, srcalpha, taralpha, loop );
	}

	// ��������ɾ������
	IUIAnimator* CreateAnimatorDeletion( u32 now, u32 time )
	{
		return new DeletionAnimator( now, time );
	}

	// �����ӳٵ��ö���
	IUIAnimator* CreateAnimatorTimelag( u32 begin, u32 duration, std::string moduleName, std::string funName, bool loop = false )
	{
		return new TimelagUIAnimator( begin, duration, moduleName, funName, loop );
	}

	// �������е�UI���ϵĽڵ�
	void DrawAll()
	{
		if ( RootUIObject )
		{
			RootUIObject->OnAnimate( Timer->getRealTime() );
			RootUIObject->DrawTree();
		}
	}




//protected:
	//�����ϻ�ȡ�ض����ֵĽڵ�
	IUIObject* GetObjectByName( const std::string& name, IUIObject* node = 0 );


public:

	/************************************************************************/
	/* ��ʷ������������ɾ��                                                  */
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

	//����UI��
	void RunTree();


private:
	IUIObject*	Root;				//UI�����ڵ�





};
#endif // UIManager_h__
