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
#include <list>
#include "IUIAnimator.h"
#include <irrlicht.h>
#include <functional>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace boost::numeric::ublas;
namespace ub = boost::numeric::ublas;

class IUIAnimator;


/*
** ���֣�IUIObject
** ˵����IUIObject�Ľӿ��࣬����������ֽڵ㣬��ɾ�������Լ�����
**
*/
class IUIObject : public Scar::IReferenceCounted
{
protected:
	std::list< IUIAnimator* >	Animators;		// �����б�
	std::list< IUIObject* >		Children;		// �ӽڵ��б�
	IUIObject*					Parent;			// ���ڵ�ָ��
	s32							Order;			// Ԫ��������ͬһ��ʱ�İڷ�˳��
	bool						IsVisible;		// Ԫ���Ƿ�ɼ�

	IVideoDriver*				Driver;			// Driverָ��
	ITexture*					Image;			// Ӧ����UI�ϵ�ͼƬ

	f32				RelativeAlpha;				// ���͸����
	vector2d<f32>	RelativeTranslation;		// ���ƽ����
	f32				RelativeRotation;			// �����ת
	vector2d<f32>	RelativeScale;				// �������
	matrix<f32>	AbsoluteTransformation;			// ��������ϵ�任����

	vector2d<f32>	DestinationQuadrangle[4];	// ��ʾ�������
									
public:

	IUIObject( IUIObject* parent, IVideoDriver * driver, s32 width, s32 height, s32 order = 0,
		const vector2d<f32>& position = vector2d<f32>( 0, 0 ),
		f32 rotdeg = 0,
		const vector2d<f32>& scale = vector2d<f32>( 1.f, 1.f ) ):
	  Parent(NULL), Driver(driver), Order(order), AbsoluteTransformation( 3, 3 )
	{
		
		if ( parent )
			parent->AddChild(this);

		//����ģ������ϵ����ԭ��Ϊ����
		DestinationQuadrangle[0].X = - width / 2.f;
		DestinationQuadrangle[0].Y = - height / 2.f;
		DestinationQuadrangle[1].X = DestinationQuadrangle[0].X + width;
		DestinationQuadrangle[1].Y = DestinationQuadrangle[0].Y;
		DestinationQuadrangle[2].X = DestinationQuadrangle[0].X + width;
		DestinationQuadrangle[2].Y = DestinationQuadrangle[0].Y + height;
		DestinationQuadrangle[3].X = DestinationQuadrangle[0].X;
		DestinationQuadrangle[3].Y = DestinationQuadrangle[0].Y + height;

		RelativeAlpha = 255;
		RelativeRotation = rotdeg;
		RelativeScale = scale;
		RelativeTranslation= position;
		IsVisible = true;

		UpdateAbsolutePosition();
	}

	// ����UIͼƬ
	void LoadImage( char * );

	// �����ĵ�Ϊ��׼����Ԫ��λ��
	//void SetCenter( const vector2d<f32>& pos );
	// �ı����ĵ�λ��
	//bool ModifyCenter( const vector2d<f32>& pos );
	// ��ȡԪ�����ĵ�λ��
	//const vector2d<f32>& GetCenter() const;

	// ���Alphaֵ
	//f32 GetAlpha();
	// ����Alphaֵ
	//void SetAlpha( f32 alpha );

	virtual ~IUIObject();


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
	virtual const std::list< IUIAnimator* >& GetAnimators() const;

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
	virtual const std::list< IUIObject* >& GetChildren() const;

	// ���Լ��Ӹ��ڵ���ɾ��
	// Ϊ�˺͸���irr::IReferenceCounted�е�drop��grab���һ��������������Сд��ͷ
	virtual void remove();

	// �жϵ�ǰ�����Ƿ���Ԫ����
	virtual IUIObject* HitTest( s32 x, s32 y )
	{
		return 0;
	}

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

	//virtual const vector2d<f32>* GetDestinationQuadrangle() const
	//{
	//	return DestinationQuadrangle;
	//}
	//virtual void SetDestinationQuadrangle( vector2d<f32> quadr[4] )
	//{
	//	for ( int i = 0; i < 4; i++ )
	//	{
	//		DestinationQuadrangle[i] = quadr[i];
	//	}
	//}

};

//#pragma warning( pop ) 

#endif // IUIObject_h__
