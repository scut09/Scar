/********************************************************************
    ����ʱ��: 2011-10-22   20:03
    �ļ���:   CSceneNodeAnimatorCollisionResponse.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     ������ӦAnimator

*********************************************************************/


#ifndef CSceneNodeAnimatorCollisionResponse_h__
#define CSceneNodeAnimatorCollisionResponse_h__

#include <irrlicht.h>

using namespace irr;
using namespace scene;


/*
** ���֣�CSceneNodeAnimatorCollisionResponse
** ˵������ײ��Ӧ
**
*/
class CSceneNodeAnimatorMyCollisionResponse : public ISceneNodeAnimator
{
public:
	CSceneNodeAnimatorMyCollisionResponse( ISceneCollisionManager* col );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone(
		ISceneNode* node,
		ISceneManager* newManager = 0 );

private:
	ISceneCollisionManager*		CollisionMgr;
	core::vector3df				LastPoint;
	bool						FirstRun;
};




#endif // CSceneNodeAnimatorCollisionResponse_h__