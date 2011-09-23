#include "IMissile.h"
#include <irrlicht.h>
#include <cmath> 

using namespace irr;

scene::ISceneCollisionManager* Missile::m_pColMan = NULL;
std::map<scene::ISceneNode*, std::string>*	Missile::m_pModels = NULL;


extern scene::ICameraSceneNode* camera;


scene::ISceneNode* Missile::TestCollision()
{

	core::line3d<f32> ray;							//构造碰撞线
	//ray.start = camera->getPosition();
	//ray.end = ray.start + (camera->getTarget() - ray.start).normalize() * 10000.0f;
	ray.start = m_pNode->getPosition();
	//子弹的最远位置
	ray.end = ray.start + m_flyBehavior->GetDirection() * 10.f;
	core::vector3df intersection;
	core::triangle3df hitTriangle;

	scene::ISceneNode * selectedSceneNode 
		= m_pColMan->getSceneNodeAndCollisionPointFromRay( ray, intersection, hitTriangle ); 
	
	

	if ( selectedSceneNode )
	{
		if ( m_pModels->find( selectedSceneNode ) != m_pModels->end() )
		{
			//selectedSceneNode->drop();
			std::cout << "Hit!!!!!" << std::endl;

			PRINT_POSITION( m_pNode->getPosition() );
			PRINT_POSITION( selectedSceneNode->getPosition() );
			PRINT_POSITION( ray.start );
			PRINT_POSITION( ray.end );


			return selectedSceneNode;
		}
	}


	return NULL;
}
