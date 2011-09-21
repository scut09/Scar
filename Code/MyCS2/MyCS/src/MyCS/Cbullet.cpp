#include "Cbullet.h"

scene::ISceneCollisionManager*					Cbullet::g_collManager = NULL;	//碰撞管理器
std::map<scene::ISceneNode*, IGlobe*>	Cbullet::g_playerList;			//玩家列表	用于后面的碰撞检测

scene::ISceneManager*		IGlobe::g_smgr = NULL;			//场景管理器
video::IVideoDriver*		IGlobe::g_driver = NULL;
IrrlichtDevice*				IGlobe::g_device = NULL;
IGUIEnvironment*			IGlobe::g_guienv = NULL;		//设备对象
Cbullet::Cbullet(void)
{
	
}

Cbullet::~Cbullet(void)
{	
}



int Cbullet::Attack( vector3df direction, vector3df& position, int& range )
{
	
	core::line3d<f32> ray;							//构造碰撞线
	ray.start = position;
	//子弹的最远位置
	ray.end = position + (direction - position).normalize() * range;
	core::vector3df intersection;
	core::triangle3df hitTriangle;

	scene::ISceneNode * selectedSceneNode =				//碰撞检测
		g_collManager->getSceneNodeAndCollisionPointFromRay(
		ray, intersection, hitTriangle, 1, 0); 

	
	if(selectedSceneNode)								//如果碰到
	{
		range = 1;
		position = intersection;
		scene::IParticleSystemSceneNode*	m_bullet = CreateBullet();		//子弹的粒子对象
		IGlobe* player = g_playerList[selectedSceneNode];
		if (NULL != player)
		{	
			m_bullet->setParent(selectedSceneNode);				//如果击中活动目标 粒子应该绑定到目标节点上
			position = intersection - selectedSceneNode->getPosition();
			m_bullet->setPosition(position);			
			
			return player->m_index;
		}
		m_bullet->setPosition(intersection);		
		return -1;
	}
	else						//没有碰到
	{
		position = ray.end;
		range = -1;				
		return -1;
	}	
}

scene::IParticleSystemSceneNode* Cbullet::CreateBullet( )
{
	//初始化粒子系统
	scene::IParticleSystemSceneNode* m_bullet =
		IGlobe::g_smgr->addParticleSystemSceneNode(false);

	// create and set emitter
	scene::IParticleEmitter* em = m_bullet->createBoxEmitter(
		core::aabbox3d<f32>(-2,0,-2,2,1,2),
		core::vector3df(0.0f,0.03f,0.0f),
		10,50,
		video::SColor(0,255,255,255), video::SColor(0,255,255,255),
		400,1100);
	em->setMinStartSize(core::dimension2d<f32>(30.0f, 40.0f));
	em->setMaxStartSize(core::dimension2d<f32>(30.0f, 40.0f));

	m_bullet->setEmitter(em);
	em->drop();

	// create and set affector
	scene::IParticleAffector* paf = m_bullet->createFadeOutParticleAffector();
	m_bullet->addAffector(paf);
	paf->drop();

	// adjust some material settings
	m_bullet->setMaterialFlag(video::EMF_LIGHTING, false);
	m_bullet->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	m_bullet->setMaterialTexture(0, IGlobe::g_driver->getTexture("image/fireball.bmp"));
	m_bullet->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);

	m_bullet->setVisible(true);

	scene::ISceneNodeAnimator* anim = IGlobe::g_smgr->createDeleteAnimator(1000);
	m_bullet->addAnimator(anim);
	anim->drop();
	return m_bullet;
}

void Cbullet::CreateBullet( vector3df position , ISceneNode* parent)
{
	scene::IParticleSystemSceneNode* m_bullet = CreateBullet();
	if(NULL != parent)		//如果击中目标 粒子应该绑定到目标节点上
	{
		m_bullet->setParent(parent);
		position.Y -= 90;
		m_bullet->setPosition(position);
	}
	else
	{
		m_bullet->setPosition(position);
	}
	
}