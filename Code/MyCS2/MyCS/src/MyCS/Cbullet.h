///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/18 16:49
//Describe: �ӵ���
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
	///	@brief ����
	///	@param [in] direction:�ӵ��ķ���
	///	@param [in/out] position:�ӵ�����ʼλ�� �������ӵ�ײ����λ��
	///	@param [in/out] range:�ӵ��Ĺ�����Χ ����ӵ��л���Ŀ�� ����1�����򷵻�-1
	///	@return �������Ŀ�� ����Ŀ������� ���򷵻�-1
	//////////////////////////////
	static int Attack(vector3df direction, vector3df& position, int& range);

	//////////////////////////////
	///	@brief ����һ���ӵ�
	///	@return void
	//////////////////////////////
	static void CreateBullet(vector3df position, ISceneNode* parent = NULL);


public:
	static std::map<scene::ISceneNode*, IGlobe*>	g_playerList;			//����б�	���ں������ײ���
	static scene::ISceneCollisionManager*					g_collManager;	//��ײ������		
	

protected:
	static scene::IParticleSystemSceneNode*	CreateBullet();
};
#endif