/********************************************************************
    ����ʱ��: 2011-10-13   14:38
    �ļ���:   IUIAnimator.h
    ����:     ���� ������
    ˵��:     2D�����ӿڣ������Ҫ�����Լ��Ķ���������ֻ��Ҫʵ��IUIAnimator�ӿڣ�
			�����Ϊ2D�����ڵ�����Լ��Ķ�����

*********************************************************************/


#ifndef UIAnimator_h__
#define UIAnimator_h__

#include <irrlicht.h>
using namespace irr;

class IUIObject;

//////////////////////////////////////////////////////////////////
//���ƣ�IUIAnimator
//�����������Ľӿ��࣬���еĶ����������Դ���
//���ߣ�����
//////////////////////////////////////////////////////////////////
class IUIAnimator : public irr::IReferenceCounted
{
public:
	virtual ~IUIAnimator() {}

	//************************************
	// ������:  IUIAnimator::animateUIObject
	// ����ֵ:  bool
	// ����:    IUIObject * node		���뱻�������õ�2D�ڵ�
	// ����:    u32 timeMS			���뵱ǰ������ʱ�䣬
	//								ʱ����video::IVideoDriver::GetTimer()->GetTime()�ṩ
	// ��������:
	// ������   ��IUIObject������OnAnimate()ʱ��
	//			IUIObject���������ע�ᵽ�����IUIAnimator��animateUIObject( this, timeMS )��
	//************************************
	virtual bool animateUIObject( IUIObject* node, u32 timeMS ) = 0;

	virtual IUIAnimator* Clone() = 0;
};

#endif // UIAnimator_h__
