#pragma once

#include "SceneNodeShader.h"
#include "MyIrrlichtEngine.h"
#include "BillBoardExplosionAnimator.h"


class ExplosionMyself
{
public:
	ExplosionMyself(ISceneNode* pN, vector3df pos) : m_pNode(pN), m_Pos(pos)
	{
		m_pSmgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();
		m_pDriver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
		m_pExplosiongBillBoard = m_pSmgr->addBillboardSceneNode(0);

		m_pExplosiongBillBoard->setMaterialTexture(0, m_pDriver->getTexture("../media/Space/sun2.png"));
		m_pExplosiongBillBoard->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
		m_pExplosiongBillBoard->setMaterialFlag(EMF_LIGHTING, false);
		m_pExplosiongBillBoard->setPosition(m_pNode->getAbsolutePosition());
		m_pExplosiongBillBoard->setSize(dimension2df(100.f, 100.f));
		m_pExplosiongBillBoard->setPosition(m_Pos);
	}

	void Explode()
	{
		vector3df v[8];
		vector3df center;
		center = m_pNode->getBoundingBox().getCenter();
		m_pNode->getBoundingBox().getEdges(v);
		f32 MaxDis = 0.0f;

		for (int i = 0; i < 8; i++)
		{
			MaxDis = v->getDistanceFrom(center) > MaxDis ? v->getDistanceFrom(center) : MaxDis;
		}

		MaxDis *= 2;

		m_pNode->setScale(vector3df(0));
		BillBoardExplosionAnimator* anim = new BillBoardExplosionAnimator(MaxDis);
		m_pExplosiongBillBoard->addAnimator( anim );
		anim->drop();
	}

	void EndExplode()
	{
		m_pNode->setScale(vector3df(1.0f));
	}

private:
	ISceneNode* m_pNode;
	IBillboardSceneNode* m_pExplosiongBillBoard;
	ISceneManager* m_pSmgr;
	IVideoDriver* m_pDriver;
	vector3df m_Pos;
};