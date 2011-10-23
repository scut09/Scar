/********************************************************************
    ����ʱ��: 2011-10-23  
    �ļ���:   Cruiseship.h
    ����:     л����
    ˵��:	  �̳�IShip����,Ѳ����,�ص���Ҫ��������

*********************************************************************/
#ifndef Cruiseship_h__
#define Cruiseship_h__


#include "iship.h"
class CCruiseship :
	public IShip



{
public:
	CCruiseship(irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr,	s32 id,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f)):
	IShip( mesh,  parent,mgr,	id,position ,rotation ,scale )
	{
		initShip(L"Ѳ����");
		MoveImmediate =1;
		MoveImmediateRefreshTime = 3000;
	}
	~CCruiseship(void);

	//��������
	virtual bool PerformMoveImmediate(const vector3df&pos);
	
	//���ü���
	virtual void ReSetMoveImmediate( const u32& time);
	
	//��ȡ���޸ļ���ˢ��ʱ��
	virtual void SetMoveImmediateRefreshTime( const u32& time){  MoveImmediateRefreshTime = time; }
	virtual u32 GetMoveImmediateRefreshTime() { return MoveImmediateRefreshTime; }

	//�����͹رռ���
	virtual void EnableMoveImmediate(){ MoveImmediate = true; }
	virtual void DisableMoveImmediate() { MoveImmediate = false;}

	//ˢ������
	virtual void RefreshAttrbutes( const u32& time){
		ReSetMoveImmediate(time);
		IShip::RefreshAttrbutes(time);
	};

private:
	u32  RecordMoveImmediateRefreshTime;     //��¼��ȥ��ʱ��
	
protected:
	bool MoveImmediate;                      //˲���ƶ�
	u32  MoveImmediateRefreshTime;           //˲���ƶ�ˢ��ʱ��
	
};

#endif // Cruiseship_h__