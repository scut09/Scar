/********************************************************************
    ����ʱ��: 2011-10-22   19:19
    �ļ���:   IWeapon.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     ����

*********************************************************************/


#ifndef IWeapon_h__
#define IWeapon_h__

#include <typeinfo>
#include "CBillboardSceneNode.h"
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


using namespace irr;

/*
** ���֣�IWeapon
** ˵������������
**
*/
class IWeapon : public irr::scene::CBillboardSceneNode, public IWeaponCollisionCallback
{
protected:
	u32 Interval;			// ������ ms
	f32 Velocity;			// �������� pixel / s
	u32 Life;				// ������ʱ�� ms
	s32	Damage;				// ɱ����
	s32 Remain;				// ��ҩ����

public:

	IWeapon( irr::scene::ISceneManager* mgr, irr::scene::ISceneNode* parent = 0, s32 id = -1,	
		const irr::core::vector3df& position = core::vector3df( 0, 0, 0 ),
		const core::dimension2d<f32>& size = core::dimension2d<f32>( 5, 5 ),
		video::SColor colorTop=video::SColor(0xFFFFFFFF),video::SColor colorBottom=video::SColor(0xFFFFFFFF));


	virtual void OnCollision( scene::ISceneNode* target );

	// ���úͻ�ȡ��ҩ����
	const s32 GetRemain() const;
	void SetRemain( s32 num );

	// ���úͻ�ȡ����ɱ����
	const s32 GetDamage() const;
	void SetDamage( s32 damage );
	
	// ���úͻ�ȡ������
	const u32 GetInterval() const;
	void SetInterval( u32 interval );

	// ���úͻ�ȡ��������
	const f32 GetVelocity() const;
	void SetVelocity( f32 velocity );

	// ���úͻ�ȡ������ʱ��
	const u32 GetLife() const;
	void SetLife( u32 life );
	
	//! ��¡һ���Լ�����Ҫ�ڷ��䵼��/�ڵ���ʱ��Ŀ��Ը���һ����������
	virtual irr::scene::ISceneNode* Clone( irr::scene::ISceneNode* newParent, irr::scene::ISceneManager* newManager ) = 0;

protected:
	//! ����IWeapon�����Ը�w���ṩ�������࿽��IWeapon������
	virtual void CloneAttributeFrom( IWeapon* w );

private:
	//! ��ֹʹ��CMeshSceneNode��clone����
	virtual ISceneNode* clone( irr::scene::ISceneNode* newParent=0, irr::scene::ISceneManager* newManager=0 )
	{
		return NULL;
	}

};




#endif // IWeapon_h__