/********************************************************************
    ����ʱ��: 2011-10-22   11:44
    �ļ���:   Battleship.h
    ����:     л����
    ˵��:	  �̳�IShip����,ս�н�

*********************************************************************/

#pragma once
#include "iship.h"
class CBattleship :
	public IShip
{
public:
	CBattleship(irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr,	s32 id,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f)):
	IShip( mesh,  parent,mgr,	id,position ,rotation ,scale )
	{
		initShip(L"ս�н�");
	}
	~CBattleship(void);
};

