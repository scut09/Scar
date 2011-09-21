///////////////////////////////////////////////////////
//  copyright:	Tian's 2009-2010
//  by author:	Tian
//create date:	2009/11/18 1:03
//description:	Ӣ����ӿ�
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
	//desc:����Ӣ�۵�y����
	//return:void
	///////////////////////////////////////
	virtual void Updata() = 0;

	///////////////////////////////////////
	//desc:�ƶ�Ӣ��
	//parm [in] dirction:�ƶ��ķ��� ����X����	
	//parm [in] z:Z����	
	//return:void
	///////////////////////////////////////
	virtual bool MoveTo(int direction,int y, int z) = 0;	

	///////////////////////////////////////
	//desc:��תӢ��
	//parm [in] rot:�Ƕ�
	//return:void
	///////////////////////////////////////
	virtual void Trun(vector3df rot) = 0;

	///////////////////////////////////////
	//desc:��õ�ǰ����	
	//return:����
	///////////////////////////////////////
	virtual vector3df GetRot() = 0;
	
	//////////////////////////////
	///	@brief ���ö���״̬
	///	@param [in] state:�������
	///	@return void
	//////////////////////////////
	virtual void	SetAinmState(int state) = 0;
	

	///////////////////////////////////////
	//desc:���Ӣ�۵�ǰ��λ��	
	//return:void
	///////////////////////////////////////
	virtual vector3df GetPosition() = 0;

	///////////////////////////////////////
	//desc:����Ӣ���Ƿ����
	//parm [in] squat:	
	//return:void
	///////////////////////////////////////
	virtual void SetSquat(bool squat) = 0;

	///////////////////////////////////////
	//desc:�ж�Ӣ���Ƿ����
	//return:void
	///////////////////////////////////////
	virtual bool GetSquat() = 0;

	//////////////////////////////
	///	@brief ����Ӣ�۵Ľڵ�	
	///	@return void
	//////////////////////////////
	virtual irr::scene::ISceneNode* GetSceneNode() = 0;


	//////////////////////////////
	///	@brief ���� ��Ӣ�۸���
	///	@param [in] position:�����λ��
	///	@return void
	//////////////////////////////
	virtual void ReSet(vector3df position) = 0;

	///////////////////////////////////////
	//desc: �ͷ���Դ	
	//return:void
	///////////////////////////////////////
	virtual void Release() = 0;

	virtual ~IHreo(){}
	
	float		m_HP;						//����ֵ
	float		m_maxHP;					//�������ֵ
	int			m_killCount;				//ɱ����
	int			m_beKill;					//��ɱ��
protected:
	int			m_AnimState;				//����״̬
	vector3df	m_rot;						//��ǰ����
	float		m_speed;					//�ƶ��ٶ�
	bool		m_IsSquat;					//��ʾ�Ƿ���� true:��ʾ����
	
	
};

#endif