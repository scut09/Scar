///////////////////////////////////////////////////////
//  copyright:	Tian's 2009-2010
//  by author:	Tian
//create date:	2009/11/18 1:02
//description:	Ӣ����
///////////////////////////////////////////////////////

#ifndef Chreo_h
#define Chreo_h

#pragma once

#include "Ihreo.h"
#include "Cbullet.h"

//////////////////////////////
///	@brief �ӵ����еĻص�����
///	@param [in] positon:�����е�λ��
///	@param [in] index:	�����е�����
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
	//desc:����Ӣ��	
	//return:void
	///////////////////////////////////////
	void Updata();

	///////////////////////////////////////
	//desc:�ƶ�Ӣ��
	//parm [in] x:���ƶ����ĵط�
	//parm [in] y:���ƶ����ĵط�
	//return:void
	///////////////////////////////////////
	bool MoveTo(int direction, int y, int z);

	///////////////////////////////////////
	//desc:��תӢ��
	//parm [in] rot:�Ƕ�
	//return:void
	///////////////////////////////////////
	void Trun(vector3df rot);

	///////////////////////////////////////
	//desc:��õ�ǰ����	
	//return:����
	///////////////////////////////////////
	vector3df GetRot();

	


	///////////////////////////////////////
	//desc:���Ӣ�۵�ǰ��λ��	
	//return:void
	///////////////////////////////////////
	vector3df GetPosition();

	///////////////////////////////////////
	//desc:����������Ŀ��	
	//return:void
	///////////////////////////////////////
	vector3df GetTagrt();


	//////////////////////////////
	///	@brief ���ö���״̬
	///	@param [in] state:�������
	///	@return void
	//////////////////////////////
	void	SetAinmState(int state);

	//////////////////////////////
	///	@brief ���ö���״̬
	///	@param [in] state:��������
	///	@return void
	//////////////////////////////
	void	SetAinmState(const char* state);

	///////////////////////////////////////
	//desc:����Ӣ���Ƿ����
	//parm [in] squat:	
	//return:void
	///////////////////////////////////////
	void SetSquat(bool squat);

	///////////////////////////////////////
	//desc:�ж�Ӣ���Ƿ����
	//return:void
	///////////////////////////////////////
	bool GetSquat();

	//////////////////////////////
	///	@brief ����Ӣ�۵Ľڵ�	
	///	@return void
	//////////////////////////////
	irr::scene::ISceneNode* GetSceneNode();	

	//////////////////////////////
	///	@brief Ӣ������
	///	@return void
	//////////////////////////////
	void Death();
	
	//////////////////////////////
	///	@brief �ж�Ӣ���Ƿ�����	
	///	@return ��������true
	//////////////////////////////
	bool isDeath();

	//////////////////////////////
	///	@brief ���� ��Ӣ�۸���
	///	@param [in] position:�����λ��
	///	@return void
	//////////////////////////////
	void ReSet(vector3df position);

	///////////////////////////////////////
	//desc: �ͷ���Դ	
	//return:void
	///////////////////////////////////////
	void Release();

	bool	m_AnimEnd;		//�����Ƿ���
	scene::IAnimatedMeshSceneNode* m_gun;
private:
	void Init(vector3df position);

	void DoInput();	//��������

	void UpdataLookAt();	//����lookat

	///////////////////////////////////////
	//desc:�ж��Ƿ����ƶ�
	//parm [in] dirction:��һ���ƶ��ķ���	
	//return:void
	///////////////////////////////////////
	bool CanMove(vector3df& dirction);

private:
	scene::ICameraSceneNode*	m_camera;
	
	OnAttackEvent				m_callBack;
	bool						m_isdeath;
public:
	int							m_ReSetCount;		//�������

};
#endif