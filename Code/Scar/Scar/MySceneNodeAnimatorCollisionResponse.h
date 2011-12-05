#ifndef MySceneNodeAnimatorCollisionResponse_h__
#define MySceneNodeAnimatorCollisionResponse_h__

/********************************************************************
	����ʱ��:	2011/12/04
	�ļ�����: 	MySceneNodeAnimatorCollisionResponse
	����:		������ - Kid
	
	����:		ʹ��triangle selector����ײ��Ӧ
*********************************************************************/

#include <irrlicht.h>
#include <functional>
#include <iostream>

using namespace irr;
using namespace scene;

typedef std::function< void( ISceneNode* node, const ISceneNode* ColNode, core::vector3df ColPos ) >	KidCollisionCallbackType;

class MySceneNodeAnimatorCollisionResponse : public ISceneNodeAnimator
{
public:
	MySceneNodeAnimatorCollisionResponse( ISceneCollisionManager* col, ITriangleSelector* sel )
	{
		CollisionMgr = col;
		TriSelector = sel;
		FirstRun = true;
		Func = []( ISceneNode*, const ISceneNode*, core::vector3df ) {};
	}

	virtual void animateNode( ISceneNode* node, u32 timeMs )
	{
		if (FirstRun)
		{
			FirstRun = false;
			LastPos = node->getPosition();
		}

		core::vector3df NowPos = node->getPosition();
		core::line3df Ray(LastPos, NowPos);

		bool IsCol = CollisionMgr->getCollisionPoint( Ray, TriSelector, ColPosition, ColTriangle, ColSceneNode );
		if ( IsCol )
		{
			// ����ǽ
			//node->setPosition( LastPos + (LastPos - NowPos).normalize() * 10 );
			// ���ûص�����
			Func( node, ColSceneNode, ColPosition );
			//std::cout<< "!_!_!_!_!_!_!_!_"<< std::endl;
		}
		else
			LastPos = NowPos;
	}

	virtual ISceneNodeAnimator* createClone(
		ISceneNode* node,
		ISceneManager* newManager = 0 )
	{
		return 0;
	}

	// ������ײʱ�Ļص�����
	void SetCollisionCallback( KidCollisionCallbackType func )
	{
		Func = func;
	}

private:
	ISceneCollisionManager*		CollisionMgr;
	ITriangleSelector*			TriSelector;

	core::vector3df				LastPos;			// �ϴε�λ��
	bool						FirstRun;			// �Ƿ��һ������

	KidCollisionCallbackType		Func;				// ��ײʱ�Ļص�
	const ISceneNode*			ColSceneNode;		// ����ײ�Ľڵ�
	core::vector3df				ColPosition;		// ��ײ������λ��
	core::triangle3df			ColTriangle;		// ��ײ������������
};

#endif // MySceneNodeAnimatorCollisionResponse_h__
