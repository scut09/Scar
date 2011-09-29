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
	m_MousePos.X = 0;
	m_MousePos.Y = 0;
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
		this->pCamara->setPosition(CamaraPos);
		this->pModule->setPosition(ModuleposRelateToCamaraVector);
		m_vCamaraRotation = pCamara->getRotation();
		m_vModuleRotation = pModule->getRotation();
		pCamara->bindTargetAndRotation(true);
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


void ModuleControl::GetForwardVector(vector3df& v)
{
	vector3df CamaraPos = pCamara->getPosition();
	vector3df LookAtPos = pCamara->getTarget();
	vector3df ForwardVector = LookAtPos - CamaraPos;
	v = ForwardVector.normalize();
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
	// 鼠标消息处理
	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		 if (event.MouseInput.Wheel == -1)
		 {
			 vector3df vForward;
			 GetForwardVector(vForward);
			 ModuleposRelateToCamaraVector = ModuleposRelateToCamaraVector*2;
			 setModuleposRelateToCamara(ModuleposRelateToCamaraVector);
		 }

		 if (event.MouseInput.Wheel == 1)
		 {
			 vector3df vForward;
			 GetForwardVector(vForward);
			 ModuleposRelateToCamaraVector = ModuleposRelateToCamaraVector/2;
			 setModuleposRelateToCamara(ModuleposRelateToCamaraVector);
		 }
		 

		 s32 offsety = (event.MouseInput.Y - m_MousePos.Y)%360;
		 s32 offsetx = (event.MouseInput.X - m_MousePos.X)%360;

		 if ((m_vCamaraRotation.X + offsety) < 90.0 )
		 {
			 m_vCamaraRotation += vector3df(offsety, 0.f, 0.f);
		 } 

		 if ((m_vCamaraRotation.Y + offsetx ) < 90.0)
		 {
			 m_vCamaraRotation += vector3df(0.f, offsetx, 0.f);
		 }
		 

		 //m_vCamaraRotation.X = (s32)m_vCamaraRotation.X % 90;
		 //m_vCamaraRotation.Y = (s32)m_vCamaraRotation.Y % 90;
		 //m_vCamaraRotation.Z = (s32)m_vCamaraRotation.X % 90;

		SetCamaraRotation(m_vCamaraRotation);
		 
			


		 m_MousePos.X = event.MouseInput.X;
		 m_MousePos.Y = event.MouseInput.Y;
		 //std::cout << event.MouseInput.X << '\t' << event.MouseInput.Y << std::endl;
		// std::cout << offsetx << '\t' << offsety << std::endl;
		 std::cout << pCamara->getRotation().X << '\t' << pCamara->getRotation().Y <<'\t'<< pCamara->getRotation().Z<< std::endl;
	}

	// 按键消息处理
	if (event.EventType == EET_KEY_INPUT_EVENT)
	{
		if (event.KeyInput.Key == KEY_KEY_W )
		{

		}

		if (event.KeyInput.Key == KEY_KEY_S )
		{
			//std::cout << "chao!";
		}

		if (event.KeyInput.Key == KEY_KEY_A )
		{
			m_vModuleRotation += vector3df(0.f, 0.f, 5.f);
			pModule->setRotation(m_vModuleRotation);
		}

		if (event.KeyInput.Key == KEY_KEY_D )
		{
			m_vModuleRotation += vector3df(0.f, 0.f, -5.f);
			pModule->setRotation(m_vModuleRotation);
		}
	}
		
	
}


void ModuleControl::SetModuelRotation(vector3df Rotate)
{
	m_vModuleRotation = Rotate;
	pModule->setRotation(m_vModuleRotation);
}


void ModuleControl::SetCamaraRotation(vector3df Rotate)
{
	m_vCamaraRotation = Rotate;
	pCamara->setRotation(m_vCamaraRotation);
}
