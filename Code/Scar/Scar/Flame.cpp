#include "Flame.h"



CFlame::CFlame(void):m_flamY(9),m_flamX(6),m_flame(0)
{

}


CFlame::~CFlame(void)
{
}



void CFlame::modifyFlameByAccel( vector3df accel )
{
	if (!m_flame)
	{
		return;
	}
	IParticleBoxEmitter*pe = (IParticleBoxEmitter*)m_flame->getEmitter();
	vector3df tempaccel=accel;
	vector3df particlespeed = tempaccel.normalize()/30;
	pe->setDirection(particlespeed);
	vector3df temp;
	temp= pe->getDirection()*2000/(pe->getMaxParticlesPerSecond()+pe->getMinParticlesPerSecond());

	f32 H=temp.X>temp.Y?temp.X:temp.Y;

	if ((temp.X)>(temp.Y))
	{
		pe->setMaxStartSize(dimension2df(m_flamY,m_flamX));pe->setMinStartSize(dimension2df(m_flamY,m_flamX));
	}
	else {
		pe->setMaxStartSize(dimension2df(m_flamX,m_flamY));pe->setMinStartSize(dimension2df(m_flamX,m_flamY));
	}

}




IParticleSystemSceneNode* CFlame::createFlame( IrrlichtDevice *device,char * texname/*=NULL*/,ISceneNode*parent /*=0*/,int id/*=-1*/,irr::core::vector3df pos/*=irr::core::vector3df(0,0,0)*/,SColor &fadeoutColor/*=SColor(0,0,0,255)*/,int fadeTime/*=1000*/,aabbox3df &box/*=aabbox3df(0,0,0,1,1,1)*/,vector3df&direction/*=vector3df(0,0.03,0)*/,int minParticlePerSecond/*=10*/,int maxParticlePerSecond/*=10*/,int lifeTimeMin/*=1000*/,int lifeTimeMax/*=1000*/,f32 maxAngleDegree/*=0*/,SColor&minStartColor/*=SColor(0,255,255,255)*/,SColor maxStartColor/*=SColor(0,255,255,255)*/,dimension2df minStartSize/*=dimension2df(6,9)*/,dimension2df& maxStartSize/*=dimension2df( 6,9 )*/,vector3df accl/*=vector3df(0,5,0)*/ )
{
	if(!device)return NULL;
	ISceneManager* smgr = device->getSceneManager();
	m_flame=smgr->addParticleSystemSceneNode(false,parent,id,pos);
	IParticleBoxEmitter * boxemitter=m_flame->createBoxEmitter(box,direction,minParticlePerSecond,maxParticlePerSecond,minStartColor,maxStartColor,lifeTimeMin,lifeTimeMax,maxAngleDegree,minStartSize,maxStartSize);
	m_flame->setEmitter(boxemitter);
	boxemitter->drop();
	IParticleFadeOutAffector* fadeoutAffactor=m_flame->createFadeOutParticleAffector(fadeoutColor,fadeTime);
	m_flame->addAffector(fadeoutAffactor);
	fadeoutAffactor->drop();


	m_flame->setMaterialFlag(EMF_LIGHTING,false);

	m_flame->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);

	if (texname)
	{
		m_flame->setMaterialTexture(0, device->getVideoDriver()->getTexture(texname));
	}
	m_flamY=(minStartSize.Height+maxStartSize.Height)/2;
	m_flamX = (minStartSize.Width+maxStartSize.Width)/2;

	modifyFlameByAccel(accl);
	return m_flame;
}

void CFlame::setpos( vector3df pos )
{
	if (m_flame)
	{
		m_flame->setPosition(pos);
	}
}

