#pragma once
//////////////////////////////////////////////////////////////////////////
//通过纹理来渲染的火焰
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
     f32 m_maxAccel;//最大加加速度 
	 u32 m_flamX;//粒子的宽
	 u32 m_flamY;//粒子的高
     u32 m_lifetime;//粒子的生命
	 IParticleSystemSceneNode *m_flame;

public:
	IParticleSystemSceneNode *getParticle();//获取粒子系统节点
	void setMaxAccel(f32&accel);//设置最大加速度的模
	void modifyFlameByAccel(vector3df accel);//通过加速度调整火焰

	CFlame(void);
	~CFlame(void);

	//创建火焰
	IParticleSystemSceneNode* createFlame(IrrlichtDevice *device,
		char * texname=NULL,ISceneNode*parent =0,int id=-1,
		irr::core::vector3df pos=irr::core::vector3df(0,0,0),
		SColor &fadeoutColor=SColor(0,0,0,255),
		int fadeTime=1000,aabbox3df &box=aabbox3df(0,0,0,1,1,1),
		vector3df&direction=vector3df(0,0.03,0),int minParticlePerSecond=10,int maxParticlePerSecond=10,
		int lifeTimeMin=1000,int lifeTimeMax=1000,f32 maxAngleDegree=0,
		SColor&minStartColor=SColor(0,255,255,255),SColor maxStartColor=SColor(0,255,255,255),
		dimension2df minStartSize=dimension2df(6,9),dimension2df& maxStartSize=dimension2df( 6,9 ),
		vector3df accl=vector3df(0,5,0));
};

