/********************************************************************
    ����ʱ��: 2011-10-22   20:03
    �ļ���:   CSceneNodeAnimatorCollisionResponse.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     ������ӦAnimator

*********************************************************************/


#ifndef CSceneNodeAnimatorCollisionResponse_h__
#define CSceneNodeAnimatorCollisionResponse_h__

#include <irrlicht.h>
#include <functional>

using namespace irr;
using namespace scene;

typedef std::function< void( ISceneNode* node, ISceneNode* target_node ) >	CollisionCallbackType;

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

	// ������ײʱ�Ļص�����
	void SetCollisionCallback( CollisionCallbackType func )
	{
		Func = func;
	}

private:
	ISceneCollisionManager*		CollisionMgr;
	core::vector3df				LastPoint;			// �ϴεĵ�
	bool						FirstRun;			// �Ƿ��һ������
	CollisionCallbackType		Func;				// ��ײʱ�Ļص�
};




#endif // CSceneNodeAnimatorCollisionResponse_h__