/********************************************************************
    ����ʱ��: 2011-10-23  
    �ļ���:   Frigate.h
    ����:     л����
    ˵��:	  �̳�IShip����,������,�ص���Ҫ���ڷ���

*********************************************************************/
#pragma once
#include "iship.h"
class CFrigate :
	public IShip
{
public:
	CFrigate(irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr,	s32 id,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f)):
	IShip( mesh,  parent,mgr,	id,position ,rotation ,scale )
	{
		initShip(L"������");
		BuildWall = BuildAir =true;
		BuildWallRefreshTime = BuildAirRefreshTime =2000;
		RecordBuildWallRefreshTime = RecordBuildAirRefreshTime =0;
	}
	~CFrigate(void);

	//�رպ���������
	virtual void EnableBuildWall() { BuildWall = true ;}
	virtual void DisableBuildWall() { BuildWall = false; }
	virtual void EnableBuildAir() { BuildAir = true; }
	virtual void DisableBuildAir() { BuildAir = false; }

	//��ȡ���޸ļ���ˢ��ʱ��
	virtual void SetBuildWallRefreshTime( const u32& time){ BuildWallRefreshTime = time; }
	virtual u32 GetBuildWallRefreshTime() const { return BuildWallRefreshTime ;}
	virtual void SetBuildAirRefreshTime( const u32& time){ BuildAirRefreshTime = time; }
	virtual u32  GetBuildAirRefreshTime()const { return BuildAirRefreshTime; }

	//���÷������弼��
	virtual void ResetBuildWall(const u32& time);

	//���÷���ǽ����
	virtual void ResetBuildAir(const u32& time);

	//�������� 
	virtual bool PerformBuildAir();
	virtual bool PerformBuildWall(){ Energy --;return BuildWall; }

	//��������
	virtual void RefreshAttrbutes(const u32& time);
private:
	u32 RecordBuildWallRefreshTime;
	u32 RecordBuildAirRefreshTime;
protected:
	bool BuildWall;                      //����ǽ����
	u32  BuildWallRefreshTime;           //����ǽ����ˢ��ʱ��
	u32  BuildAirRefreshTime;           //�������弼��ˢ��ʱ��
	bool BuildAir;                      //�������弼��
};

