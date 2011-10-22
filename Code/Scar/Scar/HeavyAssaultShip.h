#pragma once
#include "iship.h"
class CHeavyAssaultShip :
	public IShip
{
public:
	CHeavyAssaultShip(irr::scene::IMesh* mesh, irr::scene::ISceneNode* parent,
		irr::scene::ISceneManager* mgr,	s32 id,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f)):
	IShip( mesh,  parent,mgr,	id,position ,rotation ,scale )
	{
		initShip(L"电子信息舰");
	}
	~CHeavyAssaultShip(void);
};

