#ifndef ShipCrashWarnAnimator_h__
#define ShipCrashWarnAnimator_h__

/********************************************************************
	��������:	2011/12/06
	�ļ���: 	C:\Users\Administrator\Desktop\����\SCAR��Ŀ��\opengl-scut\Code\Scar\Scar\ShipCrashWarnAnimator.h
	����:		������
	
	����:		�ṩ��������ײԤ��
*********************************************************************/

#include <irrlicht.h>
#include "MyIrrlichtEngine.h"
#include "MultiplayerScene.h"
//#include <functional>
#include <iostream>

using namespace irr;
using namespace scene;

//typedef std::function< void( ISceneNode* node, const ISceneNode* ColNode, core::vector3df ColPos ) >	KidCollisionCallbackType;

class ShipCrashWarnAnimator : public ISceneNodeAnimator
{
public:
	ShipCrashWarnAnimator( ISceneCollisionManager* col, ITriangleSelector* sel, f32 radius )
	{
		CollisionMgr = col;
		TriSelector = sel;
		FirstRun = true;
		Radius = radius;
		//Func = []( ISceneNode*, const ISceneNode*, core::vector3df ) {};
	}

	virtual void animateNode( ISceneNode* node, u32 timeMs )
	{
		if (FirstRun)
		{
			FirstRun = false;
			LastPos = node->getPosition();
		}

		core::vector3df NowPos = node->getPosition();
		//ICameraSceneNode* camera = static_cast<ICameraSceneNode*>(node);
		//vector3df decPoint = (camera->getTarget() - camera->getPosition()).normalize() * Radius;
		vector3df decPoint = (NowPos - LastPos).normalize() * Radius;
		core::line3df Ray(NowPos, decPoint);

		bool IsCol = CollisionMgr->getCollisionPoint( Ray, TriSelector, ColPosition, ColTriangle, ColSceneNode );
		if ( IsCol )
		{
			// ����ǽ
			//node->setPosition( LastPos + (LastPos - NowPos).normalize() * 10 );
			// ���ûص�����
			//Func( node, ColSceneNode, ColPosition );
			//std::cout<< "!_!_!_!_!_!_!_!_"<< std::endl;
			// ��ʾԤ����Ϣ
			static_cast<MultiplayerScene*>(MyIrrlichtEngine::GetEngine()->GetGameSceneManager()->GetCurrentGameScene())->m_playerHelper->AddWarnMsg(InfoAndWarn::PIW_CrashWarn);
		}

		LastPos = NowPos;
	}

	virtual ISceneNodeAnimator* createClone(
		ISceneNode* node,
		ISceneManager* newManager = 0 )
	{
		return 0;
	}

	//// ������ײʱ�Ļص�����
	//void SetCollisionCallback( KidCollisionCallbackType func )
	//{
	//	Func = func;
	//}

private:
	ISceneCollisionManager*		CollisionMgr;
	ITriangleSelector*			TriSelector;

	core::vector3df				LastPos;			// �ϴε�λ��
	bool						FirstRun;			// �Ƿ��һ������
	f32							Radius;				// Ԥ���뾶

	//KidCollisionCallbackType		Func;				// ��ײʱ�Ļص�
	const ISceneNode*			ColSceneNode;		// ����ײ�Ľڵ�
	core::vector3df				ColPosition;		// ��ײ������λ��
	core::triangle3df			ColTriangle;		// ��ײ������������
};

#endif // ShipCrashWarnAnimator_h__
