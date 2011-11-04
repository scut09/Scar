/********************************************************************
    创建时间: 2011-10-13   14:36
    文件名:   IUIObject.h
    作者:     华亮 屠文翔
    说明:     IUIObject接口，2D场景节点的接口。
			我们可以为实现IUIObject接口的类添加IUIAnimator动画以实现动画

*********************************************************************/



#include "IUIObject.h"
#include <algorithm>
#include "MyIrrlichtEngine.h"

//#pragma warning( push )y


IUIObject::~IUIObject()
{
	RemoveAll();			// 删除所有孩子,将孩子的引用计数器减一，设置它的Parent为0
	//RemoveAnimators();		// 删除所有的动画，
	// 反正都要销毁了，为了性能，所以不需要使用RemoveAnimators里面的Animators.clear()
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
	//	//相应动画的接口
	//	(*i)->animateUIObject( this, time );
	//}
	for ( u32 i = 0; i < Animators.size(); i++ )
	{
		Animators[ i ]->animateUIObject( this, time );
	}

	//通知子节点运行动画列表
	auto it = Children.begin();
	for (; it != Children.end(); ++it)
		(*it)->OnAnimate( time );
}

void IUIObject::AddAnimator( IUIAnimator* ani )
{
	Animators.push_back( ani );
	ani->grab();
	//为所有子节点增加相应的动画
	//这个是历史遗留问题，可以删除这段了
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
	//删除元素
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
	grab();		// 增加自己的引用计数，放在在将自己从父节点中移除时被销毁
	remove();	// 将自己从父节点中移除

	// 用户可能输入为空
	Parent = parent;
	if ( parent )
		parent->AddChild( this );	//计数器将会在AddChild内部+1

	drop();		// 将自己的引用计数-1，等于是将控制权移交给父节点。当引用计数减为0是，自己会被delelte
}

void IUIObject::RemoveChild( IUIObject* node )
{
	node->Parent = 0;			// 这里不能使用SetParent()！
	//Children.remove( node );	// 将孩子从自己的子节点列表中移除
	//删除元素
	auto itr = std::find( Children.begin(), Children.end(), node );
	int diff = itr - Children.begin();
	Children.erase( Children.begin() + diff );

	node->drop();				// 孩子计数器-1
}

void IUIObject::AddChild( IUIObject* child )
{
	if ( ! child )	return;

	child->grab();				// 自己对child节点引用，所以对引用计数+1
	child->remove();			// 从原父节点中移除自己
	Children.push_back(child);
	child->Parent = this;		// 这里不能用SetParent，否则会无限递归到栈溢出
	
	// 根据孩子的Order排序
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
		(*iter)->Parent = 0;	// 这里不能使用SetParent()，否则在析构的时候，中途会把自己从Children里面移除，导致迭代器失效而崩溃
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


//装载图片
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

//获取相对变换矩阵
matrix<f32> IUIObject::GetRelativeTransformation() const
{
	matrix<f32> mat( 3, 3 );
	MAKE_INDENTITY3(mat);
	// 旋转
	f32 rad = RelativeRotation * core::DEGTORAD;
	mat(0,0) = cos(rad);	mat(0,1) = sin(rad);
	mat(1,0) = -sin(rad);	mat(1,1) = cos(rad);
	// 平移
	mat(2,0) = RelativeTranslation.X;
	mat(2,1) = RelativeTranslation.Y;
	// 缩放
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

	//设置模型坐标系，以原点为中心
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

	// 默认不适用反锯齿
	bAntiAliasing = false;

	UpdateAbsolutePosition();
}

//消息分派
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

//判断点是否在当前元件内部
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

// 判断点是否在矩形区域内
bool IUIObject::IsPointInSquare( s32 x, s32 y )
{
	//首先获取元件四个顶点当前在屏幕上的绝对坐标
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
	//求元件包围盒宽高
	vector2d<f32> v1 = AbsPoints[0] - AbsPoints[2];
	vector2d<f32> v2 = AbsPoints[1] - AbsPoints[3];
	f32 boxWidth = std::max( abs(v1.X), abs(v2.X) );
	f32 boxHeight = std::max( abs(v1.Y), abs(v2.Y) );
	
	/*std::cout<< "width: " << boxWidth << "  height: " << boxHeight << std::endl;
	std::cout<< AbsPoints[0].X << "," << AbsPoints[0].Y << "\t";
	std::cout<< AbsPoints[1].X << "," << AbsPoints[1].Y << std::endl;
	std::cout<< AbsPoints[3].X << "," << AbsPoints[3].Y << "\t"; 
	std::cout<< AbsPoints[2].X << "," << AbsPoints[2].Y << std::endl;*/
	
	//求四个顶点指向目标点的向量
	//并把这四个向量加在一起
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

// 判断点是否在圆形区域内
bool IUIObject::IsPointInCircle( s32 x, s32 y)
{
	//首先获取元件四个顶点当前在屏幕上的绝对坐标
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
	//然后获取圆形区域半径（内切，取长边）
	//f32 r = ( ( DestinationQuadrangle[2] - DestinationQuadrangle[0] ).getLength() ) / 2;
	//vector2d<f32> wh = DestinationQuadrangle[2] - DestinationQuadrangle[0];
	vector2d<f32> wh = AbsPoints[2] - AbsPoints[0];
	f32 r = wh.X > wh.Y ? wh.X/2 :wh.Y/2;
	//判断点是否在园外
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
