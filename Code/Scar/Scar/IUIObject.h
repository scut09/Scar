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
#include <functional>

using namespace irr;
using namespace irr::core;
using namespace irr::video;

class IUIAnimator;


/*
** ���֣�IUIObject
** ˵����IUIObject�Ľӿ��࣬����������ֽڵ㣬��ɾ�������Լ�����
**
*/
class IUIObject : public irr::IReferenceCounted
{
protected:
	std::list< IUIAnimator* > Animators;
	std::list< IUIObject* > Children;
	IUIObject* Parent;
	s32 Order;									//Ԫ��������ͬһ��ʱ�İڷ�˳��
	vector2d<f32> Center;						//���ε����ĵ�
	IVideoDriver * Driver;						//Driverָ��
	f32 Alpha;									//Ԫ��͸����
	ITexture * Image;							//Ӧ����UI�ϵ�ͼƬ

public:
	vector2d<f32> DstQuar[4];					//��ʾ�������
	
									
public:
	//IUIObject( s32 order = 0 );

	IUIObject( IVideoDriver * driver, const vector2d<f32>& pos, s32 width, s32 height, s32 order = 0 );

	//����UIͼƬ
	void SetImage( char * );

	//�����ĵ�Ϊ��׼����Ԫ��λ��
	void SetCenter( const vector2d<f32>& pos );
	//�ı����ĵ�λ��
	bool ModifyCenter( const vector2d<f32>& pos );
	//��ȡԪ�����ĵ�λ��
	const vector2d<f32>& GetCenter() const;

	//���Alphaֵ
	f32 GetAlpha();
	//����Alphaֵ
	void SetAlpha( f32 alpha );

	virtual ~IUIObject();

	//����Ԫ��˳��
	virtual s32 GetOrder() const;
	//��ȡԪ��˳��
	virtual void SetOrder( s32 order );

	//���Ƶ�ǰ�ڵ�
	virtual void Draw() = 0;

	//������ ���Ƶ�ǰ�ڵ��Լ���ǰ�ڵ�������ӽڵ�
	virtual void DrawTree();

	 //���ж����б��е����ж���
	virtual void OnAnimate( u32 time );

	//��ĳ���������붯�������б�
	virtual void AddAnimator( IUIAnimator* ani	);

	//��ȡ�����б�
	virtual const std::list< IUIAnimator* >& GetAnimators() const;

	//��ĳ�������Ӷ����б���ɾ��
	virtual void RemoveAnimator( IUIAnimator* ani );

	//��ն����б�
	virtual void RemoveAnimators();

	//���ø��ڵ�
	virtual void SetParent( IUIObject* parent );

	//ɾ���ӽڵ�
	virtual void RemoveChild( IUIObject* node );

	//�����ӽڵ�
	virtual void AddChild( IUIObject* child );

	virtual void RemoveAll();

	//��ȡ�ӽڵ��б�
	virtual const std::list< IUIObject* >& GetChildren() const;

	// ���Լ��Ӹ��ڵ���ɾ��
	// Ϊ�˺͸���irr::IReferenceCounted�е�drop��grab���һ��������������Сд��ͷ
	virtual void remove();

};
#endif // IUIObject_h__
