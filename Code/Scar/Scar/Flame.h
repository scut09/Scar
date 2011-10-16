#pragma once
//////////////////////////////////////////////////////////////////////////
//ͨ����������Ⱦ�Ļ���
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class CFlame
{
private:
	u32 m_flamX;//���ӵĿ�
	u32 m_flamY;//���ӵĸ�
	u32 m_life;
	IParticleSystemSceneNode *m_flame;

public:
	IParticleSystemSceneNode *getParticle();//��ȡ����ϵͳ�ڵ�
	void modifyFlameByAccel(vector3df accel);//ͨ�����ٶȵ�������
	void setpos(vector3df pos);

	CFlame(void);
	~CFlame(void);

	//��������
	IParticleSystemSceneNode* createFlame(IrrlichtDevice *device,
		char * texname=NULL,ISceneNode*parent =0,int id=-1,
		irr::core::vector3df pos=irr::core::vector3df(0,0,0),
		SColor &fadeoutColor=SColor(0,0,0,255),
		int fadeTime=1000,aabbox3df &box=aabbox3df(0,0,0,1,1,1),
		vector3df&direction=vector3df(0,0.03,0),int minParticlePerSecond=100,int maxParticlePerSecond=100,
		int lifeTimeMin=250,int lifeTimeMax=250,f32 maxAngleDegree=0,
		SColor&minStartColor=SColor(0,255,255,255),SColor maxStartColor=SColor(0,255,255,255),
		dimension2df minStartSize=dimension2df(6,9),dimension2df& maxStartSize=dimension2df( 6,9 ),
		vector3df accl=vector3df(0,5,0));
};

