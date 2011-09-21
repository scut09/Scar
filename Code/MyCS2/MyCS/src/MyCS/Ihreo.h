///////////////////////////////////////////////////////
//  copyright:	Tian's 2009-2010
//  by author:	Tian
//create date:	2009/11/18 1:03
//description:	英雄类接口
///////////////////////////////////////////////////////

#ifndef IHreo_h
#define IHreo_h

#include <irrlicht.h>
using namespace irr;
using namespace core;

#include "IGlobe.h"

enum DIRECTION
{
	DIR_NONE,
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_LUP,
	DIR_LDOWN,
	DIR_RUP,
	DIR_RDOWN,
};


class IHreo:public IGlobe
{
public:
	///////////////////////////////////////
	//desc:更新英雄的y坐标
	//return:void
	///////////////////////////////////////
	virtual void Updata() = 0;

	///////////////////////////////////////
	//desc:移动英雄
	//parm [in] dirction:移动的方向 或者X坐标	
	//parm [in] z:Z坐标	
	//return:void
	///////////////////////////////////////
	virtual bool MoveTo(int direction,int y, int z) = 0;	

	///////////////////////////////////////
	//desc:旋转英雄
	//parm [in] rot:角度
	//return:void
	///////////////////////////////////////
	virtual void Trun(vector3df rot) = 0;

	///////////////////////////////////////
	//desc:获得当前朝向	
	//return:朝向
	///////////////////////////////////////
	virtual vector3df GetRot() = 0;
	
	//////////////////////////////
	///	@brief 设置动画状态
	///	@param [in] state:动画编号
	///	@return void
	//////////////////////////////
	virtual void	SetAinmState(int state) = 0;
	

	///////////////////////////////////////
	//desc:获得英雄当前的位置	
	//return:void
	///////////////////////////////////////
	virtual vector3df GetPosition() = 0;

	///////////////////////////////////////
	//desc:设置英雄是否蹲下
	//parm [in] squat:	
	//return:void
	///////////////////////////////////////
	virtual void SetSquat(bool squat) = 0;

	///////////////////////////////////////
	//desc:判断英雄是否蹲下
	//return:void
	///////////////////////////////////////
	virtual bool GetSquat() = 0;

	//////////////////////////////
	///	@brief 返回英雄的节点	
	///	@return void
	//////////////////////////////
	virtual irr::scene::ISceneNode* GetSceneNode() = 0;


	//////////////////////////////
	///	@brief 重置 及英雄复活
	///	@param [in] position:复活的位置
	///	@return void
	//////////////////////////////
	virtual void ReSet(vector3df position) = 0;

	///////////////////////////////////////
	//desc: 释放资源	
	//return:void
	///////////////////////////////////////
	virtual void Release() = 0;

	virtual ~IHreo(){}
	
	float		m_HP;						//生命值
	float		m_maxHP;					//最大生命值
	int			m_killCount;				//杀人数
	int			m_beKill;					//被杀数
protected:
	int			m_AnimState;				//动画状态
	vector3df	m_rot;						//当前方向
	float		m_speed;					//移动速度
	bool		m_IsSquat;					//表示是否蹲下 true:表示蹲下
	
	
};

#endif