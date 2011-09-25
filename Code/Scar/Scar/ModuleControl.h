/*
** 作者：杨旭瑜
** 说明：
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
	bool setModuleposRelateToCamara(vector3df pos);
	bool MoveForward(f32 step);
	void ShutDown(void);


public:
	ICameraSceneNode* pCamara;
	ISceneNode * pModule;
	vector3df CamaraPos;
	vector3df ModuleposRelateToCamaraVector;
	bool FlyLeft(f32 speed);
	int FlyRight(f32 speed);
	int FlyUp(f32 speed);
	int FlyDown(f32 speed);
};


#endif