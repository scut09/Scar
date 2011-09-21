#include "Chreo.h"

Chreo::Chreo(int index,vector3df position)
{
	m_index = index;
	
	m_IsSquat = false;
	
	Init(position);
	m_rot = vector3df(0,0,0);
	m_speed = 5;
	m_HP = 100;
	m_maxHP = 100;

	m_killCount = 0;
	m_beKill = 0;
	
}

Chreo::~Chreo(void)
{
	//m_camera->remove();
}

void Chreo::Updata()
{
	core::line3d<f32> ray;
	ray.start = m_camera->getPosition();
	ray.end = ray.start;
	ray.end.Y -= 1000;

	
	core::vector3df intersection;	
	core::triangle3df hitTriangle;

	scene::ISceneCollisionManager* collMan = g_smgr->getSceneCollisionManager();
	scene::ISceneNode * selectedSceneNode =
		collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, 1, 0);	//与地形碰撞检测
	
	if(selectedSceneNode)
	{
		intersection.Y+=m_IsSquat?60:120;	//如果是蹲下 摄像机的位置降低
		m_camera->setPosition(intersection);
	}	
}

bool Chreo::MoveTo( int direction, int y, int z)
{
	vector3df move;

	float speed = m_IsSquat? m_speed/5:m_speed;

	switch(direction)
	{
	case DIR_UP:
		{
			move = vector3df(0, 0, speed);
			break;
		}
	case DIR_DOWN:
		{
			move = vector3df(0, 0, -speed);
			break;
		}
	case DIR_LEFT:
		{
			move = vector3df(-speed, 0, 0);
			break;
		}
	case DIR_RIGHT:
		{
			move = vector3df(speed, 0, 0);
			break;
		}
	case DIR_LUP:
		{
			move = vector3df(0, 0, speed);
			move.rotateXZBy(45);
			break;
		}
	case DIR_LDOWN:
		{
			move = vector3df(0, 0, -speed);
			move.rotateXZBy(-45);
			break;
		}
	case DIR_RUP:
		{
			move = vector3df(0, 0, speed);
			move.rotateXZBy(-45);
			break;
		}
	case DIR_RDOWN:
		{
			move = vector3df(0, 0, -speed);
			move.rotateXZBy(45);
			break;
		}
	default:
		{
			move = vector3df(0, 0, 0);
			break;
		}
	}
	move.rotateXZBy(-m_rot.Y);
	if (!CanMove(move))
	{
		return false;
	}
	m_camera->setPosition(move + m_camera->getPosition());

	Updata();		//更新高度

	UpdataLookAt();	//修正摄像机的目标位置

	return true;

	
}



void Chreo::Init(vector3df position)
{	
	m_ReSetCount = 0;
	m_isdeath = false;
	m_AnimEnd = true;
	m_camera = g_smgr->addCameraSceneNode();

	m_camera->setPosition(core::vector3df(position));	
	
	
	UpdataLookAt();

	m_camera->setFarValue(42000.0f);

	Updata();		//更新高度


	
	g_guienv->addImage(g_driver->getTexture("image\\zx.png"), core::position2d<s32>(492,365));

	m_gun = g_smgr->addAnimatedMeshSceneNode(g_smgr->getMesh("model/hreo/gun.md2"),
		m_camera);
	m_gun->setPosition(core::vector3df(-2,0,0)); // Put its feet on the floor.
	m_gun->setRotation(core::vector3df(0,-90,0));

	m_gun->setMD2Animation(EMAT_RUN);
	m_gun->setAnimationEndCallback(this);
	m_gun->setLoopMode(false);
	m_gun->setAnimationSpeed(25.f);
	irr::video::ITexture* tx = g_driver->getTexture("model/hreo/gun.jpg");
	m_gun->setMaterialTexture(0,tx);
	m_gun->setMaterialFlag(video::EMF_LIGHTING, false);

	g_device->getCursorControl()->setVisible(false);	

}


void Chreo::SetAinmState( int state )
{
	m_AnimState = state;
}

void Chreo::SetAinmState( const char* state )
{
	m_gun->setMD2Animation(state);
}
void Chreo::Trun( vector3df rot)
{
	m_rot = rot;
	UpdataLookAt();
}

irr::core::vector3df Chreo::GetRot()
{
	return m_rot;
}

void Chreo::UpdataLookAt()
{
	vector3df lookat = m_camera->getPosition();				//更新摄像机位置
	vector3df look(0, 0, 100);
	look.rotateYZBy(m_rot.X);
	look.rotateXZBy(-m_rot.Y);
	m_camera->setRotation(m_rot);
	m_camera->setTarget(lookat+look);
}

irr::core::vector3df Chreo::GetTagrt()
{
	return m_camera->getTarget();
}

irr::core::vector3df Chreo::GetPosition()
{
	return m_camera->getPosition();
}

bool Chreo::CanMove( vector3df& dirction )
{
	core::line3d<f32> ray;
	ray.start = m_camera->getPosition();
	ray.end = ray.start;
	ray.end += dirction*10;


	core::vector3df intersection;
	core::triangle3df hitTriangle;

	scene::ISceneCollisionManager* collMan = g_smgr->getSceneCollisionManager();
	scene::ISceneNode * selectedSceneNode =
		collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, 1, 0);	//与地形碰撞检测

	if(selectedSceneNode)
	{
		vector3df move = hitTriangle.getNormal();
		move.normalize();		
		return false;
	}
	return true;
}

irr::scene::ISceneNode* Chreo::GetSceneNode()
{
	return m_camera;
}

void Chreo::Death()
{
	m_isdeath = true;
	m_gun->setVisible(false);
}

bool Chreo::isDeath()
{
	return m_isdeath;
}

void Chreo::OnAnimationEnd( IAnimatedMeshSceneNode* node )
{	
	m_gun->setMD2Animation("null");
	m_gun->setAnimationSpeed(25.f);
	m_AnimEnd = true;
	
}

void Chreo::SetSquat( bool squat )
{
	m_IsSquat = squat;
	Updata();
	UpdataLookAt();

}

bool Chreo::GetSquat()
{
	return m_IsSquat;
}

void Chreo::ReSet( vector3df position )
{
	m_HP = m_maxHP;
	m_isdeath = false;
	m_IsSquat = false;
	m_ReSetCount = 0;

	m_camera->setPosition(position);
	UpdataLookAt();
	Updata();		//更新高度
	m_gun->setVisible(true);
}

void Chreo::Release()
{
	m_gun->remove();
	m_camera->remove();

}