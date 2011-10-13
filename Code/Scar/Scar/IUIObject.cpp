/********************************************************************
    ����ʱ��: 2011-10-13   14:36
    �ļ���:   IUIObject.h
    ����:     ���� ������
    ˵��:     IUIObject�ӿڣ�2D�����ڵ�Ľӿڡ�
			���ǿ���Ϊʵ��IUIObject�ӿڵ������IUIAnimator������ʵ�ֶ���

*********************************************************************/

#include "IUIObject.h"

IUIObject::IUIObject()
	: Parent( 0 )
{
}

IUIObject::~IUIObject()
{
	RemoveAll();			// ɾ�����к���,�����ӵ����ü�������һ����������ParentΪ0
	RemoveAnimators();		// ɾ�����еĶ���
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
	for( auto iter = Children.begin(); iter != Children.end(); ++iter )
	{
		IUIAnimator* aniCopy = ani->Clone(); 
		(*iter)->AddAnimator(aniCopy);
		aniCopy->drop();
	}
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
		parent->AddChild( this );

	drop();		// ���Լ������ü�����1�������ü�����Ϊ0�ǣ��Լ��ᱻdelelte
}

void IUIObject::RemoveChild( IUIObject* node )
{
	Children.remove( node );
	node->drop();
}

void IUIObject::AddChild( IUIObject* child )
{
	if ( ! child )	return;

	child->grab();
	child->remove();			// ��ԭ���ڵ����Ƴ��Լ�
	Children.push_back(child);
	child->Parent = this;		// ���ﲻ����SetParent����������޵ݹ鵽ջ���
}

void IUIObject::RemoveAll()
{
	for ( auto iter = Children.begin(); iter != Children.end(); ++iter )
	{
		(*iter)->SetParent( 0 );
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
