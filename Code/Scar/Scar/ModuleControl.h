/*
** ���ߣ������
** ˵����ģ�͵��˶�����
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
	// ���ģ���Լ�����Ұ�����
	bool Initialize(ICameraSceneNode* pCamara, ISceneNode * pModule);

	bool setCamaraPos(vector3df pos);

	bool setModuleposRelateToCamara(vector3df pos);//  ����ģ��������������λ��

	bool MoveForward(f32 step);

	void GetForwardVector(vector3df& v);// �õ���ǰ�ĵ�λ����

	void OnEvent( const SEvent& event );

	void SetModuelRotation(vector3df Rotate); // ����ģ�͵���ת�Ƕȣ������ģ���Լ�������ϵ��

	void SetCamaraRotation(vector3df Rotate); // �������������ת�Ƕȣ������target������ϵ��

	void ShutDown(void);// ��Ĺر�
public:
	ICameraSceneNode*		pCamara; 
	ISceneNode *			pModule;
	vector3df				CamaraPos;
	vector3df				ModuleposRelateToCamaraVector;// ����ģ��������������λ��
	vector3df				m_vCamaraRotation;// ���������ת�Ƕ�
	vector3df				m_vModuleRotation;// �������ת�Ƕ�
	core::position2d<f32>	CenterCursor; //������Ļ�������λ��
	core::position2d<f32>	CursorPos;// ���浱ǰ���λ��

};


#endif