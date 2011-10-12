/********************************************************************
	����ʱ��: 2011-9-29   19:30
	�ļ���:   PythonWrapper.h
	����:     ���� Cedric Porter [ Stupid ET ]	
	˵��:     ������Python�е�C++��װ�࣬���ڰ�װ����ԭ������������

*********************************************************************/

#ifndef PythonWrapper_h__
#define PythonWrapper_h__

#include <irrlicht.h>
#include "AllAnimators.h"
#include "def.h"

using namespace irr;

/*
** ���֣�PythonSColor
** ˵����Ϊ�˼���SColor
**
*/
struct PythonSColor
{
	f32 alpha;
	f32 red;
	f32 green;
	f32 blue;
};

/*
** ���֣�PythonSLight
** ˵����Ϊ�˼���SLight
**
*/
struct PythonSLight
{
	PythonSColor AmbientColor;
	PythonSColor DiffuseColor;
	PythonSColor SpecularColor;
};

/*
** ���֣�PythonVector3df
** ˵��������vector3df
**
*/
struct PythonVector3df
{
	f32 x;
	f32 y;
	f32 z;

	PythonVector3df( f32 xx = 0, f32 yy = 0, f32 zz = 0 ) : x( xx ), y( yy ), z( zz ) {}

	core::vector3df Getvector3df()
	{
		return core::vector3df( x, y, z );
	}
};

/*
** ���֣�AnimatorWrapper
** ˵����Python�����࣬���ڰ�װAnimator 
**
*/
struct AnimatorWrapper
{
	AnimatorWrapper() : ptr( 0 ) {}
	ISceneNodeAnimator* ptr;

	void Drop()
	{
		BOOST_ASSERT( ptr );

		ptr->drop();
	}
};

/*
** ���֣�PythonSceneNode
** ˵������װISceneNode
**
*/
struct PythonSceneNode
{
	scene::ISceneNode*	ptr;

	PythonSceneNode() : ptr( NULL )
	{}

	void AddAnimator( AnimatorWrapper anim )
	{
		BOOST_ASSERT( ptr );
		ptr->addAnimator( anim.ptr );		
	}

	void RemoveAnimator( AnimatorWrapper anim )
	{
		BOOST_ASSERT( ptr );
		ptr->removeAnimator( anim.ptr );
	}

	void SetPosition( f32 x, f32 y, f32 z )
	{
		BOOST_ASSERT( ptr );
		ptr->setPosition( core::vector3df( x, y, z ) );
	}

	PythonVector3df GetPosition()
	{
		BOOST_ASSERT( ptr );
		return PythonVector3df( ptr->getPosition().X, ptr->getPosition().Y, ptr->getPosition().Z );
	}

	void SetRotation( f32 x, f32 y, f32 z )
	{
		BOOST_ASSERT( ptr );
		ptr->setRotation( core::vector3df( x, y, z  ) );
	}

	PythonVector3df GetRotation()
	{
		BOOST_ASSERT( ptr );
		return PythonVector3df( ptr->getRotation().X, ptr->getRotation().Y, ptr->getRotation().Z );
	}

	void Grab()
	{
		BOOST_ASSERT( ptr );
		ptr->grab();
	}

	void Drop()
	{
		BOOST_ASSERT( ptr );
		ptr->drop();
	}

	void Remove()
	{
		BOOST_ASSERT( ptr );
		ptr->remove();
	}
};


/*
** ���֣�ModelManagerWrapper
** ˵����Python�����࣬���ڰ�װModelMananger
**
*/
class ModelManagerWrapper
{
public:
	void AddMesh( const std::string& meshID, const std::string& meshFilename, const std::string& textureFilename );

	void AddLight( const PythonSLight& light, f32 x, f32 y, f32 z );

	PythonSceneNode AddSceneNodeByMeshID( const std::string& meshID, bool bTestCollision = false );
};




/*
** ���֣�AnimationManagerSlaver
** ˵����Python�����࣬���ڴ���Animator 
**
*/
class AnimationManagerWrapper
{
public:
	AnimatorWrapper CreateFlyStraightAutoDelAnimator( PythonVector3df start, PythonVector3df end, u32 timeForWay, u32 now )
	{
		AnimatorWrapper ani;

		ani.ptr = new CSceneNodeAnimatorSelfDelFlyStraight( start.Getvector3df(), end.Getvector3df(), timeForWay, now );

		return ani;
	}

};

/*
** ���֣�TimerWrapper
** ˵����һ���ṩ����ʱ��İ�װ��
**
*/
class TimerWrapper
{
public:
	u32 GetTime();
};



#endif // PythonWrapper_h__