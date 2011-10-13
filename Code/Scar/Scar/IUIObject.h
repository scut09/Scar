#ifndef IUIObject_h__
#define IUIObject_h__

#include "def.h"
#include <list>
#include "IUIAnimator.h"
#include <irrlicht.h>

using namespace irr;

class IUIAnimator;

//////////////////////////////////////////////////////////////////
//���ƣ�IUIObject
//������UIObject�Ľӿ��࣬����������ֽڵ㣬��ɾ�������Լ�����
//���ߣ�����,������
//////////////////////////////////////////////////////////////////
class IUIObject : public irr::IReferenceCounted
{
//public:
	std::list< IUIAnimator* > Animators;
	std::list< IUIObject* > Children;
	IUIObject* Parent;

public:
	//���Ƶ�ǰ�ڵ�
	virtual void Draw() = 0;

	//������ ���Ƶ�ǰ�ڵ��Լ���ǰ�ڵ�������ӽڵ�
	void DrawTree()
	{
		Draw();
		for(auto iter = Children.begin(); iter != Children.end(); ++iter)
		{
			(*iter)->DrawTree();
		}
	}

	 //���ж����б��е����ж���
	void OnAnimate( u32 time )
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

	//��ĳ���������붯�������б�
	void AddAnimator( IUIAnimator* ani	)
	{
		Animators.push_back( ani );
		ani->grab();
		//Ϊ�����ӽڵ�������Ӧ�Ķ���
		for( auto iter = Children.begin(); iter != Children.end(); ++iter )
		{
			IUIAnimator* aniCopy = ani->Clone(); 
			(*iter)->AddAnimator(aniCopy);
		}
	}

	//��ȡ�����б�
	const std::list< IUIAnimator* >& GetAnimators() const
	{
		return Animators;
	}

	//��ĳ�������Ӷ����б���ɾ��
	void RemoveAnimator( IUIAnimator* ani )
	{
		Animators.remove( ani );
		ani->drop();
	}

	//��ն����б�
	void RemoveAnimators()
	{
		for ( auto iter = Animators.begin(); iter != Animators.end(); ++iter )
		{
			(*iter)->drop();
		}
		Animators.clear();
	}

	//���ø��ڵ�
	void SetParent( IUIObject* parent )
	{
		//���������
		/*if ( Parent )
			Parent->RemoveChild( this );*/
		Parent = parent;
	}

	//ɾ���ӽڵ�
	void RemoveChild( IUIObject* node )
	{
		Children.remove( node );
		node->drop();
	}

	//�����ӽڵ�
	void AddChild( IUIObject* node )
	{
		Children.push_back( node );
		node->SetParent(this);
		node->grab();
	}

	//��ȡ�ӽڵ��б�
	const std::list< IUIObject* >& GetChildren() const
	{
		return Children;
	}

	//���Լ��Ӹ��ڵ���ɾ��
	void RemoveSelf()
	{
		if ( Parent )
			Parent->RemoveChild( this );
	}

};
#endif // IUIObject_h__
