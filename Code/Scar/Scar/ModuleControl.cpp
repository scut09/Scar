#include "ModuleControl.h"
#include <iostream>


ModuleControl::ModuleControl(void)
{
	pCamara = 0;
	pModule = 0;
	CamaraPos.X = 0.f;
	CamaraPos.Y = 0.f;
	CamaraPos.Z = 0.f;
	ModuleposRelateToCamaraVector.X = 0.f;
	ModuleposRelateToCamaraVector.Y = 0.f;
	ModuleposRelateToCamaraVector.Z = 0.f;
}


ModuleControl::~ModuleControl(void)
{
}


// 添加模型以及其视野照相机
bool ModuleControl::Initialize(ICameraSceneNode* pCamara, ISceneNode * pModule)
{
	if (!this->pCamara && !this->pModule)
	{
		this->pCamara = pCamara;
		this->pModule = pModule;
		this->pCamara->addChild(this->pModule);
		return true;
	}
	return false;
	
}


bool ModuleControl::setCamaraPos(vector3df pos)
{
	if (pCamara)
	{
		pCamara->setPosition(pos);
		CamaraPos.X = pos.X;
		CamaraPos.Y = pos.Y;
		CamaraPos.Z = pos.Z;
		return true;
	}
	return false;
}


bool ModuleControl::setModuleposRelateToCamara(vector3df v)
{
	if (pModule)
	{
		pModule->setPosition(v);
		ModuleposRelateToCamaraVector.X = v.X;
		ModuleposRelateToCamaraVector.Y = v.Y;
		ModuleposRelateToCamaraVector.Z = v.Z;
		return true;
	}
	return false;
}


bool ModuleControl::MoveForward(f32 step)
{
	if (pCamara && pModule)
	{
		vector3df CamaraPos = pCamara->getPosition();
		vector3df LookAtPos = pCamara->getTarget();
		vector3df ForwardVector = LookAtPos - CamaraPos;
		ForwardVector = ForwardVector.normalize();
		pCamara->setPosition(CamaraPos + ForwardVector * step);
		return true;
	}

	std::cout << "Hi";
	return false;
}


void ModuleControl::ShutDown(void)
{
	if (pCamara)
	{
		delete pCamara;
	}
	if (pModule)
	{
		delete pModule;
	}

}


bool ModuleControl::FlyLeft(f32 speed)
{
	if (pCamara && pModule)
	{
		pModule->setRotation(vector3df(10.f, 180.f - 45.f, 10.f));
		return true;
	}
	return false;
}

void ModuleControl::OnEvent( const SEvent& event )
{
	std::cout << "haha0";
}
