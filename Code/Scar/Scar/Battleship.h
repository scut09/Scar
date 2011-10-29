//
///********************************************************************
//    ����ʱ��: 2011-10-22   11:44
//    �ļ���:   Battleship.h
//    ����:     л����
//    ˵��:	  �̳�IShip����,ս�н�,�ص���Ҫ���ڹ���
//
//*********************************************************************/
//#ifndef Battleship_h__
//#define Battleship_h__
//
//
//
//#pragma once
//#include "iship.h"
//
//
//class CBattleship :
//	public IShip
//{
//public:
//	CBattleship(irr::scene::IAnimatedMesh* mesh, irr::scene::ISceneNode* parent,
//		irr::scene::ISceneManager* mgr,	s32 id,
//		const core::vector3df& position = core::vector3df(0,0,0),
//		const core::vector3df& rotation = core::vector3df(0,0,0),
//		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f)):
//	IShip( mesh,  parent,mgr,	id,position ,rotation ,scale )
//	{
//		initShip(L"ս�н�");
//		HitDizzy = HitAdd = 1;
//		HitAddRefreshTime = HitDizzyRefreshTime = 1000;
//		RecordHitAddRefreshTime = RecordHitDizzyRefreshTime = 0;
//	}
//	~CBattleship(void);
//
//	//��������
//	virtual bool PerformHitDizzy();
//	virtual bool PerformHitAdd();
//
//	//���ü��� 
//    virtual void ReSetHitAdd(const u32& time);
//	virtual void ReSetHitDizzy( const u32& time);
//
//	//�޸ĺͻ�ȡ����ˢ��ʱ��
//	virtual void SetHitDizzyRefreshTime( const u32& time){ HitDizzyRefreshTime = time; }
//	virtual void SetHitAddRefreshTime ( const u32& time ) { HitAddRefreshTime = time; }
//	virtual u32  GetHitAddrefreshTime( ) const { return HitAddRefreshTime; }
//	virtual u32  GetHitDizzyRefreshTime()const { return HitDizzyRefreshTime; }
//
//	//�����͹رռ���
//	virtual void EnableHitDizzy(){ HitDizzy = true; }
//	virtual void DisableHitDizzy(){ HitDizzy = false;}
//	virtual void EnableHitAdd(){ HitAdd = true; }
//	virtual void DisableHitAdd(){ HitAdd = false; }
//
//	//ˢ������
//	virtual void RefreshAttrbutes( const u32& time){
//		ReSetHitAdd(time);
//		ReSetHitDizzy(time);
//		IShip::RefreshAttrbutes(time);
//	};
//
//private:
//	u32  RecordHitDizzyRefreshTime;          //��¼��ȥ��ʱ��
//	u32  RecordHitAddRefreshTime;            //��¼��ȥ��ʱ��
//protected:
//	bool HitDizzy;                           //����
//	u32  HitDizzyRefreshTime;                //����ˢ��ʱ��
//	u32  HitAddRefreshTime;                  //��ǿ�˺�ˢ��ʱ��
//	bool HitAdd;                             //��ǿ�˺�
//
//};
//
//#endif // Battleship_h__