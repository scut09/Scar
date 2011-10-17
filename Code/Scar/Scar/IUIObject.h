/********************************************************************
    ����ʱ��: 2011-10-13   14:36
    �ļ���:   IUIObject.h
    ����:     ���� ������
    ˵��:     IUIObject�ӿڣ�2D�����ڵ�Ľӿڡ�
			���ǿ���Ϊʵ��IUIObject�ӿڵ������IUIAnimator������ʵ�ֶ���

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
** ���֣�IUIObject
** ˵����IUIObject�Ľӿ��࣬����������ֽڵ㣬��ɾ�������Լ�����
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
	std::vector< IUIAnimator* >	Animators;		// �����б�
	std::vector< IUIObject* >	Children;		// �ӽڵ��б�
	IUIObject*					Parent;			// ���ڵ�ָ��
	s32							Order;			// Ԫ��������ͬһ��ʱ�İڷ�˳��
	bool						IsVisible;		// Ԫ���Ƿ�ɼ�

	IVideoDriver*				Driver;			// Driverָ��
	ITexture*					Image;			// Ӧ����UI�ϵ�ͼƬ

	f32				RelativeAlpha;				// ���͸����
	vector2d<f32>	RelativeTranslation;		// ���ƽ����
	f32				RelativeRotation;			// �����ת
	vector2d<f32>	RelativeScale;				// �������
	matrix<f32>		AbsoluteTransformation;		// ��������ϵ�任����

	std::hash_map< std::string, EventHandler >	FuncMap;	// ע�ᴦ������Ϣ


	vector2d<f32>	DestinationQuadrangle[4];	// ��ʾ�������
	int				Shape;						// Ԫ�����ж�������״

	bool IsPointInSquare( s32 x, s32 y );		// �жϵ��Ƿ��ھ���������
	bool IsPointInCircle( s32 x, s32 y );		// �жϵ��Ƿ���Բ��������

									
public:

	IUIObject( IUIObject* parent, s32 width, s32 height, s32 order = 0, int shape = SQUARE,
		const vector2d<f32>& position = vector2d<f32>( 0, 0 ),
		f32 rotdeg = 0,
		const vector2d<f32>& scale = vector2d<f32>( 1.f, 1.f ) );

	// ����UIͼƬ
	void LoadImage( char * );

	virtual ~IUIObject();

	// ע��Python�ĺ���
	void AddFunc( const std::string& eventName, const std::string& funcName, const std::string& ModuleName );

	// ȡ��ע��Python����
	void RemoveFunc( const std::string& funcName );

	virtual matrix<f32> GetRelativeTransformation() const;

	// ��ȡ��ǰ�ڵ�ľ��Ա任����
	virtual const matrix<f32>& GetAbsoluteTransformation() const
	{
		return AbsoluteTransformation;
	}

	// ��ȡ��ǰ�ڵ�ľ���λ��
	virtual vector2d<f32> GetAbsolutePosition() const
	{
		matrix<f32> mat = GetAbsoluteTransformation();
		vector2d<f32> abspos;
		abspos.X = mat( 2, 0 );
		abspos.Y = mat( 2, 1 );
		return abspos;
	}

	// ���µ�ǰ�ڵ������Ա任����ľ��Ա任����
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

	// ��ȡ��ǰ�ڵ����͸����
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

	// ���Ƶ�ǰ�ڵ�
	virtual void Draw() = 0;

	// ������ ���Ƶ�ǰ�ڵ��Լ���ǰ�ڵ�������ӽڵ�
	virtual void DrawTree();

	// ���ж����б��е����ж���
	virtual void OnAnimate( u32 time );

	// ��ĳ���������붯�������б�
	virtual void AddAnimator( IUIAnimator* ani	);

	// ��ȡ�����б�
	virtual const std::vector< IUIAnimator* >& GetAnimators() const;

	// ��ĳ�������Ӷ����б���ɾ��
	virtual void RemoveAnimator( IUIAnimator* ani );

	// ��ն����б�
	virtual void RemoveAnimators();

	// ���ø��ڵ�
	virtual void SetParent( IUIObject* parent );

	// �Ƴ��ӽڵ�
	virtual void RemoveChild( IUIObject* node );

	// �����ӽڵ�
	virtual void AddChild( IUIObject* child );

	// �Ƴ������ӽڵ�
	virtual void RemoveAll();

	// ��ȡ�ӽڵ��б�
	virtual const std::vector< IUIObject* >& GetChildren() const;

	// ���Լ��Ӹ��ڵ���ɾ��
	// Ϊ�˺͸���irr::IReferenceCounted�е�drop��grab���һ��������������Сд��ͷ
	virtual void remove();

	// �жϵ�ǰ�����Ƿ���Ԫ����
	virtual IUIObject* HitTest( s32 x, s32 y )
	{		
		return 0;
	}

	virtual bool IsPointIn( s32 x, s32 y );

	// Ԫ������˳��
	virtual void SetOrder( s32 order )
	{
		Order = order;
	}
	virtual s32 GetOrder() const
	{
		return Order;
	}

	// ���Alphaֵ
	virtual	void SetAlpha( f32 alpha )
	{
		RelativeAlpha = alpha;
	}
	virtual f32 GetAlpha() const
	{
		return RelativeAlpha;
	}

	// ���λ��
	virtual void SetPosition( const vector2d<f32>& pos )
	{
		RelativeTranslation = pos;
	}
	virtual const vector2d<f32>& GetPosition() const
	{
		return RelativeTranslation;
	}

	// �����ת�Ƕ�
	virtual void SetRotation( f32 rotdeg )
	{
		RelativeRotation = rotdeg;
	}
	virtual f32 GetRotation() const
	{
		return RelativeRotation;
	}

	// �������
	virtual void SetScale( const vector2d<f32>& scale )
	{
		RelativeScale = scale;
	}
	virtual const vector2d<f32>& GetScale() const
	{
		return RelativeScale;
	}

	// �ɼ���
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
