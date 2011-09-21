#include "Cbullet.h"

scene::ISceneCollisionManager*					Cbullet::g_collManager = NULL;	//��ײ������
std::map<scene::ISceneNode*, IGlobe*>	Cbullet::g_playerList;			//����б�	���ں������ײ���

scene::ISceneManager*		IGlobe::g_smgr = NULL;			//����������
video::IVideoDriver*		IGlobe::g_driver = NULL;
IrrlichtDevice*				IGlobe::g_device = NULL;
IGUIEnvironment*			IGlobe::g_guienv = NULL;		//�豸����
Cbullet::Cbullet(void)
{
	
}

Cbullet::~Cbullet(void)
{	
}



int Cbullet::Attack( vector3df direction, vector3df& position, int& range )
{
	
	core::line3d<f32> ray;							//������ײ��
	ray.start = position;
	//�ӵ�����Զλ��
	ray.end = position + (direction - position).normalize() * range;
	core::vector3df intersection;
	core::triangle3df hitTriangle;

	scene::ISceneNode * selectedSceneNode =				//��ײ���
		g_collManager->getSceneNodeAndCollisionPointFromRay(
		ray, intersection, hitTriangle, 1, 0); 

	
	if(selectedSceneNode)								//�������
	{
		range = 1;
		position = intersection;
		scene::IParticleSystemSceneNode*	m_bullet = CreateBullet();		//�ӵ������Ӷ���
		IGlobe* player = g_playerList[selectedSceneNode];
		if (NULL != player)
		{	
			m_bullet->setParent(selectedSceneNode);				//������лĿ�� ����Ӧ�ð󶨵�Ŀ��ڵ���
			position = intersection - selectedSceneNode->getPosition();
			m_bullet->setPosition(position);			
			
			return player->m_index;
		}
		m_bullet->setPosition(intersection);		
		return -1;
	}
	else						//û������
	{
		position = ray.end;
		range = -1;				
		return -1;
	}	
}

scene::IParticleSystemSceneNode* Cbullet::CreateBullet( )
{
	//��ʼ������ϵͳ
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
	if(NULL != parent)		//�������Ŀ�� ����Ӧ�ð󶨵�Ŀ��ڵ���
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