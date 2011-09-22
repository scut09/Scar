#include "IMissile.h"


scene::ISceneCollisionManager* Missile::m_pColMan = NULL;

scene::ISceneNode* Missile::TestCollision()
{
	core::line3d<f32> ray;							//������ײ��
	ray.start = m_pNode->getPosition();
	//�ӵ�����Զλ��
	ray.end = m_pNode->getPosition() + m_flyBehavior->GetDirection() * 500.f;
	core::vector3df intersection;
	core::triangle3df hitTriangle;

	scene::ISceneNode * selectedSceneNode =				//��ײ���
		m_pColMan->getSceneNodeFromRayBB (
		ray/*, intersection, hitTriangle, 1, 0*/); 

	if ( selectedSceneNode )
	{
		std::cout << "Hit!!!!!" << std::endl;
	}



	return NULL;
}
