/********************************************************************
    ����ʱ��: 2011-10-22   19:19
    �ļ���:   IWeapon.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     ����

*********************************************************************/


#ifndef IWeapon_h__
#define IWeapon_h__

#include <typeinfo>
#include "CMeshSceneNode.h"

using namespace irr;



/*
** ���֣�ICollisionCallback
** ˵������ײ�ص�
**
*/
class IWeaponCollisionCallback
{
public:
	virtual void OnCollision( scene::ISceneNode* target ) = 0;
};




/*
** ���֣�IWeapon
** ˵������������
**
*/
class IWeapon : public irr::scene::CMeshSceneNode, public IWeaponCollisionCallback
{
public:
	IWeapon( irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr, s32 id,
		const core::vector3df& position, const core::vector3df& rotation,
		const core::vector3df& scale );


	virtual void OnCollision( scene::ISceneNode* target );

	
	//! ��¡һ���Լ�����Ҫ�ڷ��䵼��/�ڵ���ʱ��Ŀ��Ը���һ����������
	virtual irr::scene::ISceneNode* Clone( irr::scene::ISceneNode* newParent, irr::scene::ISceneManager* newManager ) = 0;

protected:
	//! ����IWeapon�����Ը�w���ṩ�������࿽��IWeapon������
	virtual void CloneAttributeTo( IWeapon* w )
	{
		Amount = w->Amount;
		Damage = w->Damage;
	}

private:
	//! ��ֹʹ��CMeshSceneNode��clone����
	virtual ISceneNode* clone( irr::scene::ISceneNode* newParent=0, irr::scene::ISceneManager* newManager=0 )
	{
		return NULL;
	}

protected:

	s32		Amount;			// ��������
	s32		Damage;			// ɱ����

};




#endif // IWeapon_h__