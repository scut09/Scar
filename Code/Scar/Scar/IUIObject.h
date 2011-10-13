#ifndef IUIObject_h__
#define IUIObject_h__

#include "def.h"
#include <list>
#include "IUIAnimator.h"
#include <irrlicht.h>

using namespace irr;

class IUIAnimator;


class IUIObject : public irr::IReferenceCounted
{
	std::list< IUIAnimator* > Animators;
	std::list< IUIObject* > Children;
	IUIObject* Parent;

public:
	 //���ж����б��е����ж���
	void OnAnimate( u32 time )
	{
		auto iter = Animators.begin();
		while ( iter != Animators.end() )
		{
			auto i = iter;
			iter++;
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
		if ( Parent )
			Parent->RemoveChild( this );
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
