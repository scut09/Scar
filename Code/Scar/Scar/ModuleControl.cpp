#include "ModuleControl.h"
#include <iostream>
#include "MyIrrlichtEngine.h"
#include "Toolit.h"

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
	CenterCursor.set(0.5f, 0.5f);

	IrrlichtDevice* device = MyIrrlichtEngine::GetEngine()->GetDevice();
	CursorPos = device->getCursorControl()->getRelativePosition();
	device->getCursorControl()->setPosition(CenterCursor);
}


ModuleControl::~ModuleControl(void)
{
}



/************************************************************************/
/* ���ߣ������
   ���������ģ���Լ�����Ұ��������������һ��
*/
/************************************************************************/
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

/************************************************************************/
/* ���ߣ������
   �������������������������
*/
/************************************************************************/
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

/************************************************************************/
/* ���ߣ������
   ����������ģ������������λ��
*/
/************************************************************************/
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

/************************************************************************/
/* ���ߣ������
   ������ģ���Լ������ͬʱ��ǰ�ƶ�һ������
*/
/************************************************************************/
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

/************************************************************************/
/* ���ߣ������
   �������õ���ǰ�ķ�������
*/
/************************************************************************/
void ModuleControl::GetForwardVector(vector3df& v)
{
	vector3df CamaraPos = pCamara->getPosition();
	vector3df LookAtPos = pCamara->getTarget();
	vector3df ForwardVector = LookAtPos - CamaraPos;
	v = ForwardVector.normalize();
}



/************************************************************************/
/* ���ߣ������
   �������ر���
*/
/************************************************************************/
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


//bool ModuleControl::FlyLeft(f32 speed)
//{
//	if (pCamara && pModule)
//	{
//		pModule->setRotation(vector3df(10.f, 180.f - 45.f, 10.f));
//		return true;
//	}
//	return false;
//}


/************************************************************************/
/* ���ߣ������
   �������ⲿ�豸��Ϣ����
*/
/************************************************************************/
void ModuleControl::OnEvent( const SEvent& event )
{
	// �����Ϣ����
	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		 // ���ִ���
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
		 IrrlichtDevice* device = MyIrrlichtEngine::GetEngine()->GetDevice();
		 CursorPos = device->getCursorControl()->getRelativePosition();
		 if (CursorPos.equals(CenterCursor))
		 {
			 return;
		 }

		 if (event.MouseInput.isLeftPressed())
		 {
			 vector3df v = pModule->getPosition();
			 matrix4 vm = pCamara->getProjectionMatrix();
			 //pCamara->get
			 //f32 data[4];
			 //data[0] = v.X;
			 //data[1] = v.Y;
			 //data[2] = v.Z;
			 //data[3] = 1;
			 //vm.multiplyWith1x4Matrix(data);
			 //std::cout << "a" <<std::endl;

		 }

		 // ����ƶ�����
		 f32 xdelta = (CursorPos.Y - CenterCursor.Y)*30;
		 f32 ydelta = (CursorPos.X - CenterCursor.X)*30;

		 
		 if (m_vCamaraRotation.X >= 85.0 && xdelta > 0)
		 {
			  xdelta = 0;
		 }

		 if (m_vCamaraRotation.X <= -85.0 && xdelta < 0)
		 {
			 xdelta = 0;
		 }


		 m_vCamaraRotation += vector3df(xdelta, 0.0, 0.0);
		 m_vCamaraRotation += vector3df(0.0, ydelta, 0.0);

		 
		 SetCamaraRotation(m_vCamaraRotation);
		 device->getCursorControl()->setPosition(CenterCursor);
	
	}

	// ������Ϣ����
	if (event.EventType == EET_KEY_INPUT_EVENT)
	{
		if (event.KeyInput.Key == KEY_KEY_W )
		{

		}

		if (event.KeyInput.Key == KEY_KEY_S )
		{
		
		}

		if (event.KeyInput.Key == KEY_KEY_A )
		{
			m_vModuleRotation += vector3df(0.f, 0.f, 1.f);
			pModule->setRotation(m_vModuleRotation);
		}

		if (event.KeyInput.Key == KEY_KEY_D )
		{
			m_vModuleRotation += vector3df(0.f, 0.f, -1.f);
			pModule->setRotation(m_vModuleRotation);
		}

		if (event.KeyInput.Key == KEY_UP)
		{

		}

		if (event.KeyInput.Key == KEY_DOWN)
		{

		}

		if (event.KeyInput.Key == KEY_LEFT)
		{

		}

		if (event.KeyInput.Key == KEY_RIGHT)
		{

		}
	}
		
	
}

/************************************************************************/
/* ���ߣ������
   ����������ģ����ת�ĽǶ�
/************************************************************************/
void ModuleControl::SetModuelRotation(vector3df Rotate)
{
	m_vModuleRotation = Rotate;
	pModule->setRotation(m_vModuleRotation);
}

/************************************************************************/
/* ���ߣ������
   �����������������ת�ĽǶ�
*/
/************************************************************************/
void ModuleControl::SetCamaraRotation(vector3df Rotate)
{
	m_vCamaraRotation = Rotate;
	pCamara->setRotation(m_vCamaraRotation);
}
