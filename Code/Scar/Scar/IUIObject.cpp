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

	Image->drop();
}

void IUIObject::DrawTree()
{
	if( IsVisible )
	{
		Draw();
		for(auto iter = Children.begin(); iter != Children.end(); ++iter)
		{
			(*iter)->DrawTree();
		}
	}
}

void IUIObject::OnAnimate( u32 time )
{
	auto iter = Animators.begin();
	//while ( iter != Animators.end() )
	//{
	//	auto i = iter;
	//	iter++;
	//	//��Ӧ�����Ľӿ�
	//	(*i)->animateUIObject( this, time );
	//}
	for ( u32 i = 0; i < Animators.size(); i++ )
	{
		Animators[ i ]->animateUIObject( this, time );
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

const std::vector< IUIAnimator* >& IUIObject::GetAnimators() const
{
	return Animators;
}

void IUIObject::RemoveAnimator( IUIAnimator* ani )
{
	//ɾ��Ԫ��
	auto itr = std::find( Animators.begin(), Animators.end(), ani );
	int diff = itr - Animators.begin();
	Animators.erase( Animators.begin() + diff );

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
	//Children.remove( node );	// �����Ӵ��Լ����ӽڵ��б����Ƴ�
	//ɾ��Ԫ��
	auto itr = std::find( Children.begin(), Children.end(), node );
	int diff = itr - Children.begin();
	Children.erase( Children.begin() + diff );

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
	//Children.sort( []( IUIObject* lhs, IUIObject* rhs )->bool
	//{
	//	return lhs->GetOrder() < rhs->GetOrder();
	//});
	std::sort( Children.begin(), Children.end(), []( IUIObject* lhs, IUIObject* rhs )->bool
		{
			return lhs->GetOrder() < rhs->GetOrder();
		} );

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

const std::vector< IUIObject* >& IUIObject::GetChildren() const
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
	if ( Image )
	{
		Image->drop();
	}

	Image = Driver->getTexture( filename );
	if ( Image )
	{
		Image->grab();
		LeftTop = vector2df( 0, 0 );
		RightBottom = vector2df( (f32)Image->getSize().Width, (f32)Image->getSize().Height );
	}
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

IUIObject::IUIObject( IUIObject* parent, s32 width, s32 height, s32 order /*= 0*/, int shape,
	const vector2d<f32>& position /*= vector2d<f32>( 0, 0 )*/,
	f32 rotdeg /*= 0*/, const vector2d<f32>& scale /*= vector2d<f32>( 1.f, 1.f ) */ ) :
Parent(NULL), Order(order), AbsoluteTransformation( 3, 3 ), Image( 0 ), Shape( shape )
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

	// Ĭ�ϲ����÷����
	bAntiAliasing = false;

	UpdateAbsolutePosition();
}

//��Ϣ����
void IUIObject::OnEvent( const SEvent& event )
{
	//using namespace irr;
	if ( IsVisible )
	{
		if ( event.EventType == EET_MOUSE_INPUT_EVENT )
		{
			SEvent::SMouseInput mouseEvent = event.MouseInput;

			if ( mouseEvent.Event == EMIE_MOUSE_MOVED )
				OnMouseMove( mouseEvent );
			if ( mouseEvent.Event == EMIE_LMOUSE_PRESSED_DOWN )
				OnMouseLeftButtonDown( mouseEvent );
			if ( mouseEvent.Event == EMIE_LMOUSE_LEFT_UP )
				OnMouseLeftButtonUp( mouseEvent );
			if ( mouseEvent.Event == EMIE_RMOUSE_PRESSED_DOWN )
				OnMouseRightButtonDown( mouseEvent );
			if ( mouseEvent.Event == EMIE_RMOUSE_LEFT_UP )
				OnMouseRightButtonUp( mouseEvent );
			if ( mouseEvent.Event == EMIE_MOUSE_WHEEL )
				OnWheel( mouseEvent );
		}
		else if ( event.EventType == EET_KEY_INPUT_EVENT )
		{
			SEvent::SKeyInput keyEvent = event.KeyInput;
			if ( keyEvent.PressedDown )
				OnKeyDown( keyEvent );
			if ( !keyEvent.PressedDown )
				OnKeyUp( keyEvent );
		}
		else
			return;

		for( auto iter = Children.begin(); iter != Children.end(); ++iter )
			(*iter)->OnEvent( event );
	}

	//IUIObject::OnEvent( event );
}

//�жϵ��Ƿ��ڵ�ǰԪ���ڲ�
bool IUIObject::IsPointIn( s32 x, s32 y )
{
	if ( IsVisible )
	{
		if ( DestinationQuadrangle[0] != DestinationQuadrangle[2] ) 
		{
			bool tem;
			if( Shape == SQUARE )
				tem = IsPointInSquare( x, y );
			else if( Shape == CIRCLE )
				tem = IsPointInCircle( x, y );
			if ( tem )
				return tem;
		}

		for ( auto iter = Children.begin(); iter != Children.end(); ++iter )
		{
			if ( (*iter)->IsPointIn( x, y ) )
				return true;
		}
	}

	return false;	
}

// �жϵ��Ƿ��ھ���������
bool IUIObject::IsPointInSquare( s32 x, s32 y )
{
	//���Ȼ�ȡԪ���ĸ����㵱ǰ����Ļ�ϵľ�������
	matrix<f32> TransMat = AbsoluteTransformation;
	vector2d<f32> AbsPoints[4];
	ub::vector<f32> temPoint(3);
	temPoint(2) = 1;
	for( int i=0; i<4; i++ )
	{
		temPoint(0) = DestinationQuadrangle[i].X;
		temPoint(1) = DestinationQuadrangle[i].Y;
		temPoint = prod( temPoint, TransMat );
		AbsPoints[i].X = temPoint(0);
		AbsPoints[i].Y = temPoint(1);
	}
	//��Ԫ����Χ�п��
	vector2d<f32> v1 = AbsPoints[0] - AbsPoints[2];
	vector2d<f32> v2 = AbsPoints[1] - AbsPoints[3];
	f32 boxWidth = std::max( abs(v1.X), abs(v2.X) );
	f32 boxHeight = std::max( abs(v1.Y), abs(v2.Y) );
	
	/*std::cout<< "width: " << boxWidth << "  height: " << boxHeight << std::endl;
	std::cout<< AbsPoints[0].X << "," << AbsPoints[0].Y << "\t";
	std::cout<< AbsPoints[1].X << "," << AbsPoints[1].Y << std::endl;
	std::cout<< AbsPoints[3].X << "," << AbsPoints[3].Y << "\t"; 
	std::cout<< AbsPoints[2].X << "," << AbsPoints[2].Y << std::endl;*/
	
	//���ĸ�����ָ��Ŀ��������
	//�������ĸ���������һ��
	vector2d<f32> v[4];
	vector2d<f32> vd = vector2d<f32>(0, 0);
	for ( int i=0; i<4; i++ )
	{
		v[i] = vector2d<f32>( (f32)x, (f32)y ) - AbsPoints[i];
		vd += v[i];
	}
	/*std::cout<< v[0].X << "," << v[0].Y << "\t";
	std::cout<< v[1].X << "," << v[1].Y << std::endl;
	std::cout<< v[3].X << "," << v[3].Y << "\t"; 
	std::cout<< v[2].X << "," << v[2].Y << std::endl;*/
	if( abs(vd.X) <= 2 * boxWidth && abs(vd.Y) <= 2 * boxHeight )
		return true;
	return false;
}

// �жϵ��Ƿ���Բ��������
bool IUIObject::IsPointInCircle( s32 x, s32 y)
{
	//���Ȼ�ȡԪ���ĸ����㵱ǰ����Ļ�ϵľ�������
	matrix<f32> TransMat = AbsoluteTransformation;
	vector2d<f32> AbsPoints[4];
	ub::vector<f32> temPoint(3);
	temPoint(2) = 1;
	for( int i=0; i<4; i++ )
	{
		temPoint(0) = DestinationQuadrangle[i].X;
		temPoint(1) = DestinationQuadrangle[i].Y;
		temPoint = prod( temPoint, TransMat );
		AbsPoints[i].X = temPoint(0);
		AbsPoints[i].Y = temPoint(1);
	}
	//Ȼ���ȡԲ������뾶�����У�ȡ���ߣ�
	//f32 r = ( ( DestinationQuadrangle[2] - DestinationQuadrangle[0] ).getLength() ) / 2;
	//vector2d<f32> wh = DestinationQuadrangle[2] - DestinationQuadrangle[0];
	vector2d<f32> wh = AbsPoints[2] - AbsPoints[0];
	f32 r = wh.X > wh.Y ? wh.X/2 :wh.Y/2;
	//�жϵ��Ƿ���԰��
	vector2d<f32> point = vector2d<f32>( (f32)x, (f32)y );
	f32 dis = ( point - GetAbsolutePosition() ).getLength();
	if ( dis <= r )
		return true;
	
	return false;
}

void IUIObject::AddFunc( const std::string& eventName, const std::string& funcName, const std::string& ModuleName )
{
	FuncMap[ eventName ] = EventHandler( funcName, ModuleName );
}

void IUIObject::RemoveFunc( const std::string& funcName )
{
	FuncMap.erase( funcName );
}

void IUIObject::PythonFunc( const std::string& eventName )
{
	try
	{	
		auto func = FuncMap.find( eventName );
		if ( func != FuncMap.end() )
		{			
			using namespace boost::python;
			auto FuncInfo = (*func).second;	//FuncMap[ eventName ];		// Speed Up
			object module = import( FuncInfo.ModuleName.c_str() );
			object fun = module.attr( FuncInfo.FuncName.c_str() );
			fun( boost::ref( this ) );
		}
	}
	catch ( ... )
	{
		PyErr_Print();
	}
}

IUIObject* IUIObject::GetParent() const
{
	return Parent;
}

void IUIObject::CloneMembersFrom( IUIObject* toCopyFrom )
{
	BOOST_FOREACH( IUIAnimator* ani, Animators )
	{
		IUIAnimator* a = ani->Clone();
		if ( a )
		{
			AddAnimator( a );
			a->drop();
		}
	}

	BOOST_FOREACH( IUIObject* child, Children )
	{
		IUIObject* object = child->Clone();
		AddChild( object );
		object->drop();
	}

	//toCopyFrom->Parent->AddChild( this );

	//SetParent( toCopyFrom->Parent );		

	Order		= toCopyFrom->Order;			
	IsVisible	= toCopyFrom->IsVisible;		
	Driver		= toCopyFrom->Driver;	

	Image		= toCopyFrom->Image;
	Image->grab();

	RelativeAlpha			= toCopyFrom->RelativeAlpha;				
	RelativeTranslation		= toCopyFrom->RelativeTranslation;		
	RelativeRotation		= toCopyFrom->RelativeRotation;			
	RelativeScale			= toCopyFrom->RelativeScale;				
	AbsoluteTransformation	= toCopyFrom->AbsoluteTransformation;	

	FuncMap			= toCopyFrom->FuncMap;	
	Name			= toCopyFrom->Name;				
	LeftTop			= toCopyFrom->LeftTop;					
	RightBottom		= toCopyFrom->RightBottom;		
	bAntiAliasing	= toCopyFrom->bAntiAliasing;
	Shape			= toCopyFrom->Shape;						

	for ( int i = 0; i < 4; i++ )
	{
		DestinationQuadrangle[ i ] = toCopyFrom->DestinationQuadrangle[ i ];
	}
}
