#include "Cenemy.h"

Cenemy::Cenemy(int index, vector3df position)
{
	m_HP = 100;
	m_maxHP = 100;
	m_IsSquat = false;
	m_killCount = 0;
	m_beKill = 0;

	m_isRun = false;
	m_speed = 5;
	m_rot = vector3df(0,0,0);

	m_index = index;
	m_enemy = g_smgr->addAnimatedMeshSceneNode(g_smgr->getMesh("model/hreo/sydney.md2"));
	m_enemy->setPosition(core::vector3df(position));	//����λ��
	m_enemy->setScale(core::vector3df(2, 2, 2));		//ģ�ͷŴ�
	m_enemy->setRotation(core::vector3df(0,-90,0));		//��ת90��
	m_enemy->setMD2Animation(scene::EMAT_STAND);
	m_enemy->setAnimationEndCallback(this);
	m_enemy->setLoopMode(false);
	m_enemy->setAnimationSpeed(10.f);

	Updata();	//���¸߶�

	g_device->getCursorControl()->setVisible(false);
	video::SMaterial material;							//���ò�������
	material.setTexture(0, g_driver->getTexture("model/hreo/sydney.bmp"));
	material.Lighting = false;							//�ƹ�ر�
	material.NormalizeNormals = true;
	m_enemy->getMaterial(0) = material;
	
	// Ϊ�ڵ������ײ�����
	scene::ITriangleSelector* selector  = g_smgr->createTriangleSelector(m_enemy);
	m_enemy->setTriangleSelector(selector);
	selector->drop(); 
}

Cenemy::~Cenemy(void)
{	
}

bool Cenemy::MoveTo( int x, int y, int z)
{
	vector3df move(x, m_IsSquat?y:y-60 , z);
	if( !m_isRun)
	{
		
		if (m_IsSquat)			//����Ƕ��� �Ͳ��Ŷ��µĶ���
		{
			ISound::MyPlaySound(ISound::SND_MinMove, m_enemy->getPosition());	//�����ӵ�����
			m_enemy->setMD2Animation(scene::EMAT_CROUCH_WALK);
		}
		else
		{
			ISound::MyPlaySound(ISound::SND_Move, m_enemy->getPosition());	//�����ӵ�����
			m_enemy->setMD2Animation(scene::EMAT_RUN);
		}		
		m_isRun = true;
	}	
	m_enemy->setPosition(move);
	return true;
}

irr::core::vector3df Cenemy::GetPosition()
{
	return vector3df(0,0,0);
}

void Cenemy::Updata()
{
	core::line3d<f32> ray;
	ray.start = m_enemy->getPosition();
	ray.end = ray.start;
	ray.end.Y -= 1000;

	
	core::vector3df intersection;
	core::triangle3df hitTriangle;

	scene::ISceneCollisionManager* collMan = g_smgr->getSceneCollisionManager();
	scene::ISceneNode * selectedSceneNode =
		collMan->getSceneNodeAndCollisionPointFromRay(ray,intersection, hitTriangle, 1, 0); //�������ײ���
	
	if(selectedSceneNode)
	{
		intersection.Y+=60;
		m_enemy->setPosition(intersection);		//���¸߶�
	}
}

void Cenemy::Trun( vector3df rot )
{
	m_rot = rot;
	m_rot.Y -= 90;
	m_enemy->setRotation(m_rot);
}

irr::core::vector3df Cenemy::GetRot()
{
	return m_rot;
}

void Cenemy::SetAinmState( int state )
{
	m_enemy->setMD2Animation((EMD2_ANIMATION_TYPE)state);
}

void Cenemy::OnAnimationEnd( IAnimatedMeshSceneNode* node )
{
	m_isRun = false;
	if(m_HP > 0)
	{
		if (m_IsSquat)			//����Ƕ��� �Ͳ��Ŷ��µĶ���
		{
			node->setMD2Animation(scene::EMAT_CROUCH_STAND);
		}
		else
		{
			node->setMD2Animation(scene::EMAT_STAND);
		}		
	}
	else
	{
		node->setVisible(false);
	}
	
}

irr::scene::ISceneNode* Cenemy::GetSceneNode()
{
	return m_enemy;
}

void Cenemy::SetSquat( bool squat )
{
	m_IsSquat = squat;
	if (m_IsSquat)			//����Ƕ��� �Ͳ��Ŷ��µĶ���
	{
		m_enemy->setMD2Animation(scene::EMAT_CROUCH_STAND);		
	}
	else
	{
		m_enemy->setMD2Animation(scene::EMAT_STAND);		
	}
	m_isRun = false;
}

bool Cenemy::GetSquat()
{
	return m_IsSquat;
}

void Cenemy::ReSet( vector3df position )
{

	m_enemy->setPosition(core::vector3df(position));	//����λ��	
	m_enemy->setRotation(core::vector3df(0,-90,0));		//��ת90��
	m_enemy->setMD2Animation(scene::EMAT_STAND);

	Updata();	//���¸߶�

	m_HP = m_maxHP;	
	m_IsSquat = false;
	m_isRun = false;
	m_enemy->setVisible(true);


}

void Cenemy::Release()
{
	m_enemy->remove();
}