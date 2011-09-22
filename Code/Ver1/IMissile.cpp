#include "IMissile.h"
#include <irrlicht.h>

using namespace irr;

scene::ISceneCollisionManager* Missile::m_pColMan = NULL;
std::map<scene::ISceneNode*, std::string>*	Missile::m_pModels = NULL;


scene::ISceneNode* Missile::TestCollision()
{
	core::line3d<f32> ray;							//������ײ��
	ray.start = m_pNode->getPosition();
	//�ӵ�����Զλ��
	ray.end = m_pNode->getPosition() + m_flyBehavior->GetDirection();
	core::vector3df intersection;
	core::triangle3df hitTriangle;

	scene::ISceneNode * selectedSceneNode =				//��ײ���
		m_pColMan->getSceneNodeFromRayBB( ray/*, intersection, hitTriangle, 1, 0*/); 

	if ( m_pModels->find( selectedSceneNode ) != m_pModels->end() )
	{
		//selectedSceneNode->drop();
		std::cout << "Hit!!!!!" << std::endl;

		return selectedSceneNode;
	}



	return NULL;
}
