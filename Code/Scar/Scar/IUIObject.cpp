/********************************************************************
    ����ʱ��: 2011-10-13   14:36
    �ļ���:   IUIObject.h
    ����:     ���� ������
    ˵��:     IUIObject�ӿڣ�2D�����ڵ�Ľӿڡ�
			���ǿ���Ϊʵ��IUIObject�ӿڵ������IUIAnimator������ʵ�ֶ���

*********************************************************************/



#include "IUIObject.h"
#include <algorithm>
#include "MyIrrlichtEngine.h"

//#pragma warning( push )y


IUIObject::~IUIObject()
{
	RemoveAll();			// ɾ�����к���,�����ӵ����ü�������һ����������ParentΪ0
	//RemoveAnimators();		// ɾ�����еĶ�����
	// ������Ҫ�����ˣ�Ϊ�����ܣ����Բ���Ҫʹ��RemoveAnimators�����Animators.clear()
	for ( auto iter = Animators.begin(); iter != Animators.end(); ++iter )
	{
		(*iter)->drop();
	}
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
		//��Ӧ�����Ľӿ�
		(*i)->animateUIObject( this, time );
	}
	//֪ͨ�ӽڵ����ж����б�
	auto it = Children.begin();
	for (; it != Children.end(); ++it)
		(*it)->OnAnimate( time );
}

void IUIObject::AddAnimator( IUIAnimator* ani )
{
	Animators.push_back( ani );
	ani->grab();
	//Ϊ�����ӽڵ�������Ӧ�Ķ���
	//�������ʷ�������⣬����ɾ�������
	/*for( auto iter = Children.begin(); iter != Children.end(); ++iter )
	{
		IUIAnimator* aniCopy = ani->Clone(); 
		(*iter)->AddAnimator(aniCopy);
		aniCopy->drop();
	}*/
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
	grab();		// �����Լ������ü����������ڽ��Լ��Ӹ��ڵ����Ƴ�ʱ������
	remove();	// ���Լ��Ӹ��ڵ����Ƴ�

	// �û���������Ϊ��
	Parent = parent;
	if ( parent )
		parent->AddChild( this );	//������������AddChild�ڲ�+1

	drop();		// ���Լ������ü���-1�������ǽ�����Ȩ�ƽ������ڵ㡣�����ü�����Ϊ0�ǣ��Լ��ᱻdelelte
}

void IUIObject::RemoveChild( IUIObject* node )
{
	node->Parent = 0;			// ���ﲻ��ʹ��SetParent()��
	Children.remove( node );	// �����Ӵ��Լ����ӽڵ��б����Ƴ�
	node->drop();				// ���Ӽ�����-1
}

void IUIObject::AddChild( IUIObject* child )
{
	if ( ! child )	return;

	child->grab();				// �Լ���child�ڵ����ã����Զ����ü���+1
	child->remove();			// ��ԭ���ڵ����Ƴ��Լ�
	Children.push_back(child);
	child->Parent = this;		// ���ﲻ����SetParent����������޵ݹ鵽ջ���
	
	// ���ݺ��ӵ�Order����
	Children.sort( []( IUIObject* lhs, IUIObject* rhs )->bool
	{
		return lhs->GetOrder() < rhs->GetOrder();
	});




}

void IUIObject::RemoveAll()
{
	for ( auto iter = Children.begin(); iter != Children.end(); ++iter )
	{
		(*iter)->Parent = 0;	// ���ﲻ��ʹ��SetParent()��������������ʱ����;����Լ���Children�����Ƴ������µ�����ʧЧ������
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


//װ��ͼƬ
void IUIObject::LoadImage( char * filename )
{
	Image = Driver->getTexture( filename );
}

//��ȡ��Ա任����
matrix<f32> IUIObject::GetRelativeTransformation() const
{
	matrix<f32> mat( 3, 3 );
	MAKE_INDENTITY3(mat);
	// ��ת
	f32 rad = RelativeRotation * core::DEGTORAD;
	mat(0,0) = cos(rad);	mat(0,1) = sin(rad);
	mat(1,0) = -sin(rad);	mat(1,1) = cos(rad);
	// ƽ��
	mat(2,0) = RelativeTranslation.X;
	mat(2,1) = RelativeTranslation.Y;
	// ����
	if( RelativeScale != vector2d<f32>(1.0f, 1.0f) )
	{
		matrix<f32> smat( 3, 3 );
		MAKE_INDENTITY3(smat);
		smat(0,0) = RelativeScale.X;
		smat(1,1) = RelativeScale.Y;
		mat = prod(smat, mat);
	}
	return mat;
}

IUIObject::IUIObject( IUIObject* parent, s32 width, s32 height, s32 order /*= 0*/, const vector2d<f32>& position /*= vector2d<f32>( 0, 0 )*/, f32 rotdeg /*= 0*/, const vector2d<f32>& scale /*= vector2d<f32>( 1.f, 1.f ) */ ) :
Parent(NULL), Order(order), AbsoluteTransformation( 3, 3 ), Image( 0 )
{
	if ( parent )
		parent->AddChild(this);

	Driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();

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
