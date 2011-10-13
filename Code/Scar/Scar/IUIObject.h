/********************************************************************
    ����ʱ��: 2011-10-13   14:36
    �ļ���:   IUIObject.h
    ����:     ���� ������
    ˵��:     IUIObject�ӿڣ�2D�����ڵ�Ľӿڡ�
			���ǿ���Ϊʵ��IUIObject�ӿڵ������IUIAnimator������ʵ�ֶ���

*********************************************************************/

#ifndef IUIObject_h__
#define IUIObject_h__

#include "def.h"
#include <list>
#include "IUIAnimator.h"
#include <irrlicht.h>

using namespace irr;

class IUIAnimator;


/*
** ���֣�IUIObject
** ˵����UIObject�Ľӿ��࣬����������ֽڵ㣬��ɾ�������Լ�����
**
*/
class IUIObject : public irr::IReferenceCounted
{
//public:
	std::list< IUIAnimator* > Animators;
	std::list< IUIObject* > Children;
	IUIObject* Parent;

public:
	IUIObject();

	virtual ~IUIObject();

	//���Ƶ�ǰ�ڵ�
	virtual void Draw() = 0;

	//������ ���Ƶ�ǰ�ڵ��Լ���ǰ�ڵ�������ӽڵ�
	void DrawTree();

	 //���ж����б��е����ж���
	void OnAnimate( u32 time );

	//��ĳ���������붯�������б�
	void AddAnimator( IUIAnimator* ani	);

	//��ȡ�����б�
	const std::list< IUIAnimator* >& GetAnimators() const;

	//��ĳ�������Ӷ����б���ɾ��
	void RemoveAnimator( IUIAnimator* ani );

	//��ն����б�
	void RemoveAnimators();

	//���ø��ڵ�
	void SetParent( IUIObject* parent );

	//ɾ���ӽڵ�
	void RemoveChild( IUIObject* node );

	//�����ӽڵ�
	void AddChild( IUIObject* child );

	void RemoveAll();

	//��ȡ�ӽڵ��б�
	const std::list< IUIObject* >& GetChildren() const;

	// ���Լ��Ӹ��ڵ���ɾ��
	// Ϊ�˺͸���irr::IReferenceCounted�е�drop��grab���һ��������������Сд��ͷ
	void remove();

};
#endif // IUIObject_h__
