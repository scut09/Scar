/********************************************************************
	����ʱ��: 2011:9:27   14:55
	�ļ���:   IFly.h
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     

*********************************************************************/

#ifndef _IFLY_H_
#define _IFLY_H_

#include "base.h"
#include "IMovable.h"

#include <irrlicht.h>

using namespace irr;

/*
** ���֣�IFly
** ˵�����ɷ�������Ľӿ�
**
*/
class IFly : public IMovable
{
public:

	//************************************
	// ������:  IFly::LoadSceneNode
	// ����ֵ:  void
	// ����:    scene::ISceneNode * pNode
	// ��������:
	// ������   Ϊ���������ͼ�νڵ�
	//************************************
	virtual void LoadSceneNode( scene::ISceneNode* pNode ) = 0;

	//************************************
	// ������:  IFly::GetSceneNode
	// ����ֵ:  scene::ISceneNode*
	// ��������:
	// ������   ��ȡ�������е�ģ�ͽڵ�
	//************************************
	virtual scene::ISceneNode* GetSceneNode() = 0;

	//************************************
	// ������:  IFly::SetPostion
	// ����ֵ:  void
	// ����:    const core::vector3df & pos
	// ��������:
	// ������   ���÷���������������������λ��
	//************************************
	virtual void SetPostion( const core::vector3df& pos ) = 0;		

	//************************************
	// ������:  IFly::SetRotation
	// ����ֵ:  void
	// ����:    const core::vector3df & rot
	// ��������:
	// ������   ���÷��������ת�Ƕ�
	//************************************
	virtual void SetRotation( const core::vector3df& rot ) = 0;		

	//************************************
	// ������:  IFly::GetPosition
	// ����ֵ:  core::vector3df
	// ��������:
	// ������   ��ȡ�������λ��
	//************************************
	virtual core::vector3df GetPosition() = 0;		// ��ȡλ��

	//************************************
	// ������:  IFly::TestCollision
	// ����ֵ:  scene::ISceneNode*
	// ��������:
	// ������   ��ײ��⣬��ʷ�������⣬��ɾ������Ϊ�ص�����������ײ����
	//************************************
	virtual scene::ISceneNode* TestCollision() = 0;	// �Ƿ�����ײ

	//************************************
	// ������:  IFly::Drop
	// ����ֵ:  void
	// ��������:
	// ������   ɾ���ڲ��ڵ�
	//************************************
	virtual void Drop() = 0;
};


/*
** ���֣�IFlyBehavior
** ˵�������е���Ϊ
**
*/
class IFlyBehavior
{
public:
	~IFlyBehavior() {}

	//************************************
	// ������:  IFlyBehavior::SetOwner
	// ����ֵ:  void
	// ����:    IFly * pFly
	// ��������:
	// ������   
	//************************************
	virtual void SetOwner( IFly* pFly ) = 0;	

	//************************************
	// ������:  IFlyBehavior::Fly
	// ����ֵ:  core::vector3df
	// ����:    const core::vector3df & pos
	// ��������:
	// ������   
	//************************************
	virtual core::vector3df Fly( const core::vector3df& pos ) = 0;

	//************************************
	// ������:  IFlyBehavior::GetDirection
	// ����ֵ:  core::vector3df
	// ��������:
	// ������   
	//************************************
	virtual core::vector3df GetDirection() = 0;
};


#endif
