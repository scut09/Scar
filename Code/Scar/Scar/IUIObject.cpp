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
		//相应动画的接口
		(*i)->animateUIObject( this, time );
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
	Children.remove( node );	// 将孩子从自己的子节点列表中移除
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
	Children.sort( []( IUIObject* lhs, IUIObject* rhs )->bool
	{
		return lhs->GetOrder() < rhs->GetOrder();
	});




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

const std::list< IUIObject* >& IUIObject::GetChildren() const
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
	Image = Driver->getTexture( filename );
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

IUIObject::IUIObject( IUIObject* parent, s32 width, s32 height, s32 order /*= 0*/, const vector2d<f32>& position /*= vector2d<f32>( 0, 0 )*/, f32 rotdeg /*= 0*/, const vector2d<f32>& scale /*= vector2d<f32>( 1.f, 1.f ) */ ) :
Parent(NULL), Order(order), AbsoluteTransformation( 3, 3 ), Image( 0 )
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

	UpdateAbsolutePosition();
}
