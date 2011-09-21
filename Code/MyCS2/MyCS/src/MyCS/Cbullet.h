///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/18 16:49
//Describe: 子弹类
///////////////////////////////////////////////////////////////////////

#ifndef  Cbullet_h
#define  Cbullet_h
#pragma once

#include "IGlobe.h"
#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

#include <map>

class Cbullet
{
public:
	Cbullet(void);
	~Cbullet(void);	

	//////////////////////////////
	///	@brief 攻击
	///	@param [in] direction:子弹的方向
	///	@param [in/out] position:子弹的起始位置 将返回子弹撞击的位置
	///	@param [in/out] range:子弹的攻击范围 如果子弹有击中目标 返回1，否则返回-1
	///	@return 如果击中目标 返回目标的索引 否则返回-1
	//////////////////////////////
	static int Attack(vector3df direction, vector3df& position, int& range);

	//////////////////////////////
	///	@brief 创建一颗子弹
	///	@return void
	//////////////////////////////
	static void CreateBullet(vector3df position, ISceneNode* parent = NULL);


public:
	static std::map<scene::ISceneNode*, IGlobe*>	g_playerList;			//玩家列表	用于后面的碰撞检测
	static scene::ISceneCollisionManager*					g_collManager;	//碰撞管理器		
	

protected:
	static scene::IParticleSystemSceneNode*	CreateBullet();
};
#endif