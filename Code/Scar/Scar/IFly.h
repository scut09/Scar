/*
** ���ߣ�����
** ˵����
**
*/

#include "base.h"

#include <irrlicht.h>

#ifndef _IFLY_H_
#define _IFLY_H_

using namespace irr;


/*
** ���֣�IFly
** ˵�����ɷ�������Ľӿ�
**
*/
class IFly : public IMovable
{
public:
	virtual void LoadSceneNode( scene::ISceneNode* pNode ) = 0;
	virtual scene::ISceneNode* GetSceneNode() = 0;
	virtual void SetPostion( const core::vector3df& pos ) = 0;					// ����λ��
	virtual void SetRotation( const core::vector3df& rot ) = 0;					// ������ת�Ƕȣ��������ȶ
	virtual core::vector3df GetPosition() = 0;		// ��ȡλ��
	virtual scene::ISceneNode* TestCollision() = 0;	// �Ƿ�����ײ
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
	virtual void SetOwner( IFly* pFly ) = 0;	
	virtual core::vector3df Fly( const core::vector3df& pos ) = 0;
	virtual core::vector3df GetDirection() = 0;
};


#endif
