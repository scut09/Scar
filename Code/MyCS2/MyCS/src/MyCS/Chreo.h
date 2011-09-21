///////////////////////////////////////////////////////
//  copyright:	Tian's 2009-2010
//  by author:	Tian
//create date:	2009/11/18 1:02
//description:	英雄类
///////////////////////////////////////////////////////

#ifndef Chreo_h
#define Chreo_h

#pragma once

#include "Ihreo.h"
#include "Cbullet.h"

//////////////////////////////
///	@brief 子弹击中的回调函数
///	@param [in] positon:被击中的位置
///	@param [in] index:	被击中的索引
///	@return void
//////////////////////////////
typedef void (* OnAttackEvent) (vector3df positon, int index);

class Chreo:public IHreo,public IAnimationEndCallBack
{
public:
	Chreo(int index, vector3df position);
	~Chreo(void);
public:	
	virtual void OnAnimationEnd(IAnimatedMeshSceneNode* node);	

	///////////////////////////////////////
	//desc:更新英雄	
	//return:void
	///////////////////////////////////////
	void Updata();

	///////////////////////////////////////
	//desc:移动英雄
	//parm [in] x:想移动到的地方
	//parm [in] y:想移动到的地方
	//return:void
	///////////////////////////////////////
	bool MoveTo(int direction, int y, int z);

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

	///////////////////////////////////////
	//desc:获得摄像机的目标	
	//return:void
	///////////////////////////////////////
	vector3df GetTagrt();


	//////////////////////////////
	///	@brief 设置动画状态
	///	@param [in] state:动画编号
	///	@return void
	//////////////////////////////
	void	SetAinmState(int state);

	//////////////////////////////
	///	@brief 设置动画状态
	///	@param [in] state:动画名字
	///	@return void
	//////////////////////////////
	void	SetAinmState(const char* state);

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
	///	@brief 英雄死亡
	///	@return void
	//////////////////////////////
	void Death();
	
	//////////////////////////////
	///	@brief 判断英雄是否死亡	
	///	@return 死亡返回true
	//////////////////////////////
	bool isDeath();

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

	bool	m_AnimEnd;		//动画是否播完
	scene::IAnimatedMeshSceneNode* m_gun;
private:
	void Init(vector3df position);

	void DoInput();	//按键处理

	void UpdataLookAt();	//修正lookat

	///////////////////////////////////////
	//desc:判断是否能移动
	//parm [in] dirction:下一步移动的方向	
	//return:void
	///////////////////////////////////////
	bool CanMove(vector3df& dirction);

private:
	scene::ICameraSceneNode*	m_camera;
	
	OnAttackEvent				m_callBack;
	bool						m_isdeath;
public:
	int							m_ReSetCount;		//复活计算

};
#endif