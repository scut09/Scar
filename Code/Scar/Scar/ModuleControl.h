/*
** 作者：杨旭瑜
** 说明：模型的运动控制
**
*/

#ifndef _MODULECONTROL_H_
#define _MODULECONTROL_H_

#include <cmath>
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;



class ModuleControl
{
public:
	ModuleControl(void);
	~ModuleControl(void);


public:
	// 添加模型以及其视野照相机
	bool Initialize(ICameraSceneNode* pCamara, ISceneNode * pModule);

	bool setCamaraPos(vector3df pos);

	bool setModuleposRelateToCamara(vector3df pos);//  设置模型相对于照相机的位置

	bool MoveForward(f32 step);

	void GetForwardVector(vector3df& v);// 得到向前的单位向量

	void OnEvent( const SEvent& event );

	void SetModuelRotation(vector3df Rotate); // 设置模型的旋转角度（相对于模型自己的坐标系）

	void SetCamaraRotation(vector3df Rotate); // 设置摄像机的旋转角度（相对于target的坐标系）

	void ShutDown(void);// 类的关闭
public:
	ICameraSceneNode*		pCamara; 
	ISceneNode *			pModule;
	vector3df				CamaraPos;
	vector3df				ModuleposRelateToCamaraVector;// 保存模型相对与摄像机的位置
	vector3df				m_vCamaraRotation;// 照相机的旋转角度
	vector3df				m_vModuleRotation;// 物体的旋转角度
	core::position2d<f32>	CenterCursor; //保存屏幕中心鼠标位置
	core::position2d<f32>	CursorPos;// 保存当前鼠标位置

};


#endif