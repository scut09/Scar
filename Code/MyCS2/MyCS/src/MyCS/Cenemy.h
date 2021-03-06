///////////////////////////////////////////////////////////////////////
//Copyright(c) 1999-2009, TQ Digital Entertainment, All Rights Reserved
//Author:   Tian
//Created:  2009/11/18 18:57
//Describe: 敌人
///////////////////////////////////////////////////////////////////////

#ifndef  Cenemy_h
#define  Cenemy_h
#pragma once

#include "Ihreo.h"
#include "../../include/ISound.h"


class Cenemy:public IHreo,public IAnimationEndCallBack
{
public:
	Cenemy(int index, vector3df position);
	~Cenemy(void);
public:
	virtual void OnAnimationEnd(IAnimatedMeshSceneNode* node);	

	///////////////////////////////////////
	//desc:更新英雄y坐标
	//return:void
	///////////////////////////////////////
	void Updata();

	///////////////////////////////////////
	//desc:移动英雄
	//parm [in] x:移动到的方式	
	//parm [in] Z:移动到的方式	
	//return:void
	///////////////////////////////////////
	bool MoveTo(int x, int y, int z);

	///////////////////////////////////////
	//desc:旋转英雄
	//parm [in] rot:角度
	//return:void
	///////////////////////////////////////
	void Trun(vector3df rot);

	///////////////////////////////////////
	//desc:获得当前朝向	
	//return:朝向
	///////////////////////////////////////
	vector3df GetRot();


	///////////////////////////////////////
	//desc:获得英雄当前的位置	
	//return:void
	///////////////////////////////////////
	vector3df GetPosition();

	//////////////////////////////
	///	@brief 设置动画状态
	///	@param [in] state:动画编号
	///	@return void
	//////////////////////////////
	void	SetAinmState(int state);

	///////////////////////////////////////
	//desc:设置英雄是否蹲下
	//parm [in] squat:	
	//return:void
	///////////////////////////////////////
	void SetSquat(bool squat);

	///////////////////////////////////////
	//desc:判断英雄是否蹲下
	//return:void
	///////////////////////////////////////
	bool GetSquat();

	//////////////////////////////
	///	@brief 返回英雄的节点	
	///	@return void
	//////////////////////////////
	irr::scene::ISceneNode* GetSceneNode();

	//////////////////////////////
	///	@brief 重置 及英雄复活
	///	@param [in] position:复活的位置
	///	@return void
	//////////////////////////////
	void ReSet(vector3df position);

	///////////////////////////////////////
	//desc: 释放资源	
	//return:void
	///////////////////////////////////////
	void Release();

private:
	scene::IAnimatedMeshSceneNode*	m_enemy;
	bool	m_isRun;

};
#endif