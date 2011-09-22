#include "IMissile.h"


scene::ISceneCollisionManager* Missile::m_pColMan = NULL;

scene::ISceneNode* Missile::TestCollision()
{
	core::line3d<f32> ray;							//构造碰撞线
	ray.start = m_pNode->getPosition();
	//子弹的最远位置
	ray.end = m_pNode->getPosition() + m_flyBehavior->GetDirection() * 500.f;
	core::vector3df intersection;
	core::triangle3df hitTriangle;

	scene::ISceneNode * selectedSceneNode =				//碰撞检测
		m_pColMan->getSceneNodeFromRayBB (
		ray/*, intersection, hitTriangle, 1, 0*/); 

	if ( selectedSceneNode )
	{
		std::cout << "Hit!!!!!" << std::endl;
	}



	return NULL;
}
